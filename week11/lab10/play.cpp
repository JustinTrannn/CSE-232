// play.cpp
// Lab 10: The Puppet Show. PROVIDED. Do not edit.
//
// The stage. It runs before you have written anything, and it does more as
// your classes grow: every function it finds in Puppeteer.hpp and
// Narrator.hpp makes another command work, and the screen counts them.
//
// Build:  g++ -std=c++20 -Wall play.cpp -o play                    (no Puppeteer.hpp yet)
//         g++ -std=c++20 -Wall play.cpp Puppeteer.cpp -o play      (once Puppeteer.cpp exists)
// Run:    ./play          (Windows: .\play.exe)

#include "Puppet.hpp"

class Puppeteer;    // yours, in Puppeteer.hpp
class Narrator;     // yours, in Narrator.hpp

#if __has_include("Puppeteer.hpp")
#include "Puppeteer.hpp"
const bool PUPPETEER_FILE{true};
#else
const bool PUPPETEER_FILE{false};
#endif

#if __has_include("Narrator.hpp")
#include "Narrator.hpp"
const bool NARRATOR_FILE{true};
#else
const bool NARRATOR_FILE{false};
#endif

#include <array>
#include <cctype>
#include <concepts>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

const int SCREEN_WIDTH{76};     // characters across the screen
const int COLUMN_WIDTH{24};     // one puppet's part of the stage
const int FUNCTION_COUNT{10};   // the functions the stage looks for

// =================================================================
// Finding your classes and functions.
// The stage asks the compiler whether each class and function it needs
// exists, with the right parameters and return type. If it does, the stage
// calls it. If not, the command says what is missing. You do not need to
// understand how this part works; it is well beyond this course.
// =================================================================

template <typename P>
concept PuppeteerReady = requires(std::string name) { P{name}; };
template <typename N>
concept NarratorTakesACopy = requires { N{std::declval<Puppet>()}; };
template <typename N>
concept NarratorReady = requires(Puppet& star) { N{star}; } && !NarratorTakesACopy<N>;

struct NoPuppeteer
{
};
struct NoNarrator
{
};

// Your class once it is ready, and a stand-in until then.
using Hand = std::conditional_t<PuppeteerReady<Puppeteer>, Puppeteer, NoPuppeteer>;
using Voice = std::conditional_t<NarratorReady<Narrator>, Narrator, NoNarrator>;

template <typename H>
concept HasGetName = requires(H h) { { h.getName() } -> std::convertible_to<std::string>; };
template <typename H>
concept GrabsACopy = requires(H h) { h.grab(std::declval<Puppet>()); };
template <typename H>
concept CanGrab = requires(H h, Puppet& puppet) { h.grab(puppet); } && !GrabsACopy<H>;
template <typename H>
concept CanLetGo = requires(H h) { h.letGo(); };
template <typename H>
concept CanGetPuppet = requires(H h) { { h.getPuppet() } -> std::convertible_to<Puppet*>; };
template <typename H>
concept CanPerform = requires(H h, std::string pose) { { h.perform(pose) } -> std::convertible_to<bool>; };
template <typename H>
concept PassesACopy = requires(H h) { h.passTo(std::declval<H>()); };
template <typename H>
concept CanPassTo = requires(H h, H& other) { { h.passTo(other) } -> std::convertible_to<bool>; } && !PassesACopy<H>;
template <typename H>
concept TradesACopy = requires(H h) { h.trade(std::declval<H>()); };
template <typename H>
concept CanTrade = requires(H h, H& other) { h.trade(other); } && !TradesACopy<H>;

template <typename N>
concept HasStarName = requires(N n) { { n.getStarName() } -> std::convertible_to<std::string>; };
template <typename N>
concept CanCue = requires(N n, std::string pose) { n.cue(pose); };
template <typename N>
concept CanGetStar = requires(N n) { { n.getStar() } -> std::same_as<Puppet&>; };

const char* running{""};    // the function of yours that the stage is calling right now

// Runs when the program is stopped for touching memory it does not own,
// which is what happens when a function follows a nullptr.
void crashed(int)
{
    std::cout << "\n\n  CRASH! The show was stopped while your " << running << "() was running.\n"
                 "  The bug is in " << running << "() or in a function of yours that it calls.\n"
                 "  A function used -> on a pointer that was nullptr, or that held the\n"
                 "  address of a puppet that no longer exists. Remember that a puppeteer's\n"
                 "  hands can be empty (nullptr). Test a pointer before you follow it.\n\n"
              << std::flush;
    std::_Exit(1);
}

template <typename H>
std::string callGetName(H& h, std::string fallback)
{
    if constexpr (HasGetName<H>)
    {
        running = "getName";
        return h.getName();
    }
    else
    {
        return fallback;
    }
}

template <typename H>
void callGrab(H& h, Puppet& puppet)
{
    if constexpr (CanGrab<H>)
    {
        running = "grab";
        h.grab(puppet);
    }
}

template <typename H>
void callLetGo(H& h)
{
    if constexpr (CanLetGo<H>)
    {
        running = "letGo";
        h.letGo();
    }
}

template <typename H>
Puppet* callGetPuppet(H& h)
{
    if constexpr (CanGetPuppet<H>)
    {
        running = "getPuppet";
        return h.getPuppet();
    }
    else
    {
        return nullptr;
    }
}

template <typename H>
bool callPerform(H& h, std::string pose)
{
    if constexpr (CanPerform<H>)
    {
        running = "perform";
        return h.perform(pose);
    }
    else
    {
        return false;
    }
}

template <typename H>
bool callPassTo(H& h, H& other)
{
    if constexpr (CanPassTo<H>)
    {
        running = "passTo";
        return h.passTo(other);
    }
    else
    {
        return false;
    }
}

template <typename H>
void callTrade(H& h, H& other)
{
    if constexpr (CanTrade<H>)
    {
        running = "trade";
        h.trade(other);
    }
}

template <typename N>
std::string callGetStarName(N& n)
{
    if constexpr (HasStarName<N>)
    {
        running = "getStarName";
        return n.getStarName();
    }
    else
    {
        return "?";
    }
}

template <typename N>
void callCue(N& n, std::string pose)
{
    if constexpr (CanCue<N>)
    {
        running = "cue";
        n.cue(pose);
    }
}

template <typename H>
void buildTroupe(std::vector<H>& troupe, std::array<std::string, 3> names)
{
    troupe.clear();
    if constexpr (PuppeteerReady<H>)
    {
        for (std::string name : names)
        {
            running = "Puppeteer constructor";
            troupe.emplace_back(name);
        }
    }
}

template <typename N>
void buildNarrator(std::optional<N>& narrator, Puppet& star)
{
    if constexpr (NarratorReady<N>)
    {
        running = "Narrator constructor";
        narrator.emplace(star);
    }
}

int functionsFound()
{
    std::array<bool, FUNCTION_COUNT> found{HasGetName<Hand>, CanGrab<Hand>, CanLetGo<Hand>, CanGetPuppet<Hand>, CanPerform<Hand>,
                                           CanPassTo<Hand>, CanTrade<Hand>, HasStarName<Voice>, CanCue<Voice>, CanGetStar<Voice>};
    int count{0};
    for (bool yes : found)
    {
        if (yes)
        {
            ++count;
        }
    }
    return count;
}

// =================================================================
// The stage
// =================================================================

const std::array<std::string, 3> PUPPETEER_NAMES{"Ana", "Raj", "Lee"};
const std::array<std::string, 3> PUPPET_NAMES{"Pip", "Kit", "Bo"};
const std::array<std::string, 6> POSES{"stand", "wave", "cheer", "bow", "sit", "jump"};

std::array<Puppet, 3> puppets{Puppet{"Pip"}, Puppet{"Kit"}, Puppet{"Bo"}};
std::vector<Hand> troupe{};
std::optional<Voice> narrator{};
int scenesDone{0};

// What a puppeteer holds, as a number: 0, 1 or 2 for a puppet, or one of these.
const int EMPTY{-1};        // nullptr
const int UNKNOWN{-2};      // getPuppet() is not written yet
const int STRANGE{-3};      // an address that is none of the puppets on the stage

int heldBy(int who)
{
    if (!CanGetPuppet<Hand> || troupe.empty())
    {
        return UNKNOWN;
    }
    Puppet* held{callGetPuppet(troupe.at(who))};
    if (held == nullptr)
    {
        return EMPTY;
    }
    for (int i{0}; i < 3; ++i)
    {
        if (held == &puppets.at(i))
        {
            return i;
        }
    }
    return STRANGE;
}

std::string heldText(int held)
{
    if (held >= 0)
    {
        return PUPPET_NAMES.at(held);
    }
    if (held == EMPTY)
    {
        return "empty hands";
    }
    if (held == STRANGE)
    {
        return "an address that is no puppet on the stage";
    }
    return "?";
}

std::string who(int index)
{
    if (troupe.empty())
    {
        return PUPPETEER_NAMES.at(index);
    }
    return callGetName(troupe.at(index), PUPPETEER_NAMES.at(index));
}

struct Scene
{
    std::string text;
    std::string hint;
};

const std::array<Scene, 5> SCENES{{
    {"Kit waves to the audience.", "ana grab kit,  then  ana wave"},
    {"Raj grabs Kit too: two puppeteers, one puppet. Raj makes Kit jump.", "raj grab kit,  then  raj jump"},
    {"Ana lets go. Raj passes Kit to Lee, and Lee makes Kit sit.", "ana let go,  raj pass lee,  lee sit"},
    {"Ana picks up Bo. Ana and Lee trade puppets, and both puppets cheer.", "ana grab bo,  ana trade lee,  ana cheer,  lee cheer"},
    {"The narrator cues the star: Pip bows, and nobody holds Pip.", "narrator bow"},
}};

bool sceneDone(int scene)
{
    std::array<int, 3> held{heldBy(0), heldBy(1), heldBy(2)};
    std::string pip{puppets.at(0).getPose()};
    std::string kit{puppets.at(1).getPose()};
    std::string bo{puppets.at(2).getPose()};
    switch (scene)
    {
    case 0:
        return kit == "wave";
    case 1:
        return held.at(0) == 1 && held.at(1) == 1 && kit == "jump";
    case 2:
        return held.at(2) == 1 && held.at(0) == EMPTY && held.at(1) == EMPTY && kit == "sit";
    case 3:
        return held.at(0) == 1 && held.at(2) == 2 && kit == "cheer" && bo == "cheer";
    case 4:
        for (int h : held)
        {
            if (h == 0 || h == UNKNOWN)
            {
                return false;
            }
        }
        return pip == "bow";
    }
    return false;
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

// One puppet, 7 characters wide and 4 rows high.
std::array<std::string, 4> figure(std::string pose)
{
    if (pose == "wave")
    {
        return {"       ", "   o/  ", "  /|   ", "  / \\  "};
    }
    if (pose == "cheer")
    {
        return {"       ", "  \\o/  ", "   |   ", "  / \\  "};
    }
    if (pose == "bow")
    {
        return {"       ", "       ", "  o__  ", "  / |\\ "};
    }
    if (pose == "sit")
    {
        return {"       ", "       ", "   o   ", "  /|\\_ "};
    }
    if (pose == "jump")
    {
        return {"  \\o/  ", "   |   ", "  / \\  ", "       "};
    }
    return {"       ", "   o   ", "  /|\\  ", "  / \\  "};
}

// Writes text into the picture at (row, col), ignoring anything outside it.
void put(std::vector<std::string>& rows, int row, int col, std::string text)
{
    for (std::size_t i{0}; i < text.size(); ++i)
    {
        int c{col + static_cast<int>(i)};
        if (row >= 0 && row < static_cast<int>(rows.size()) && c >= 0 && c < SCREEN_WIDTH)
        {
            rows.at(row).at(c) = text.at(i);
        }
    }
}

// Breaks a long message into lines that fit the screen.
std::string wrap(std::string text)
{
    std::string result{};
    std::string line{"  "};
    std::string word{};
    text += ' ';
    for (char c : text)
    {
        if (c == ' ' || c == '\n')
        {
            if (line.size() + word.size() > static_cast<std::size_t>(SCREEN_WIDTH) && line.size() > 2)
            {
                result += line + "\n";
                line = "  ";
            }
            line += word + ' ';
            word = "";
            if (c == '\n')
            {
                result += line + "\n";
                line = "  ";
            }
        }
        else
        {
            word += c;
        }
    }
    return result + line + "\n";
}

void drawScreen(std::string message)
{
    const std::string rule{"  " + std::string(SCREEN_WIDTH - 4, '-') + "\n"};
    std::cout << "\x1b[2J\x1b[H";
    std::cout << "  THE PUPPET SHOW" << std::string(10, ' ') << "your files: " << functionsFound() << " / " << FUNCTION_COUNT << " functions found";
    std::cout << "\n" << rule;
    if (scenesDone < static_cast<int>(SCENES.size()))
    {
        std::cout << "  scene " << (scenesDone + 1) << " of " << SCENES.size() << ":  " << SCENES.at(scenesDone).text << "\n";
        std::cout << "  try:         " << SCENES.at(scenesDone).hint << "\n";
    }
    else
    {
        std::cout << "  Encore! Every scene is played. The stage is yours.\n\n";
    }

    // The stage: names of the hands on each puppet, the strings, the
    // puppet, its name.
    std::vector<std::string> rows(9, std::string(SCREEN_WIDTH, ' '));
    std::array<int, 3> held{heldBy(0), heldBy(1), heldBy(2)};
    for (int p{0}; p < 3; ++p)
    {
        int left{2 + p * COLUMN_WIDTH};
        std::array<std::string, 4> shape{figure(puppets.at(p).getPose())};
        int top{3};
        for (int r{0}; r < 4; ++r)
        {
            put(rows, top + r, left + 8, shape.at(r));
        }

        std::string hands{};
        for (int w{0}; w < 3; ++w)
        {
            if (held.at(w) == p)
            {
                hands += (hands.empty() ? "" : " & ") + who(w);
            }
        }
        if (!hands.empty())
        {
            int head{0};
            while (shape.at(head).find('o') == std::string::npos)
            {
                ++head;
            }
            int headColumn{left + 8 + static_cast<int>(shape.at(head).find('o'))};
            put(rows, 0, headColumn - static_cast<int>(hands.size()) / 2, hands);
            for (int r{1}; r < top + head; ++r)
            {
                put(rows, r, headColumn, "|");
            }
        }
        std::string name{puppets.at(p).getName()};
        put(rows, 7, left + 11 - static_cast<int>(name.size()) / 2, name);
        if (p == 0 && narrator.has_value())
        {
            put(rows, 8, left + 3, "(narrator's star)");
        }
    }
    std::cout << "\n";
    for (const std::string& row : rows)
    {
        std::cout << row << "\n";
    }

    std::cout << rule;
    if (troupe.empty())
    {
        std::cout << "  hands:   the puppeteers are waiting backstage for their class.\n";
    }
    else
    {
        std::cout << "  hands:  ";
        for (int w{0}; w < 3; ++w)
        {
            std::cout << "  " << who(w) << ": " << heldText(held.at(w)) << "  ";
        }
        std::cout << "\n";
    }
    std::cout << rule;
    if (message.find('\n') == std::string::npos)
    {
        std::cout << wrap(message);
    }
    else
    {
        std::cout << "  " << message << "\n";     // already laid out in lines, like the help
    }
}

// =================================================================
// Commands
// =================================================================

std::string missing(std::string function)
{
    if (!PUPPETEER_FILE)
    {
        return "Puppeteer.hpp was not found. The puppeteers come to life in Milestone 1.";
    }
    if (troupe.empty())
    {
        return "Puppeteer.hpp has no class Puppeteer with a constructor that takes a std::string yet.";
    }
    if (function == "grab" && GrabsACopy<Hand>)
    {
        return "grab() takes a copy of the puppet: its parameter is a Puppet, not a Puppet&. The hand would "
               "hold the address of the copy, which is gone as soon as grab() ends.";
    }
    if (function == "passTo" && PassesACopy<Hand>)
    {
        return "passTo() takes a copy of the other puppeteer, so the real one would never get the puppet. "
               "Its parameter must be a Puppeteer&.";
    }
    if (function == "trade" && TradesACopy<Hand>)
    {
        return "trade() takes a copy of the other puppeteer, so the real one would never get your puppet. "
               "Its parameter must be a Puppeteer&.";
    }
    return function + "() was not found in Puppeteer.hpp (or its parameters or return type differ from the guide).";
}

std::string narratorMissing()
{
    if (!NARRATOR_FILE)
    {
        return "Narrator.hpp was not found. The narrator comes in Milestone 2.";
    }
    if (NarratorTakesACopy<Narrator>)
    {
        return "The Narrator constructor takes a copy of the puppet, so the narrator would be bound to a copy "
               "that is gone as soon as the constructor ends. Its parameter must be a Puppet&.";
    }
    return "Narrator.hpp has no class Narrator with a constructor that takes a Puppet& yet.";
}

std::string commandGrab(int w, int p)
{
    if (!CanGrab<Hand>)
    {
        return missing("grab");
    }
    callGrab(troupe.at(w), puppets.at(p));
    std::string text{who(w) + " grabs " + PUPPET_NAMES.at(p) + "."};
    int now{heldBy(w)};
    if (now != UNKNOWN && now != p)
    {
        text += " But afterwards getPuppet() gives " + heldText(now) + ", not the address of " + PUPPET_NAMES.at(p) +
                ". grab() has to keep the address of the puppet it was handed.";
    }
    else if (now == UNKNOWN)
    {
        text += " (getPuppet() is not written yet, so the stage cannot show whose hands hold what.)";
    }
    return text;
}

std::string commandLetGo(int w)
{
    if (!CanLetGo<Hand>)
    {
        return missing("letGo");
    }
    callLetGo(troupe.at(w));
    int now{heldBy(w)};
    if (now != EMPTY && now != UNKNOWN)
    {
        return who(w) + " let go, but getPuppet() still gives " + heldText(now) + ". letGo() has to empty the hands: nullptr.";
    }
    return who(w) + "'s hands are empty.";
}

std::string commandPose(int w, std::string pose)
{
    if (!CanPerform<Hand>)
    {
        return missing("perform");
    }
    int before{heldBy(w)};
    bool moved{callPerform(troupe.at(w), pose)};
    if (before >= 0)
    {
        std::string name{PUPPET_NAMES.at(before)};
        if (!moved)
        {
            return "perform() returned false, but " + who(w) + " holds " + name + ".";
        }
        if (puppets.at(before).getPose() != pose)
        {
            return "perform() returned true, but " + name + " did not move. Did perform() change the puppet the hand points to?";
        }
        return who(w) + " makes " + name + " " + pose + ".";
    }
    if (before == EMPTY)
    {
        if (moved)
        {
            return "perform() returned true, but " + who(w) + "'s hands are empty.";
        }
        return who(w) + "'s hands are empty: nothing moves, and perform() returned false.";
    }
    return std::string{"perform() returned "} + (moved ? "true" : "false") + ".";
}

std::string commandPass(int w, int to)
{
    if (!CanPassTo<Hand>)
    {
        return missing("passTo");
    }
    int a{heldBy(w)};
    int b{heldBy(to)};
    bool ok{callPassTo(troupe.at(w), troupe.at(to))};
    if (a == UNKNOWN)
    {
        return std::string{"passTo() returned "} + (ok ? "true" : "false") + ". (Without getPuppet() the stage cannot show more.)";
    }
    int a2{heldBy(w)};
    int b2{heldBy(to)};
    std::string result{std::string{"passTo() returned "} + (ok ? "true" : "false") + "; now " + who(w) + ": " + heldText(a2) +
                       ", " + who(to) + ": " + heldText(b2) + "."};
    if (w == to || a == EMPTY || b != EMPTY)
    {
        std::string reason{w == to ? "a puppeteer cannot pass to themselves"
                           : a == EMPTY ? who(w) + "'s hands are empty"
                                        : who(to) + "'s hands are full"};
        if (!ok && a2 == a && b2 == b)
        {
            return "Nothing is passed: " + reason + ". passTo() returned false.";
        }
        return "Nothing should be passed (" + reason + "), and passTo() should return false. But " + result;
    }
    if (ok && a2 == EMPTY && b2 == a)
    {
        return who(w) + " passes " + heldText(a) + " to " + who(to) + ".";
    }
    return who(w) + " should now have empty hands, " + who(to) + " should hold " + heldText(a) +
           ", and passTo() should return true. But " + result;
}

std::string commandTrade(int w, int to)
{
    if (!CanTrade<Hand>)
    {
        return missing("trade");
    }
    int a{heldBy(w)};
    int b{heldBy(to)};
    callTrade(troupe.at(w), troupe.at(to));
    if (a == UNKNOWN)
    {
        return "trade() ran. (Without getPuppet() the stage cannot show more.)";
    }
    int a2{heldBy(w)};
    int b2{heldBy(to)};
    if (a2 == b && b2 == a)
    {
        return who(w) + " and " + who(to) + " trade: " + who(w) + ": " + heldText(a2) + ", " + who(to) + ": " + heldText(b2) + ".";
    }
    return "After trade(), " + who(w) + ": " + heldText(a2) + " and " + who(to) + ": " + heldText(b2) + ". They should have swapped, to " +
           who(w) + ": " + heldText(b) + " and " + who(to) + ": " + heldText(a) + ".";
}

std::string commandNarrator(std::string pose)
{
    if (!narrator.has_value())
    {
        return narratorMissing();
    }
    if (pose.empty())
    {
        if (!HasStarName<Voice>)
        {
            return "getStarName() was not found in Narrator.hpp (or its return type differs from the guide).";
        }
        return "The narrator's star is " + callGetStarName(*narrator) +
               ". The narrator holds a Puppet&: it was bound to its star when it was made, and nothing can bind it to another puppet.";
    }
    if (!CanCue<Voice>)
    {
        return "cue() was not found in Narrator.hpp (or its parameters differ from the guide).";
    }
    callCue(*narrator, pose);
    if (puppets.at(0).getPose() != pose)
    {
        return "cue() ran, but Pip did not move. Is the narrator's star a Puppet&, or a copy of Pip?";
    }
    return "The narrator cues the star: Pip " + pose + "s.";
}

void resetStage()
{
    puppets = {Puppet{"Pip"}, Puppet{"Kit"}, Puppet{"Bo"}};     // the same three puppets, standing again
    buildTroupe(troupe, PUPPETEER_NAMES);
}

const std::string HELP_TEXT{
    "Commands (ana, raj or lee; pip, kit or bo):\n"
    "  ana grab kit      grab                 ana let go       letGo\n"
    "  ana wave          perform              ana pass lee     passTo\n"
    "  ana trade lee     trade                narrator bow     cue (Milestone 2)\n"
    "  poses: stand wave cheer bow sit jump   reset, help, quit"};

int indexOf(std::string word, std::array<std::string, 3> names)
{
    for (int i{0}; i < 3; ++i)
    {
        std::string lower{names.at(i)};
        lower.at(0) = static_cast<char>(std::tolower(static_cast<unsigned char>(lower.at(0))));
        if (word == lower)
        {
            return i;
        }
    }
    return -1;
}

bool isPose(std::string word)
{
    for (const std::string& pose : POSES)
    {
        if (word == pose)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::string> split(std::string line)
{
    std::vector<std::string> words{};
    std::string word{};
    line += ' ';
    for (char c : line)
    {
        if (c == ' ' || c == '\t' || c == '\r')
        {
            if (!word.empty())
            {
                words.push_back(word);
            }
            word = "";
        }
        else
        {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    return words;
}

std::string puppeteerCommand(std::vector<std::string> words)
{
    int w{indexOf(words.at(0), PUPPETEER_NAMES)};
    if (troupe.empty())
    {
        return missing("");
    }
    if (words.size() == 3 && words.at(1) == "grab" && indexOf(words.at(2), PUPPET_NAMES) >= 0)
    {
        return commandGrab(w, indexOf(words.at(2), PUPPET_NAMES));
    }
    if ((words.size() == 3 && words.at(1) == "let" && words.at(2) == "go") || (words.size() == 2 && (words.at(1) == "letgo" || words.at(1) == "drop")))
    {
        return commandLetGo(w);
    }
    if (words.size() == 3 && words.at(1) == "pass" && indexOf(words.at(2), PUPPETEER_NAMES) >= 0)
    {
        return commandPass(w, indexOf(words.at(2), PUPPETEER_NAMES));
    }
    if (words.size() == 3 && words.at(1) == "trade" && indexOf(words.at(2), PUPPETEER_NAMES) >= 0)
    {
        return commandTrade(w, indexOf(words.at(2), PUPPETEER_NAMES));
    }
    if (words.size() == 2 && isPose(words.at(1)))
    {
        return commandPose(w, words.at(1));
    }
    return "Try for example:  " + words.at(0) + " grab kit,  " + words.at(0) + " wave,  " + words.at(0) + " let go,  " + words.at(0) +
           " pass lee,  " + words.at(0) + " trade raj.";
}

int main()
{
    enableAnsi();
    std::signal(SIGSEGV, crashed);
    buildTroupe(troupe, PUPPETEER_NAMES);
    buildNarrator(narrator, puppets.at(0));
    std::string message{"The curtain is up. Type help for the list of commands."};
    while (true)
    {
        drawScreen(message);
        std::cout << "  Command: ";
        std::string line{};
        if (!std::getline(std::cin, line))
        {
            break;
        }
        std::vector<std::string> words{split(line)};
        if (words.empty())
        {
            message = "Type help for the list of commands.";
            continue;
        }
        if (words.at(0) == "quit")
        {
            break;
        }
        if (words.at(0) == "help")
        {
            message = HELP_TEXT;
            continue;
        }
        if (indexOf(words.at(0), PUPPETEER_NAMES) >= 0)
        {
            message = puppeteerCommand(words);
        }
        else if (words.at(0) == "narrator" && words.size() == 1)
        {
            message = commandNarrator("");
        }
        else if (words.at(0) == "narrator" && words.size() == 2 && isPose(words.at(1)))
        {
            message = commandNarrator(words.at(1));
        }
        else if (words.at(0) == "reset" && words.size() == 1)
        {
            resetStage();
            message = "The stage is reset: every puppet stands, and every hand is empty.";
        }
        else
        {
            message = "That is not a command. Type help for the list of commands.";
            continue;
        }
        if (scenesDone < static_cast<int>(SCENES.size()) && sceneDone(scenesDone))
        {
            ++scenesDone;
            message += scenesDone < static_cast<int>(SCENES.size()) ? "  Scene " + std::to_string(scenesDone) + ": applause!"
                                                                    : "  That was the last scene. Bravo!";
        }
    }
    std::cout << "\n  The curtain falls. Goodbye!\n";
    return 0;
}
