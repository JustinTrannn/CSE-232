// minutes_between.cpp
// Lab 05, Problem 2: Minutes between two times
//
// Build:  g++ -std=c++20 -Wall minutes_between.cpp -o minutes_between
// Run:    ./minutes_between        (Windows: .\minutes_between.exe)
//
// Written by:  (your name)

#include <iostream>
#include <string>

// =================================================================
// PROVIDED: check utilities. Do not edit.
// =================================================================

// Prints one PASS or FAIL line for a number. Returns 1 or 0.
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

// =================================================================
// YOUR CODE. Write your function here, above the CHECKS line.
// =================================================================

int minutes_between(std::string start, std::string end) {
    int minutes {};
    std::string start_first_pos {};
    std::string start_sec_pos {};
    std::string end_first_pos {};
    std::string end_sec_pos {};


    bool light_switch {true};

    // start string first pos
    // start string sec pos
    // end string first pos
    // end string sec pos

    // first pos * 60 + sec pos; do this for start and end times

    // subtract end by start times;

    // if it is negative, then its midnight;
    // if its not, return those minutes;

    for (char &c : start) {
        if (std::isdigit(c) && light_switch) {
            start_first_pos.push_back(c);
        } else {
            light_switch = false;
            if (std::isdigit(c)) {
                start_sec_pos.push_back(c);
            }
        }
    }

    light_switch = true;
    for (char &c : end) {
        if (std::isdigit(c) && light_switch) {
            end_first_pos.push_back(c);
        } else {
            light_switch = false;
            if (std::isdigit(c)) {
                end_sec_pos.push_back(c);
            }
        }
    }
    // std::cout << start_first_pos << start_sec_pos << end_first_pos << end_sec_pos << std::endl;

    int start_since_mid {std::stoi(start_first_pos) * 60 + std::stoi(start_sec_pos)};
    int end_since_mid {std::stoi(end_first_pos) * 60 + std::stoi(end_sec_pos)};

    if (end_since_mid - start_since_mid < 0) {
        minutes = end_since_mid - start_since_mid + 1440;
    } else {
        minutes = end_since_mid - start_since_mid;
    }

    return minutes;
}

// =================================================================
// CHECKS (provided). Once your function exists, delete the
// [CHECKS START] and [CHECKS END] lines. Do not edit the checks.
// =================================================================

void run_checks()
{
    std::cout << "== Minutes between checks ==\n";
    int passed{0};
    passed += check("minutes_between(\"09:45\", \"11:10\")", minutes_between("09:45", "11:10"), 85);
    passed += check("minutes_between(\"00:00\", \"23:59\")", minutes_between("00:00", "23:59"), 1439);
    passed += check("minutes_between(\"13:05\", \"13:05\")", minutes_between("13:05", "13:05"), 0);
    passed += check("minutes_between(\"9:05\", \"10:00\")", minutes_between("9:05", "10:00"), 55);
    passed += check("minutes_between(\"7:45\", \"8:15\")", minutes_between("7:45", "8:15"), 30);
    passed += check("minutes_between(\"23:30\", \"00:15\")", minutes_between("23:30", "00:15"), 45);
    passed += check("minutes_between(\"18:00\", \"07:30\")", minutes_between("18:00", "07:30"), 810);
    passed += check("minutes_between(\"10:00\", \"9:05\")", minutes_between("10:00", "9:05"), 1385);
    std::cout << "Minutes between: " << passed << " / 8 checks passed\n";
}


int main()
{
    // Un-comment the next line together with the check block above.
    run_checks();
    // std::cout << minutes_between("10:00", "10:10");
    return 0;
}
