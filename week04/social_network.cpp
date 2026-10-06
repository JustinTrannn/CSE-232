// Lab 04: Social Network Backend
//
// Reads a member list and their connections from standard input, then
// answers commands. The input format, the commands, and the exact output
// are in the lab guide. The milestone pages describe each function you
// must create; writing its signature is part of the task.
//
// Build:  g++ -std=c++20 -Wall social_network.cpp -o social_network
// Run:    ./social_network < data/campus.txt
//
// Written by:  (your name)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// =================================================================
// PROVIDED: check utilities. Do not edit.
// =================================================================

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

// Prints one PASS or FAIL line for a list of names. Returns 1 or 0.
int check_list(std::string label, std::vector<std::string> got, std::vector<std::string> expected)
{
    std::cout << (got == expected ? "[PASS] " : "[FAIL] ") << label << (got == expected ? " -> {" : ": got {");
    for (size_t i{0}; i < got.size(); ++i)
    {
        std::cout << (i == 0 ? "" : " ") << got.at(i);
    }
    std::cout << '}';
    if (got != expected)
    {
        std::cout << ", expected {";
        for (size_t i{0}; i < expected.size(); ++i)
        {
            std::cout << (i == 0 ? "" : " ") << expected.at(i);
        }
        std::cout << '}';
    }
    std::cout << '\n';
    return got == expected ? 1 : 0;
}

// =================================================================
// YOUR FUNCTIONS. Everything you write goes here, above the CHECKS line.
// The required signatures are in the lab guide. Type them exactly.
// Helpers you design yourself go here too.
// =================================================================

bool user_exists(std::string username, std::vector<std::string> users) {
    for (std::string name : users) {
        if (name == username) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> friends_of(std::string username, std::vector<std::string> friend_a, std::vector<std::string> friend_b) {
    std::vector<std::string> friends {};
    std::vector<std::string> non_dup_friends {};

    for (size_t i {0}; friend_a.size() > i; ++i) {
        if (friend_a.at(i) == username) {
            friends.push_back(friend_b.at(i));
        }
    }

    for (size_t i {0}; friend_b.size() > i; ++i) {
        if (friend_b.at(i) == username) {
            friends.push_back(friend_a.at(i));
        }
    }

    for (std::string x : friends) {
        if (user_exists(x, non_dup_friends) == false) {
            non_dup_friends.push_back(x);
        }
    }

    return non_dup_friends;
}

int count_friends(std::string username, std::vector<std::string> friend_a, std::vector<std::string> friend_b) {
    return static_cast<int>(friends_of(username, friend_a, friend_b).size());
}

std::vector<std::string> mutual_friends(std::string username_1, std::string username_2, std::vector<std::string> friend_a, std::vector<std::string> friend_b) {
    std::vector<std::string> friends_of_1 {friends_of(username_2, friend_a, friend_b)};
    std::vector<std::string> friends_of_2 {friends_of(username_1, friend_a, friend_b)};
    std::vector<std::string> mutuals {};
    for (std::string name : friends_of_1) {
        if (user_exists(name, friends_of_2) == true) {
            mutuals.push_back(name);
        }
    }
    return mutuals;
}

std::string recommend_friend(std::string username, std::vector<std::string> users, std::vector<std::string> friend_a, std::vector<std::string> friend_b) {
    std::vector<std::string> candidates {};
    std::vector<std::string> friends_of_username {friends_of(username, friend_a, friend_b)};
    std::string recommended_username {};
    int count {0};

    for (std::string x : users) {
        if (x != username && user_exists(x, friends_of_username) == false) {
            candidates.push_back(x);
        }
    }

    for (std::string potential_friend : candidates) {
        int num_of_mutuals {static_cast<int>(mutual_friends(username, potential_friend, friend_a, friend_b).size())};
        if (num_of_mutuals > count) {
            count = num_of_mutuals;
            recommended_username = potential_friend;
        }
    }


    return recommended_username;
}

// =================================================================
// CHECKS (provided). Un-comment a block once you have written the
// functions it calls. Do not edit the checks themselves.
// =================================================================

// [M1 CHECKS START] delete this line and the [M1 CHECKS END] line below to enable
void check_milestone_1()
{
    std::cout << "\n== Milestone 1 checks ==\n";
    std::vector<std::string> users{"ann", "ben", "cal", "dee", "eve"};
    std::vector<std::string> fa{"ann", "ann", "ben", "cal"};
    std::vector<std::string> fb{"ben", "cal", "dee", "dee"};
    std::vector<std::string> dup_a{"ann", "ben", "ann", "ann"};
    std::vector<std::string> dup_b{"ben", "ann", "cal", "ben"};
    int passed{0};
    passed += check("user_exists(\"ann\")", user_exists("ann", users), true);
    passed += check("user_exists(\"eve\")", user_exists("eve", users), true);
    passed += check("user_exists(\"zed\")", user_exists("zed", users), false);
    passed += check_list("friends_of(\"ann\")", friends_of("ann", fa, fb), {"ben", "cal"});
    passed += check_list("friends_of(\"dee\")", friends_of("dee", fa, fb), {"ben", "cal"});
    passed += check_list("friends_of(\"eve\")", friends_of("eve", fa, fb), {});
    passed += check_list("friends_of(\"ann\")  (duplicate connections)", friends_of("ann", dup_a, dup_b), {"ben", "cal"});
    passed += check_list("friends_of(\"ben\")  (duplicate connections)", friends_of("ben", dup_a, dup_b), {"ann"});
    std::cout << "Milestone 1: " << passed << " / 8 checks passed\n";
}
// [M1 CHECKS END]


void check_milestone_2()
{
    std::cout << "\n== Milestone 2 checks ==\n";
    std::vector<std::string> fa{"ann", "ann", "ben", "cal"};
    std::vector<std::string> fb{"ben", "cal", "dee", "dee"};
    std::vector<std::string> dup_a{"ann", "ben", "ann", "ann"};
    std::vector<std::string> dup_b{"ben", "ann", "cal", "ben"};
    int passed{0};
    passed += check("count_friends(\"ann\")", count_friends("ann", fa, fb), 2);
    passed += check("count_friends(\"dee\")", count_friends("dee", fa, fb), 2);
    passed += check("count_friends(\"eve\")", count_friends("eve", fa, fb), 0);
    passed += check("count_friends(\"ann\")  (duplicate connections)", count_friends("ann", dup_a, dup_b), 2);
    passed += check_list("mutual_friends(\"ann\", \"dee\")", mutual_friends("ann", "dee", fa, fb), {"ben", "cal"});
    passed += check_list("mutual_friends(\"ben\", \"cal\")", mutual_friends("ben", "cal", fa, fb), {"ann", "dee"});
    passed += check_list("mutual_friends(\"ann\", \"ben\")", mutual_friends("ann", "ben", fa, fb), {});
    passed += check_list("mutual_friends(\"eve\", \"ann\")", mutual_friends("eve", "ann", fa, fb), {});
    std::cout << "Milestone 2: " << passed << " / 8 checks passed\n";
}


// [M3 CHECKS START] delete this line and the [M3 CHECKS END] line below to enable
void check_milestone_3()
{
    std::cout << "\n== Milestone 3 checks ==\n";
    std::vector<std::string> users{"ann", "ben", "cal", "dee", "eve"};
    std::vector<std::string> fa{"ann", "ann", "ben", "cal"};
    std::vector<std::string> fb{"ben", "cal", "dee", "dee"};
    std::vector<std::string> users2{"pat", "quinn", "ray", "sam", "tess"};
    std::vector<std::string> fa2{"pat", "pat", "quinn", "ray", "quinn"};
    std::vector<std::string> fb2{"quinn", "ray", "sam", "tess", "ray"};
    int passed{0};
    passed += check_text("recommend_friend(\"ann\")", recommend_friend("ann", users, fa, fb), "dee");
    passed += check_text("recommend_friend(\"dee\")", recommend_friend("dee", users, fa, fb), "ann");
    passed += check_text("recommend_friend(\"ben\")", recommend_friend("ben", users, fa, fb), "cal");
    passed += check_text("recommend_friend(\"eve\")  (no friends)", recommend_friend("eve", users, fa, fb), "");
    passed += check_text("recommend_friend(\"zed\")  (unknown)", recommend_friend("zed", users, fa, fb), "");
    passed += check_text("recommend_friend(\"pat\")  (tie: sam and tess)", recommend_friend("pat", users2, fa2, fb2), "sam");
    std::cout << "Milestone 3: " << passed << " / 6 checks passed\n";
}
// [M3 CHECKS END] 

// =================================================================
// MAIN
// =================================================================

int main()
{
    // Un-comment each call together with its check block above.
    check_milestone_1();
    check_milestone_2();
    check_milestone_3();

    // ---- Load the network (Milestone 1) ----
    std::vector<std::string> users{};
    std::vector<std::string> friend_a{};
    std::vector<std::string> friend_b{};

    // TODO 1. Read the number of users, then read that many names into `users`.
    int num_users {};
    std::cin >> num_users;
    for (int i = 0; num_users > i; ++i) {
        std::string user {};
        std::cin >> user;
        users.push_back(user);
    }
    // TODO 2. Read the number of connections, then read that many pairs. For each
    //         pair push the first name onto `friend_a` and the second onto `friend_b`.
    int num_connections {};
    std::cin >> num_connections;
    for (int i = 0; num_connections*2 > i; ++i) {
        std::string friend_a_name;
        std::string friend_b_name;
        std::cin >> friend_a_name;
        std::cin >> friend_b_name;
        friend_a.push_back(friend_a_name);
        friend_b.push_back(friend_b_name);
    }

    // ---- Answer commands until the input ends ----
    std::string command{};
    while (std::cin >> command)
    {   
        // TODO 3. Add one `if (command == "...")` branch per command, above the
        //         final else. Milestone 1 adds "exists" and "friends".
        std::string name {};
        if (command == "exists") {
            std::cin >> name;
            if (user_exists(name, users)) {
                std::cout << name << ": not found" << "\n";
            } else {
                std::cout << name << ": found" << "\n";
            }

        } else if (command == "friends") {
            std::cin >> name;
            if (user_exists(name, users) == false) {
                std::cout << "unknown user: " << name << "\n";
            } else if (friends_of(name, friend_a, friend_b).size() > 0) {
                std::cout << name << ": ";
                for (std::string friend_name : friends_of(name, friend_a, friend_b)) {
                    std::cout << friend_name << " ";
                }
                std::cout << "\n";

            } else if (friends_of(name, friend_a, friend_b).size() == 0) {
                std::cout << name << ": (no friends)" << "\n";

            } else {
                std::cout << "something went wrong in main";
            }

        } else if (command == "summary") {
            std::cout << "users: " << static_cast<int>(users.size()) << "\nconnections: " << count_friends(name, friend_a, friend_b) << "\nmost connected: " << static_cast<int>(mutual_friends(name, name, friend_a, friend_b)) << "no friends: (none)" << "\n";
        } else {
            // Provided: unknown command. Throw away the rest of that line.
            // std::cout << "unknown command: " << command << '\n';
            std::string rest_of_line{};
            std::getline(std::cin, rest_of_line);
        }
        
    }

    return 0;
}
