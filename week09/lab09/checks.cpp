// checks.cpp
// Lab 08: Virtual Pet. PROVIDED. Do not edit.
//
// The grader. Switch on each group of checks once the functions it uses
// exist in your Pet class: delete the group's [GROUP n START] and
// [GROUP n END] lines, and un-comment its call in main.
//
// Build:  g++ -std=c++20 -Wall checks.cpp -o checks            (Pet.hpp only)
//         g++ -std=c++20 -Wall checks.cpp Pet.cpp -o checks    (Pet.hpp + Pet.cpp)
// Run:    ./checks        (Windows: .\checks.exe)

#include "Pet.hpp"

#include <iostream>
#include <string>

// Prints one PASS or FAIL line for a number (or a bool). Returns 1 or 0.
int check(std::string label, int got, int expected)
{
    if (got == expected)
    {
        std::cout << "[PASS] " << label << " -> " << got << '\n';
        return 1;
    }
    std::cout << "[FAIL] " << label << ": got " << got << ", expected " << expected << '\n';
    return 0;
}

// Prints one PASS or FAIL line for a string. Returns 1 or 0.
int check_text(std::string label, std::string got, std::string expected)
{
    if (got == expected)
    {
        std::cout << "[PASS] " << label << " -> \"" << got << "\"\n";
        return 1;
    }
    std::cout << "[FAIL] " << label << ": got \"" << got << "\", expected \"" << expected << "\"\n";
    return 0;
}

// [GROUP 1 START] delete this line and the [GROUP 1 END] line below to enable
int group_1()
{
    std::cout << "== Group 1: constructor and getters ==\n";
    int passed{0};
    Pet pet{"Mochi"};
    passed += check_text("getName()", pet.getName(), "Mochi");
    passed += check("getFullness() at the start", pet.getFullness(), 50);
    passed += check("getEnergy() at the start", pet.getEnergy(), 50);
    passed += check("getHappiness() at the start", pet.getHappiness(), 50);
    passed += check("getAge() at the start", pet.getAge(), 0);
    std::cout << "Group 1: " << passed << " / 5\n\n";
    return passed;
}
// [GROUP 1 END]

// [GROUP 2 START] delete this line and the [GROUP 2 END] line below to enable
int group_2()
{
    std::cout << "== Group 2: feed and rename ==\n";
    int passed{0};
    Pet pet{"Mochi"};
    passed += check("feed(30) returns true", pet.feed(30), true);
    passed += check("fullness after feed(30)", pet.getFullness(), 80);
    pet.feed(50);
    passed += check("fullness never goes above 100", pet.getFullness(), 100);
    passed += check("feed(10) when already full returns false", pet.feed(10), false);
    passed += check("rename(\"\") returns false", pet.rename(""), false);
    pet.rename("Bean");
    passed += check_text("getName() after rename(\"Bean\")", pet.getName(), "Bean");
    std::cout << "Group 2: " << passed << " / 6\n\n";
    return passed;
}
// [GROUP 2 END]

// [GROUP 3 START] delete this line and the [GROUP 3 END] line below to enable
int group_3()
{
    std::cout << "== Group 3: play and sleep ==\n";
    int passed{0};
    Pet pet{"Mochi"};
    passed += check("play() with 50 energy returns true", pet.play(), true);
    passed += check("happiness after play()", pet.getHappiness(), 65);
    pet.play();
    passed += check("energy after two play()", pet.getEnergy(), 10);
    passed += check("play() with 10 energy returns false", pet.play(), false);
    pet.sleep();
    passed += check("energy after sleep()", pet.getEnergy(), 50);
    passed += check("fullness after two play() and sleep()", pet.getFullness(), 20);
    std::cout << "Group 3: " << passed << " / 6\n\n";
    return passed;
}
// [GROUP 3 END]

// [GROUP 4 START] delete this line and the [GROUP 4 END] line below to enable
int group_4()
{
    std::cout << "== Group 4: tick and isAlive ==\n";
    int passed{0};
    Pet pet{"Mochi"};
    passed += check("isAlive() at the start", pet.isAlive(), true);
    pet.tick();
    passed += check("fullness after tick()", pet.getFullness(), 40);
    passed += check("energy after tick()", pet.getEnergy(), 45);
    passed += check("getAge() after tick()", pet.getAge(), 1);
    for (int i{0}; i < 9; ++i)
    {
        pet.tick();
    }
    passed += check("fullness never goes below 0", pet.getFullness(), 0);
    passed += check("isAlive() with 0 fullness", pet.isAlive(), false);
    std::cout << "Group 4: " << passed << " / 6\n\n";
    return passed;
}
// [GROUP 4 END]

// [GROUP 5 START] delete this line and the [GROUP 5 END] line below to enable
int group_5()
{
    std::cout << "== Group 5: mood and status ==\n";
    int passed{0};
    Pet fresh{"Mochi"};
    passed += check_text("status() at the start", fresh.status(), "Mochi | fullness 50 energy 50 happiness 50 | okay");

    Pet happy{"Mochi"};
    happy.play();
    happy.play();
    happy.sleep();
    happy.feed(30);
    passed += check_text("mood() with happiness 80 and the rest fine", happy.mood(), "happy");

    Pet hungry{"Mochi"};
    hungry.tick();
    hungry.tick();
    hungry.tick();
    passed += check_text("mood() with fullness 20", hungry.mood(), "hungry");

    Pet tired{"Mochi"};
    tired.play();
    tired.play();
    passed += check_text("mood() with energy 10 and happiness 80: tired wins", tired.mood(), "tired");

    Pet sad{"Mochi"};
    sad.sleep();
    sad.feed(60);
    for (int i{0}; i < 5; ++i)
    {
        sad.tick();
    }
    passed += check_text("mood() with happiness 25 and the rest fine", sad.mood(), "sad");
    std::cout << "Group 5: " << passed << " / 5\n\n";
    return passed;
}
// [GROUP 5 END] 

int main()
{
    int total{0};
    // Un-comment each call together with its group above.
    total += group_1();
    total += group_2();
    total += group_3();
    total += group_4();
    total += group_5();
    std::cout << "Pet: " << total << " / 28 checks passed\n";
    return 0;
}
