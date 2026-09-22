// bossfight.cpp
// Challenge protocol for the basement MAINFRAME, CSE building
//
// Started by: a student assistant (graduated last spring)
// Status:     the scoreboard and the checks are done. The game logic is not.
//             Every function marked TODO is yours to write.
//
// Follow the lab guide. It tells you which function to write next,
// what it must do, and how to check it.

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// -----------------------------------------------------------------
// Game constants. "const" means the value can never change, which is
// why it is safe for these to live outside of every function.
// Do not change these numbers.
// -----------------------------------------------------------------
const int PLAYER_MAX_HP{100};
const int BOSS_MAX_HP{200};
const int PLAYER_ATTACK{30};
const int HEAL_AMOUNT{40};

// -----------------------------------------------------------------
// Function list (forward declarations).
// Every function in this file is declared here, so that any function
// can call any other one no matter where it is written below.
// -----------------------------------------------------------------
void print_health_bar(int hp, int max_hp);
// Milestone 1
int apply_damage(int hp, int damage);
int heal(int hp, int amount, int max_hp);
bool is_alive(int hp);
// Milestone 2
int boss_damage_for_turn(int turn, std::vector<int> pattern);
void print_status(int turn, int player_hp, int boss_hp);
void battle();
// Milestone 3
int player_attack_damage(int turn);
void print_health_bar(int hp, int max_hp);
int defended_damage(int damage);
// Practice (optional, not graded)
int potion_amount(std::vector<int> potions, int next_potion);
bool is_enraged(int boss_hp, int boss_max_hp);
int enraged_damage(int base_damage);
// Provided
std::string boss_move_name(int turn);
void print_result(int turn, int player_hp, int boss_hp);
int check(std::string label, int got, int expected);
void check_milestone_1();
void check_milestone_2();
void check_milestone_3();
void check_practice();

int main()
{
    check_milestone_1();
    check_milestone_2();
    check_milestone_3();
    // check_practice();
    battle();
    return 0;
}

// =================================================================
// YOUR CODE
// =================================================================

// ------------------------- Milestone 1 ---------------------------

// Returns the HP that is left after taking damage.
// HP can never go below 0.
//   apply_damage(100, 30) returns 70
//   apply_damage(20, 50)  returns 0
int apply_damage(int hp, int damage)
{   
    // If your hp ends up as 0 or lower, then return 0
    if ((hp - damage) <= 0) {
        return 0;
    } else {
        return (hp - damage);
    }
}

// Returns the HP after healing by amount.
// HP can never go above max_hp.
//   heal(50, 40, 100) returns 90
//   heal(90, 40, 100) returns 100
int heal(int hp, int amount, int max_hp)
{
    if ((hp + amount) > max_hp) {
        return max_hp;
    } else {
        return (hp + amount);
    }
}

// Returns true if hp is more than 0, and false otherwise.
bool is_alive(int hp)
{
    if (hp > 0) {
        return true;
    } else {
        return false;
    }
}

// ------------------------- Milestone 2 ---------------------------

// Returns how much damage the boss deals on the given turn.
// The boss walks through the pattern one number per turn and starts
// over when it reaches the end. Turns start at 1.
// With the pattern {10, 15, 10, 40}:
//   turn 1 returns 10, turn 2 returns 15, turn 4 returns 40,
//   turn 5 returns 10 again, turn 8 returns 40 again.
// It must work for a pattern of any length.
int boss_damage_for_turn(int turn, std::vector<int> pattern)
{
    int pattern_length {int(pattern.size())};
    int actual_turn {turn % pattern_length};

    if (turn < pattern_length) {
        return pattern.at(turn-1);
    } else if (turn % pattern_length != 0){
        return pattern.at(actual_turn-1);
    } else {
        return pattern.at(pattern_length-1);
    }
    
}

// Prints the turn header and both HP values. See the guide for the format.
void print_status(int turn, int player_hp, int boss_hp)
{
    std::cout << "--- Turn " << turn << " ---" << "\n";
    std::cout << "You         ";
    print_health_bar(player_hp, PLAYER_MAX_HP);
    std::cout << player_hp << "/" << PLAYER_MAX_HP << "\n";
    std::cout << "Mainframe   ";
    print_health_bar(boss_hp, BOSS_MAX_HP);
    std::cout << " "<< boss_hp << "/" << BOSS_MAX_HP << "\n";
}

// Runs the whole fight. The guide walks you through the numbered steps.
void battle()
{
    std::vector<int> boss_pattern{10, 15, 10, 40};
    int player_hp{PLAYER_MAX_HP};
    int boss_hp{BOSS_MAX_HP};
    int turn{0};

    std::cout << "\n=== THE MAINFRAME BOOTS UP ===\n";

    // TODO: repeat the steps below while BOTH the player and the boss are alive.
    //
    //   Step 1. Add 1 to turn.
    //   Step 2. Print the status.
    //   Step 3. Ask for an action and read one word into a std::string.
    //   Step 4. Do the action:
    //             "attack"       the boss takes PLAYER_ATTACK damage
    //             "heal"         the player heals HEAL_AMOUNT (never above PLAYER_MAX_HP)
    //             anything else  the player fumbles and the turn is wasted
    //   Step 5. If the boss is still alive, it attacks the player with
    //           boss_damage_for_turn(turn, boss_pattern).

    // Provided: announces the winner. Keep this as the last line of battle().
    while (is_alive(boss_hp) && is_alive(player_hp)) {
        bool defending {false};
        ++turn;
        print_status(turn, player_hp, boss_hp);

        std::string action {};
        std::cin >> action;
        if (action == "attack") {
            boss_hp = apply_damage(boss_hp, player_attack_damage(turn));
        } else if (action == "heal") {
            player_hp = heal(player_hp, HEAL_AMOUNT, PLAYER_MAX_HP);
        } else if (action == "defend") {
            defending = true;
        } else {
            std::cout << "You fumble with the keyboard. Turn wasted." << "\n";
        }
        
        if (is_alive(boss_hp) && defending == false) {
            player_hp = player_hp - boss_damage_for_turn(turn, boss_pattern);
        } else if (is_alive(boss_hp) && defending == true) {
            player_hp = player_hp - defended_damage(boss_damage_for_turn(turn, boss_pattern));
        }
    }



    print_result(turn, player_hp, boss_hp);
}

// ------------------------- Milestone 3 ---------------------------

// 3a. Returns how much damage the player's attack deals on the given turn.
// Every 3rd turn (3, 6, 9, ...) is a critical hit and deals double PLAYER_ATTACK.
// Every other turn deals PLAYER_ATTACK.
int player_attack_damage(int turn)
{
    if (turn % 3 == 0) {
        std::cout << "CRITICAL HIT! You hit the Mainframe for 60 damage." << "\n";
        return PLAYER_ATTACK*2;
    } else {
        return PLAYER_ATTACK;
    }
}

// 3b. Prints a 10-segment health bar such as [######----] with no newline.
// The number of '#' segments is hp * 10 / max_hp. The rest are '-'.
//   print_health_bar(65, 100)  prints [######----]
//   print_health_bar(140, 200) prints [#######---]
void print_health_bar(int hp, int max_hp)
{
    std::cout << "[";
    int tag_counter {0};
    for (int i {0}; hp > i; i += 10) {
        std::cout << "#";
        ++tag_counter;
    }
    for (int i {0}; 10-tag_counter > i; ++i) {
        std::cout << "-";
    }
    std::cout << "]";
}

// 3c. Returns the damage that gets through when the player is defending:
// half of the damage, rounded down.
//   defended_damage(40) returns 20
//   defended_damage(15) returns 7
int defended_damage(int damage)
{
    return int(damage/2);
}

// ----------------- Practice (optional, not graded) ----------------
// The graded lab ends with Milestone 3. These functions belong to the
// optional practice page of the guide.

// 4a. Returns the healing amount of the potion at position next_potion,
// or 0 if there is no potion at that position (all potions are used up).
//   potion_amount({30, 50}, 0) returns 30
//   potion_amount({30, 50}, 1) returns 50
//   potion_amount({30, 50}, 2) returns 0
int potion_amount(std::vector<int> potions, int next_potion)
{
    // TODO
    return -1;
}

// 4b. Returns true when the boss has 30 percent or less of its max HP left.
//   is_enraged(59, 200) returns true    (29.5 percent)
//   is_enraged(61, 200) returns false   (30.5 percent)
bool is_enraged(int boss_hp, int boss_max_hp)
{
    // TODO
    return false;
}

// 4b. Returns base_damage multiplied by 1.5, rounded down to a whole number.
//   enraged_damage(10) returns 15
//   enraged_damage(15) returns 22
int enraged_damage(int base_damage)
{
    // TODO
    return -1;
}

// =================================================================
// PROVIDED -- DO NOT EDIT BELOW THIS LINE
// =================================================================

// The Mainframe repeats four moves forever.
std::string boss_move_name(int turn)
{
    int slot{turn % 4};
    if (slot == 0)
    {
        return "SEGFAULT SLAM";
    }
    if (slot == 2)
    {
        return "Packet Storm";
    }
    return "Ping";
}

void print_result(int turn, int player_hp, int boss_hp)
{
    std::cout << '\n';
    if (player_hp <= 0)
    {
        std::cout << "DEFEAT on turn " << turn << ". The Mainframe had "
                  << boss_hp << " HP left.\n";
    }
    else if (boss_hp <= 0)
    {
        std::cout << "VICTORY on turn " << turn << " with " << player_hp << " HP left.\n";
    }
    else
    {
        std::cout << "The fight is not over: you have " << player_hp
                  << " HP, the Mainframe has " << boss_hp << " HP.\n";
    }
}

// Prints one PASS or FAIL line. Returns 1 for a pass and 0 for a fail.
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

void check_milestone_1()
{
    std::cout << "\n== Milestone 1 checks ==\n";
    int passed{0};
    passed += check("apply_damage(100, 30)", apply_damage(100, 30), 70);
    passed += check("apply_damage(30, 30)", apply_damage(30, 30), 0);
    passed += check("apply_damage(20, 50)", apply_damage(20, 50), 0);
    passed += check("heal(50, 40, 100)", heal(50, 40, 100), 90);
    passed += check("heal(90, 40, 100)", heal(90, 40, 100), 100);
    passed += check("heal(100, 40, 100)", heal(100, 40, 100), 100);
    passed += check("is_alive(25)", is_alive(25), true);
    passed += check("is_alive(0)", is_alive(0), false);
    std::cout << "Milestone 1: " << passed << " / 8 checks passed\n";
}

void check_milestone_2()
{
    std::cout << "\n== Milestone 2 checks ==\n";
    std::vector<int> pattern{10, 15, 10, 40};
    std::vector<int> short_pattern{5, 7};
    int passed{0};
    passed += check("boss_damage_for_turn(1, {10,15,10,40})", boss_damage_for_turn(1, pattern), 10);
    passed += check("boss_damage_for_turn(2, {10,15,10,40})", boss_damage_for_turn(2, pattern), 15);
    passed += check("boss_damage_for_turn(3, {10,15,10,40})", boss_damage_for_turn(3, pattern), 10);
    passed += check("boss_damage_for_turn(4, {10,15,10,40})", boss_damage_for_turn(4, pattern), 40);
    passed += check("boss_damage_for_turn(5, {10,15,10,40})", boss_damage_for_turn(5, pattern), 10);
    passed += check("boss_damage_for_turn(8, {10,15,10,40})", boss_damage_for_turn(8, pattern), 40);
    passed += check("boss_damage_for_turn(3, {5,7})", boss_damage_for_turn(3, short_pattern), 5);
    std::cout << "Milestone 2: " << passed << " / 7 checks passed\n";
}

void check_milestone_3()
{
    std::cout << "\n== Milestone 3 checks ==\n";
    int passed{0};

    std::cout << "3a critical hits\n";
    passed += check("player_attack_damage(1)", player_attack_damage(1), 30);
    passed += check("player_attack_damage(3)", player_attack_damage(3), 60);
    passed += check("player_attack_damage(6)", player_attack_damage(6), 60);
    passed += check("player_attack_damage(7)", player_attack_damage(7), 30);

    std::cout << "3b health bar (look at these yourself, they are not counted)\n";
    std::cout << "  ";
    print_health_bar(100, 100);
    std::cout << "  should be [##########]\n";
    std::cout << "  ";
    print_health_bar(65, 100);
    std::cout << "  should be [######----]\n";
    std::cout << "  ";
    print_health_bar(140, 200);
    std::cout << "  should be [#######---]\n";
    std::cout << "  ";
    print_health_bar(0, 200);
    std::cout << "  should be [----------]\n";

    std::cout << "3c defend\n";
    passed += check("defended_damage(40)", defended_damage(40), 20);
    passed += check("defended_damage(15)", defended_damage(15), 7);

    std::cout << "Milestone 3: " << passed << " / 6 checks passed\n";
}

// Optional practice page. Not graded.
void check_practice()
{
    std::cout << "\n== Practice checks (optional) ==\n";
    std::vector<int> potions{30, 50};
    int passed{0};

    std::cout << "4a potions\n";
    passed += check("potion_amount({30,50}, 0)", potion_amount(potions, 0), 30);
    passed += check("potion_amount({30,50}, 1)", potion_amount(potions, 1), 50);
    passed += check("potion_amount({30,50}, 2)", potion_amount(potions, 2), 0);

    std::cout << "4b enrage\n";
    passed += check("is_enraged(200, 200)", is_enraged(200, 200), false);
    passed += check("is_enraged(61, 200)", is_enraged(61, 200), false);
    passed += check("is_enraged(59, 200)", is_enraged(59, 200), true);
    passed += check("is_enraged(20, 200)", is_enraged(20, 200), true);
    passed += check("enraged_damage(10)", enraged_damage(10), 15);
    passed += check("enraged_damage(15)", enraged_damage(15), 22);
    passed += check("enraged_damage(40)", enraged_damage(40), 60);

    std::cout << "Practice: " << passed << " / 10 checks passed\n";
}
