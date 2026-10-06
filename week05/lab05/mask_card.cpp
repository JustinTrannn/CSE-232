// mask_card.cpp
// Lab 05, Problem 1: Mask a card number
//
// Build:  g++ -std=c++20 -Wall mask_card.cpp -o mask_card
// Run:    ./mask_card        (Windows: .\mask_card.exe)
//
// Written by:  (your name)

#include <cctype>
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

std::string mask_card(std::string x) {
    // First test case: If it's 4 or less, return the same thing
    if (static_cast<int>(x.size()) <= 4) {
        return x;
    } 

    int digit_count {};
    std::string final_x {};

    for (char &c : x) {
        if (std::isdigit(c)) {
            ++digit_count;
        }
    }

    for (char &c : x) {
        if (std::isdigit(c) && digit_count - 4 > 0) {
            final_x.push_back('*');
            --digit_count;
        } else {
            final_x.push_back(c);
        }
    }

    return final_x;
}

// =================================================================
// CHECKS (provided). Once your function exists, delete the
// [CHECKS START] and [CHECKS END] lines. Do not edit the checks.
// =================================================================


void run_checks()
{
    std::cout << "== Mask card checks ==\n";
    int passed{0};
    passed += check_text("mask_card(\"4111222233334444\")", mask_card("4111222233334444"), "************4444");
    passed += check_text("mask_card(\"4111 2222 3333 4444\")", mask_card("4111 2222 3333 4444"), "**** **** **** 4444");
    passed += check_text("mask_card(\"4111-2222-3333-4444\")", mask_card("4111-2222-3333-4444"), "****-****-****-4444");
    passed += check_text("mask_card(\"378282246310005\")", mask_card("378282246310005"), "***********0005");
    passed += check_text("mask_card(\"12 34 56\")", mask_card("12 34 56"), "** 34 56");
    passed += check_text("mask_card(\"1234\")", mask_card("1234"), "1234");
    passed += check_text("mask_card(\"98\")", mask_card("98"), "98");
    passed += check_text("mask_card(\"\")", mask_card(""), "");
    std::cout << "Mask card: " << passed << " / 8 checks passed\n";
}


int main()
{
    // Un-comment the next line together with the check block above.
    run_checks();
    // std::cout << mask_card("12 34 abc56") << std::endl;
    return 0;
}
