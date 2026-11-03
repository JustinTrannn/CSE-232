  // play.cpp
  // Lab 08: Virtual Pet. PROVIDED. Do not edit.
  //
  // The game. It runs before you have written anything, and it does more as
  // your Pet class grows: every function the game finds in Pet.hpp replaces
  // a stand-in, and the screen tells you which ones are still missing.
  //
  // Build:  g++ -std=c++20 -Wall play.cpp -o play            (Pet.hpp only, or no Pet.hpp yet)
  //         g++ -std=c++20 -Wall play.cpp Pet.cpp -o play    (Pet.hpp + Pet.cpp)
  // Run:    ./play          (Windows: .\play.exe)

  #if __has_include("Pet.hpp")
  #include "Pet.hpp"
  #else
  // No Pet.hpp yet. This empty class lets the game run with a pet that knows nothing.
  class Pet
  {
  };
  #endif

  #include <chrono>
  #include <concepts>
  #include <cstdlib>
  #include <iostream>
  #include <string>
  #include <thread>
  #include <vector>

  #ifdef _WIN32
  #include <windows.h>
  #endif

  const int ROOM_WIDTH{40};       // characters inside the frame
  const int ROOM_HEIGHT{6};       // rows inside the frame
  const int SPRITE_WIDTH{7};
  const int FRAMES_PER_ACTION{8};
  const int FUNCTION_COUNT{12};   // the functions the game looks for

  // =================================================================
  // Finding your functions.
  // The game asks the compiler whether your Pet class has each function it
  // needs. If it does, the game calls it. If not, the game uses a stand-in
  // and tells you what is missing. You do not need to understand how this
  // part works; it is well beyond this course.
  // =================================================================

  template <typename P>
  P makePet(std::string name)
  {
      static_assert(std::constructible_from<P, std::string> || std::default_initializable<P>,
                    "Your Pet class needs a constructor that takes the pet's name as a std::string.");
      if constexpr (std::constructible_from<P, std::string>)
      {
          return P{name};
      }
      else
      {
          return P{};
      }
  }

  template <typename P>
  std::string nameOf(P& pet)
  {
      if constexpr (requires { { pet.getName() } -> std::convertible_to<std::string>; })
      {
          return pet.getName();
      }
      else
      {
          return "???";
      }
  }

  template <typename P>
  int fullnessOf(P& pet)
  {
      if constexpr (requires { { pet.getFullness() } -> std::convertible_to<int>; })
      {
          return pet.getFullness();
      }
      else
      {
          return 50;
      }
  }

  template <typename P>
  int energyOf(P& pet)
  {
      if constexpr (requires { { pet.getEnergy() } -> std::convertible_to<int>; })
      {
          return pet.getEnergy();
      }
      else
      {
          return 50;
      }
  }

  template <typename P>
  int happinessOf(P& pet)
  {
      if constexpr (requires { { pet.getHappiness() } -> std::convertible_to<int>; })
      {
          return pet.getHappiness();
      }
      else
      {
          return 50;
      }
  }

  template <typename P>
  int ageOf(P& pet)
  {
      if constexpr (requires { { pet.getAge() } -> std::convertible_to<int>; })
      {
          return pet.getAge();
      }
      else
      {
          return 0;
      }
  }

  template <typename P>
  std::string moodOf(P& pet)
  {
      if constexpr (requires { { pet.mood() } -> std::convertible_to<std::string>; })
      {
          return pet.mood();
      }
      else
      {
          return "?";
      }
  }

  template <typename P>
  bool aliveOf(P& pet)
  {
      if constexpr (requires { { pet.isAlive() } -> std::convertible_to<bool>; })
      {
          return pet.isAlive();
      }
      else
      {
          return true;
      }
  }

  template <typename P>
  std::string statusOf(P& pet)
  {
      if constexpr (requires { { pet.status() } -> std::convertible_to<std::string>; })
      {
          return pet.status();
      }
      else
      {
          return "(status() was not found in Pet.hpp)";
      }
  }

  // What happened when the game tried an action: was the function there, and did the pet agree?
  struct Outcome
  {
      bool found{false};
      bool ok{false};
  };

  template <typename P>
  Outcome feedPet(P& pet, int amount)
  {
      if constexpr (requires { { pet.feed(amount) } -> std::convertible_to<bool>; })
      {
          return {true, pet.feed(amount)};
      }
      else
      {
          return {false, false};
      }
  }

  template <typename P>
  Outcome playPet(P& pet)
  {
      if constexpr (requires { { pet.play() } -> std::convertible_to<bool>; })
      {
          return {true, pet.play()};
      }
      else
      {
          return {false, false};
      }
  }

  template <typename P>
  bool sleepPet(P& pet)
  {
      if constexpr (requires { pet.sleep(); })
      {
          pet.sleep();
          return true;
      }
      else
      {
          return false;
      }
  }

  template <typename P>
  bool tickPet(P& pet)
  {
      if constexpr (requires { pet.tick(); })
      {
          pet.tick();
          return true;
      }
      else
      {
          return false;
      }
  }

  template <typename P>
  int functionsFound(P& pet)
  {
      int found{0};
      if constexpr (requires { { pet.getName() } -> std::convertible_to<std::string>; }) ++found;
      if constexpr (requires { { pet.getFullness() } -> std::convertible_to<int>; }) ++found;
      if constexpr (requires { { pet.getEnergy() } -> std::convertible_to<int>; }) ++found;
      if constexpr (requires { { pet.getHappiness() } -> std::convertible_to<int>; }) ++found;
      if constexpr (requires { { pet.getAge() } -> std::convertible_to<int>; }) ++found;
      if constexpr (requires { { pet.feed(1) } -> std::convertible_to<bool>; }) ++found;
      if constexpr (requires { { pet.play() } -> std::convertible_to<bool>; }) ++found;
      if constexpr (requires { pet.sleep(); }) ++found;
      if constexpr (requires { pet.tick(); }) ++found;
      if constexpr (requires { { pet.mood() } -> std::convertible_to<std::string>; }) ++found;
      if constexpr (requires { { pet.isAlive() } -> std::convertible_to<bool>; }) ++found;
      if constexpr (requires { { pet.status() } -> std::convertible_to<std::string>; }) ++found;
      return found;
  }

  // =================================================================
  // Drawing
  // =================================================================

  // Lets older Windows consoles understand the screen-clearing codes.
  void enableAnsi()
  {
  #ifdef _WIN32
      HANDLE out{GetStdHandle(STD_OUTPUT_HANDLE)};
      DWORD mode{0};
      if (GetConsoleMode(out, &mode))
      {
          SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
      }
  #endif
  }

  void frameDelay()
  {
      if (std::getenv("PET_NO_DELAY") == nullptr)
      {
          std::this_thread::sleep_for(std::chrono::milliseconds(120));
      }
  }

  std::string bar(int value)
  {
      std::string result{"["};
      for (int i{0}; i < 10; ++i)
      {
          result += (i < value / 10) ? '#' : '-';
      }
      return result + "]";
  }

  std::string face(std::string mood, std::string action)
  {
      if (action == "sleep")
      {
          return "( -.- )";
      }
      if (action == "refuse")
      {
          return "( >.< )";
      }
      if (mood == "happy")
      {
          return "( ^.^ )";
      }
      if (mood == "hungry")
      {
          return "( o_o )";
      }
      if (mood == "tired")
      {
          return "( -.- )";
      }
      if (mood == "sad")
      {
          return "( ;.; )";
      }
      return "( o.o )";
  }

  std::vector<std::string> sprite(std::string mood, std::string action, int frame)
  {
      std::string ears{" /\\_/\\ "};
      std::string legs{(frame % 2 == 0) ? " > ^ < " : " >^ ^< "};
      if (action == "sleep")
      {
          legs = " >___< ";
      }
      return {ears, face(mood, action), legs};
  }

  // Writes text into the room at (row, col), ignoring anything outside it.
  void put(std::vector<std::string>& rows, int row, int col, std::string text)
  {
      if (row < 0 || row >= ROOM_HEIGHT)
      {
          return;
      }
      for (size_t i{0}; i < text.size(); ++i)
      {
          int c{col + static_cast<int>(i)};
          if (c >= 0 && c < ROOM_WIDTH)
          {
              rows.at(row).at(c) = text.at(i);
          }
      }
  }

  void drawFrame(Pet& pet, int x, int frame, std::string action, std::string caption)
  {
      std::cout << "\x1b[2J\x1b[H";
      std::cout << "  " << nameOf(pet) << "   day " << ageOf(pet) << "\n";
      std::string border{"  +" + std::string(ROOM_WIDTH, '-') + "+\n"};
      std::cout << border;

      std::vector<std::string> rows(ROOM_HEIGHT, std::string(ROOM_WIDTH, ' '));
      int top{ROOM_HEIGHT - 3};
      if (action == "sleep")
      {
          put(rows, top - 1 - (frame % 2), x + SPRITE_WIDTH, (frame % 2 == 0) ? "z" : "Z");
      }
      if (action == "eat")
      {
          put(rows, ROOM_HEIGHT - 1, x + SPRITE_WIDTH + 1, (frame < FRAMES_PER_ACTION / 2) ? "[::]" : "[  ]");
      }
      if (action == "play")
      {
          put(rows, ROOM_HEIGHT - 1 - (frame % 3), x + SPRITE_WIDTH + 2 + (frame % 4), "o");
      }
      std::vector<std::string> pet_rows{sprite(moodOf(pet), action, frame)};
      for (int i{0}; i < 3; ++i)
      {
          put(rows, top + i, x, pet_rows.at(i));
      }
      for (int r{0}; r < ROOM_HEIGHT; ++r)
      {
          std::cout << "  |" << rows.at(r) << "|\n";
      }
      std::cout << border;

      std::cout << "  fullness   " << bar(fullnessOf(pet)) << ' ' << fullnessOf(pet) << "\n";
      std::cout << "  energy     " << bar(energyOf(pet)) << ' ' << energyOf(pet) << "\n";
      std::cout << "  happiness  " << bar(happinessOf(pet)) << ' ' << happinessOf(pet) << "\n";
      std::cout << "  mood: " << moodOf(pet) << "\n";
      std::cout << "  your Pet class: " << functionsFound(pet) << " / " << FUNCTION_COUNT << " functions found\n\n";
      std::cout << "  " << caption << "\n\n";
  }

  // Plays a short animation. The pet walks unless it is asleep or refusing.
  void animate(Pet& pet, int& x, int& direction, std::string action, std::string caption)
  {
      for (int frame{0}; frame < FRAMES_PER_ACTION; ++frame)
      {
          if (action != "sleep" && action != "refuse")
          {
              x += direction;
              if (x <= 1 || x >= ROOM_WIDTH - SPRITE_WIDTH - 6)
              {
                  direction = -direction;
              }
          }
          drawFrame(pet, x, frame, action, caption);
          frameDelay();
      }
  }

  std::string missing(std::string name, std::string function, std::string wish)
  {
      return name + " would love to " + wish + ", but " + function + " was not found in Pet.hpp.";
  }

  // =================================================================
  // The game
  // =================================================================

  int main()
  {
      enableAnsi();
      std::cout << "What is your pet's name? ";
      std::string typed{};
      if (!(std::cin >> typed))
      {
          typed = "Mochi";
      }

      Pet pet{makePet<Pet>(typed)};
      std::string name{nameOf(pet)};
      int x{2};
      int direction{1};
      animate(pet, x, direction, "idle", name + " moves in. Commands: feed, play, sleep, wait, left, right, quit.");

      while (aliveOf(pet))
      {
          std::cout << "  Command: ";
          std::string command{};
          if (!(std::cin >> command) || command == "quit")
          {
              break;
          }

          std::string action{"idle"};
          std::string caption{};
          if (command == "feed")
          {
              Outcome result{feedPet(pet, 30)};
              if (!result.found)
              {
                  caption = missing(name, "feed()", "eat");
              }
              else if (result.ok)
              {
                  action = "eat";
                  caption = name + " munches happily. (+30 fullness)";
              }
              else
              {
                  action = "refuse";
                  caption = name + " is full and refuses to eat.";
              }
          }
          else if (command == "play")
          {
              Outcome result{playPet(pet)};
              if (!result.found)
              {
                  caption = missing(name, "play()", "play");
              }
              else if (result.ok)
              {
                  action = "play";
                  caption = name + " chases the ball! (+15 happiness, -20 energy, -10 fullness)";
              }
              else
              {
                  action = "refuse";
                  caption = name + " is too tired to play.";
              }
          }
          else if (command == "sleep")
          {
              if (sleepPet(pet))
              {
                  action = "sleep";
                  caption = name + " takes a nap. (+40 energy, -10 fullness)";
              }
              else
              {
                  caption = missing(name, "sleep()", "nap");
              }
          }
          else if (command == "wait")
          {
              if (tickPet(pet))
              {
                  caption = "A day passes. (-10 fullness, -5 energy, -5 happiness)";
              }
              else
              {
                  caption = "Time stands still: tick() was not found in Pet.hpp.";
              }
          }
          else if (command == "left")
          {
              direction = -1;
              caption = name + " trots to the left.";
          }
          else if (command == "right")
          {
              direction = 1;
              caption = name + " trots to the right.";
          }
          else
          {
              std::cout << "  Unknown command. Try feed, play, sleep, wait, left, right or quit.\n";
              continue;
          }

          animate(pet, x, direction, action, caption);
      }

      if (!aliveOf(pet))
      {
          drawFrame(pet, x, 0, "refuse", name + " got too hungry and ran away to find food.");
          std::cout << "  Game over after " << ageOf(pet) << " days.\n";
      }
      else
      {
          std::cout << "\n  " << statusOf(pet) << "\n  Goodbye!\n";
      }
      return 0;
  }
