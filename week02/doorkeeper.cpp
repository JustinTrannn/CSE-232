// doorkeeper.cpp
// Doorkeeper v0.9 -- after-hours door controller, CSE building, 3rd floor
//
// Written by: a student assistant (graduated last spring)
// Status:     unfinished. "Works on my machine." Last edited during finals week.
//
// Every door on the floor asks this program whether it may open.
// Each door that opens prints one FRAGMENT of the exit code.
// Collect all four fragments to reach the stairwell.

#include <iostream>
#include <string>

// -----------------------------------------------------------------
// Door list. Each door is a function, and main() opens them in order.
// A function must be declared before it is called, so every door is
// declared here and written out further down the file.
// -----------------------------------------------------------------
void door_1();
void door_2();
void door_3();
void door_4();
void exit_stairwell();

int main()
{
    std::cout << "=== DOORKEEPER v0.9 === after-hours mode ===\n\n";

    door_1();
    door_2();
    door_3();
    door_4();
    exit_stairwell();

    std::cout << "\nReport your exit code to the TA.\n";
    return 0;
}

// Joins two numbers: combine(23, 2) should give 232.
int combine(int left, int right)
{
    int result = left * 10 + right;
    std::cout << "[Door 4] combining " << left << " and " << right << "\n";
    return result;
}

// =================================================================
// DOOR 1: LOBBY DOOR
// The lobby door just wants to know who is there.
// =================================================================
void door_1()
{
    std::cout << "[Door 1] The lobby door hums. A speaker crackles." << std::endl;
    std::cout << "[Door 1] Who's there? ";

    std::string name;
    std::cin >> name;

    std::cout << "[Door 1] Welcome, " << name << ". After-hours access granted.\n";
    std::cout << "[Door 1] UNLOCKED. Fragment: C\n\n";
}

// =================================================================
// DOOR 2: KEYPAD
// The keypad shows two numbers. It opens only if the arithmetic
// comes out exactly right. The check values are on the sticky note.
// =================================================================
void door_2()
{
    std::cout << "[Door 2] A keypad glows. Two numbers blink on its screen.\n";
    std::cout << "[Door 2] Enter the two numbers: ";

    int a;
    int b;
    std::cin >> a >> b;

    int sum = a + b;
    int product = a * b;
    int remainder = a % b;
    double average = (a + b) / 2.0;

    std::cout << "[Door 2] sum=" << sum << " product=" << product
              << " remainder=" << remainder << " average=" << average << "\n";

    // The keypad opens for an odd sum with the exact average.
    if (sum % 2 == 1 && average == 119.5)
    {
        std::cout << "[Door 2] UNLOCKED. Fragment: S\n\n";
    }
    else
    {
        std::cout << "[Door 2] LOCKED. The keypad expected average 119.5 exactly.\n\n";
    }
}

// =================================================================
// DOOR 3: BADGE READER
// The badge reader checks the time and the badge type.
// After hours (18 to 23), only staff and admin badges work.
// =================================================================
void door_3()
{
    std::cout << "[Door 3] A badge reader blinks red.\n";
    std::cout << "[Door 3] Enter the hour (0-23) and your badge type: ";

    int hour;
    std::string badge;
    std::cin >> hour >> badge;

    bool after_hours = false;
    if (hour >= 18 && hour <= 23)
    {
        after_hours = true;
    }

    int level = 1; // everyone starts as a visitor
    if (badge == "STAFF")
    {
        level = 7;
    }
    else if (badge == "ADMIN")
    {
        level = 10;
    }

    std::string rank;
    if (level >= 0 && level < 5)
    {
        rank = "student";
    }
    else if (level > 5 && level < 9)
    {
        rank = "staff";
    }
    else if (level > 9)
    {
        rank = "admin";
    }

    std::cout << "[Door 3] after_hours=" << after_hours
              << " level=" << level << " rank=" << rank << "\n";

    if (after_hours && rank != "student")
    {
        std::cout << "[Door 3] UNLOCKED. Fragment: E\n\n";
    }
    else
    {
        std::cout << "[Door 3] LOCKED. Student badges do not open this door after hours.\n\n";
    }
}

// =================================================================
// DOOR 4: SERVER ROOM
// The server room door has no keypad. It computes its own code from
// the wiring diagram, which splits room 232 into 23 and 2.
// =================================================================
void door_4()
{
    std::cout << "[Door 4] The server room door has no keypad, only a wiring diagram.\n";

    bool armed = true; // the door is always armed after hours
    int code {0};

    if (armed)
    {
        code = combine(23, 2);
    }

    std::cout << "[Door 4] Computed code: " << code << "\n";

    if (code == 232)
    {
        std::cout << "[Door 4] UNLOCKED. Fragment: " << code << "\n\n";
    }
    else
    {
        std::cout << "[Door 4] LOCKED. The wiring diagram says the code should be 232.\n\n";
    }
}

// =================================================================
// EXIT: STAIRWELL   (Week 02 material -- see Milestone 3)
// The stairwell door only opens when every hallway light is on.
// A light reading of 0 or less means that light is out.
//
// TODO: the 3rd floor has more than 6 lights. I did not know how to
// check them all without copying this block again and again.
// =================================================================
void exit_stairwell()
{
    std::cout << "[Exit] The stairwell door checks the hallway lights.\n";
    std::cout << "[Exit] Enter the 6 light readings: ";

    bool all_on = true;

    int light1;
    std::cin >> light1;
    if (light1 <= 0)
    {
        std::cout << "[Exit] Light 1 is out.\n";
        all_on = false;
    }

    int light2;
    std::cin >> light2;
    if (light2 <= 0)
    {
        std::cout << "[Exit] Light 2 is out.\n";
        all_on = false;
    }

    int light3;
    std::cin >> light3;
    if (light3 <= 0)
    {
        std::cout << "[Exit] Light 3 is out.\n";
        all_on = false;
    }

    int light4;
    std::cin >> light4;
    if (light4 <= 0)
    {
        std::cout << "[Exit] Light 4 is out.\n";
        all_on = false;
    }

    int light5;
    std::cin >> light5;
    if (light5 <= 0)
    {
        std::cout << "[Exit] Light 5 is out.\n";
        all_on = false;
    }

    int light6;
    std::cin >> light6;
    if (light6 <= 0)
    {
        std::cout << "[Exit] Light 6 is out.\n";
        all_on = false;
    }

    int steps = 3.9; // flights of stairs to the exit? never finished this part

    if (all_on)
    {
        std::cout << "[Exit] All lights on. " << steps << " flights down to the exit.\n";
        std::cout << "[Exit] STAIRWELL UNLOCKED.\n";
    }
    else
    {
        std::cout << "[Exit] STAIRWELL LOCKED. Fix the lights first.\n";
    }
}
