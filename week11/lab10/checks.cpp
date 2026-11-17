// checks.cpp
// Lab 10: The Puppet Show. PROVIDED. Do not edit.
//
// The grader. Switch on each group of checks once the functions it uses
// exist: delete the group's [GROUP n START] and [GROUP n END] lines, and
// un-comment its call in main.
//
// Build:  g++ -std=c++20 -Wall checks.cpp Puppeteer.cpp -o checks
// Run:    ./checks        (Windows: .\checks.exe)

#include "Puppet.hpp"
#include "Puppeteer.hpp"

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// =================================================================
// PROVIDED: check utilities.
// =================================================================

// Runs when the program is stopped for touching memory it does not own,
// which is what happens when a function follows a nullptr.
void crashed(int)
{
    std::cout << "\n[CRASH] The program was stopped during the check that comes right after the\n"
                 "        last line printed above. One of your functions used -> on a pointer\n"
                 "        that was nullptr, or that held the address of a puppet that no longer\n"
                 "        exists. Which pointer can be nullptr there? Test it before you follow it.\n"
                 "        The tallies are not printed after a crash. To see them, comment out\n"
                 "        the call of the group that crashed in main again, and rebuild.\n";
    std::_Exit(1);
}

// True when grab accepts a temporary puppet, which a Puppet& parameter
// never does: then grab works on a copy of the caller's puppet.
template <typename P>
concept GrabsACopy = requires(P puppeteer) { puppeteer.grab(std::declval<Puppet>()); };

// True when the Narrator constructor accepts a temporary puppet: then it
// works on a copy of the caller's puppet.
template <typename N>
concept NarratorTakesACopy = requires { N{std::declval<Puppet>()}; };

// True when passTo accepts a temporary puppeteer: then it works on a copy
// of the other puppeteer.
template <typename P>
concept PassesACopy = requires(P puppeteer) { puppeteer.passTo(std::declval<P>()); };

// Prints one PASS or FAIL line for something that should be true. Returns 1 or 0.
int checkYes(std::string label, bool ok)
{
    if (ok)
    {
        std::cout << "[PASS] " << label << " -> yes\n";
        return 1;
    }
    std::cout << "[FAIL] " << label << ": no\n";
    return 0;
}

// Prints one PASS or FAIL line for a string. Returns 1 or 0.
int checkText(std::string label, std::string got, std::string expected)
{
    if (got == expected)
    {
        std::cout << "[PASS] " << label << " -> " << got << '\n';
        return 1;
    }
    std::cout << "[FAIL] " << label << ": got " << got << ", expected " << expected << '\n';
    return 0;
}

// What a pointer to a puppet holds, in words: "the address of Kit",
// "nullptr", or an address that belongs to none of the puppets in cast.
std::string puppetText(Puppet* puppet, std::vector<Puppet*> cast)
{
    if (puppet == nullptr)
    {
        return "nullptr";
    }
    for (Puppet* known : cast)
    {
        if (puppet == known)
        {
            return "the address of " + known->getName();
        }
    }
    return "an address that is none of the puppets here (a copy of one?)";
}

// Prints one PASS or FAIL line for a pointer to a puppet: it passes only
// when the two pointers hold the same address. Returns 1 or 0.
int checkHand(std::string label, Puppet* got, Puppet* expected, std::vector<Puppet*> cast)
{
    if (got == expected)
    {
        std::cout << "[PASS] " << label << " -> " << puppetText(got, cast) << '\n';
        return 1;
    }
    std::cout << "[FAIL] " << label << ": got " << puppetText(got, cast) << ", expected " << puppetText(expected, cast) << '\n';
    return 0;
}

// Who holds what, for example "Ana: Kit, Raj: Bo, Lee: empty hands".
template <typename P>
std::string handsText(std::vector<P*> troupe, std::vector<Puppet*> cast)
{
    std::string text{};
    for (P* puppeteer : troupe)
    {
        std::string what{"?"};
        Puppet* held{puppeteer->getPuppet()};
        if (held == nullptr)
        {
            what = "empty hands";
        }
        for (Puppet* known : cast)
        {
            if (held == known)
            {
                what = known->getName();
            }
        }
        text += (text.empty() ? "" : ", ") + puppeteer->getName() + ": " + what;
    }
    return text;
}

// =================================================================
// CHECKS. Once a group's functions exist, delete its [GROUP n START]
// and [GROUP n END] lines and un-comment its call in main.
// =================================================================

// [GROUP 1 START] delete this line and the [GROUP 1 END] line below to enable
int group_1()
{
    std::cout << "== Group 1: the constructor, getName, grab and getPuppet ==\n";
    if (GrabsACopy<Puppeteer>)
    {
        std::cout << "[FAIL] grab takes a Puppet&: no. It accepts a temporary puppet, so its parameter\n"
                     "       is a copy, and the hand would hold the address of a copy that is gone\n"
                     "       as soon as grab ends.\n";
        std::cout << "Group 1: 0 / 5 (the other checks wait until grab takes a Puppet&)\n\n";
        return 0;
    }
    int passed{checkYes("grab takes a Puppet&, not a copy", true)};
    Puppet kit{"Kit"};
    Puppet bo{"Bo"};
    std::vector<Puppet*> cast{&kit, &bo};
    Puppeteer ana{"Ana"};
    passed += checkText("ana.getName()", ana.getName(), "Ana");
    passed += checkHand("a new puppeteer: ana.getPuppet()", ana.getPuppet(), nullptr, cast);
    ana.grab(kit);
    passed += checkHand("after ana.grab(kit): ana.getPuppet()", ana.getPuppet(), &kit, cast);
    ana.grab(bo);
    passed += checkHand("after ana.grab(bo), a second grab: ana.getPuppet()", ana.getPuppet(), &bo, cast);
    std::cout << "Group 1: " << passed << " / 5\n\n";
    return passed;
}
// [GROUP 1 END]

// [GROUP 2 START] delete this line and the [GROUP 2 END] line below to enable
int group_2()
{
    std::cout << "== Group 2: perform and letGo ==\n";
    if (GrabsACopy<Puppeteer>)
    {
        std::cout << "Group 2: 0 / 5 (skipped until grab takes a Puppet&: see Group 1)\n\n";
        return 0;
    }
    int passed{0};
    Puppet kit{"Kit"};
    std::vector<Puppet*> cast{&kit};
    Puppeteer ana{"Ana"};
    Puppeteer raj{"Raj"};
    ana.grab(kit);
    std::cout << "  " << handsText<Puppeteer>({&ana, &raj}, cast) << '\n';
    passed += checkYes("ana.perform(\"wave\") returns true", ana.perform("wave"));
    passed += checkText("the real Kit afterwards: kit.getPose()", kit.getPose(), "wave");
    ana.letGo();
    passed += checkHand("after ana.letGo(): ana.getPuppet()", ana.getPuppet(), nullptr, cast);
    bool moved{ana.perform("bow")};
    passed += checkYes("empty hands: ana.perform(\"bow\") returns false, and Kit still waves", !moved && kit.getPose() == "wave");

    ana.grab(kit);
    raj.grab(kit);
    std::cout << "  " << handsText<Puppeteer>({&ana, &raj}, cast) << '\n';
    ana.perform("sit");
    raj.perform("jump");
    Puppet* anasPuppet{ana.getPuppet()};
    passed += checkYes("after ana.perform(\"sit\") and raj.perform(\"jump\"), Ana's puppet jumps", anasPuppet == &kit && kit.getPose() == "jump");
    std::cout << "Group 2: " << passed << " / 5\n\n";
    return passed;
}
// [GROUP 2 END] */

// [GROUP 3 START] delete this line and the [GROUP 3 END] line below to enable
int group_3()
{
    std::cout << "== Group 3: passTo and trade ==\n";
    int passed{0};
    Puppet kit{"Kit"};
    Puppet bo{"Bo"};
    std::vector<Puppet*> cast{&kit, &bo};
    Puppeteer ana{"Ana"};
    Puppeteer raj{"Raj"};
    Puppeteer lee{"Lee"};
    std::vector<Puppeteer*> troupe{&ana, &raj, &lee};

    // Before each check the hands are set here with grab and letGo, so that
    // one wrong answer does not change the checks after it.
    ana.grab(kit);
    raj.grab(bo);
    lee.letGo();
    std::cout << "  " << handsText(troupe, cast) << '\n';
    bool passed1{ana.passTo(lee)};
    std::cout << "  after ana.passTo(lee): " << handsText(troupe, cast) << '\n';
    passed += checkYes("ana.passTo(lee) returns true, and passTo takes a Puppeteer& (not a copy)", passed1 && !PassesACopy<Puppeteer>);
    passed += checkYes("afterwards Lee holds Kit and Ana's hands are empty", lee.getPuppet() == &kit && ana.getPuppet() == nullptr);

    ana.letGo();
    raj.grab(bo);
    lee.grab(kit);
    std::cout << "  " << handsText(troupe, cast) << '\n';
    bool passedBack{lee.passTo(ana)};
    std::cout << "  after lee.passTo(ana): " << handsText(troupe, cast) << '\n';
    passed += checkYes("lee.passTo(ana) returns true, Ana holds Kit, and Lee's hands are empty", passedBack && ana.getPuppet() == &kit && lee.getPuppet() == nullptr);

    ana.letGo();
    raj.grab(bo);
    lee.letGo();
    std::cout << "  " << handsText(troupe, cast) << '\n';
    bool passed2{ana.passTo(lee)};
    passed += checkYes("ana.passTo(lee) with empty hands returns false, and nobody holds anything new", !passed2 && ana.getPuppet() == nullptr && lee.getPuppet() == nullptr);

    ana.grab(kit);
    raj.grab(bo);
    std::cout << "  " << handsText(troupe, cast) << '\n';
    bool passed3{ana.passTo(raj)};
    passed += checkYes("ana.passTo(raj), whose hands are full, returns false, and nothing changes", !passed3 && ana.getPuppet() == &kit && raj.getPuppet() == &bo);

    ana.grab(kit);
    raj.grab(bo);
    bool passed4{ana.passTo(ana)};
    passed += checkYes("ana.passTo(ana) returns false, and Ana still holds Kit", !passed4 && ana.getPuppet() == &kit);

    ana.grab(kit);
    raj.grab(bo);
    std::cout << "  " << handsText(troupe, cast) << '\n';
    ana.trade(raj);
    std::cout << "  after ana.trade(raj): " << handsText(troupe, cast) << '\n';
    passed += checkYes("ana.trade(raj): Ana holds Bo and Raj holds Kit", ana.getPuppet() == &bo && raj.getPuppet() == &kit);

    ana.grab(kit);
    lee.letGo();
    std::cout << "  " << handsText(troupe, cast) << '\n';
    ana.trade(lee);
    std::cout << "  after ana.trade(lee): " << handsText(troupe, cast) << '\n';
    passed += checkYes("ana.trade(lee), whose hands are empty: Ana's hands are empty and Lee holds Kit", ana.getPuppet() == nullptr && lee.getPuppet() == &kit);
    std::cout << "Group 3: " << passed << " / 8\n\n";
    return passed;
}
// [GROUP 3 END] */

// [GROUP 4 START] delete this line and the [GROUP 4 END] line below to enable
#include "Narrator.hpp"

int group_4()
{
    std::cout << "== Group 4: the Narrator ==\n";
    if (NarratorTakesACopy<Narrator>)
    {
        std::cout << "[FAIL] the Narrator constructor takes a Puppet&: no. It accepts a temporary\n"
                     "       puppet, so its parameter is a copy, and the narrator would be bound to\n"
                     "       a copy that is gone as soon as the constructor ends.\n";
        std::cout << "Group 4: 0 / 6 (the other checks wait until the constructor takes a Puppet&)\n\n";
        return 0;
    }
    int passed{checkYes("the Narrator constructor takes a Puppet&, not a copy", true)};
    Puppet pip{"Pip"};
    Narrator narrator{pip};
    passed += checkText("Narrator narrator{pip}; narrator.getStarName()", narrator.getStarName(), "Pip");
    narrator.cue("bow");
    passed += checkText("after narrator.cue(\"bow\"): the real Pip, pip.getPose()", pip.getPose(), "bow");
    narrator.getStar().setPose("sit");
    passed += checkText("after narrator.getStar().setPose(\"sit\"): pip.getPose()", pip.getPose(), "sit");

    Puppeteer ana{"Ana"};
    ana.grab(pip);
    narrator.cue("cheer");
    Puppet* anasPuppet{ana.getPuppet()};
    passed += checkYes("Ana holds Pip; after narrator.cue(\"cheer\"), Ana's puppet cheers", anasPuppet == &pip && pip.getPose() == "cheer");

    // Only a reference member makes this true: a reference can never be
    // bound to another puppet, so one Narrator cannot be assigned to another.
    passed += checkYes("the star is a Puppet& member: one Narrator cannot be assigned to another", !std::is_copy_assignable_v<Narrator>);
    std::cout << "Group 4: " << passed << " / 6\n\n";
    return passed;
}
// [GROUP 4 END] */

int main()
{
    std::signal(SIGSEGV, crashed);
    std::cout << std::unitbuf;      // print every line at once, so nothing is lost in a crash
    int milestone1{0};
    int milestone2{0};
    // Un-comment each call together with its group above.
    milestone1 += group_1();
    milestone1 += group_2();
    milestone2 += group_3();
    milestone2 += group_4();
    std::cout << "Milestone 1: " << milestone1 << " / 10 checks passed\n";
    std::cout << "Milestone 2: " << milestone2 << " / 14 checks passed\n";
    return 0;
}
