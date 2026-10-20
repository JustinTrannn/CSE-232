// vowels_to_end.cpp
// Lab 07, Milestone 1: Vowels to the end
//
// Build:  g++ -std=c++20 -Wall vowels_to_end.cpp -o vowels_to_end
// Run:    ./vowels_to_end        (Windows: .\vowels_to_end.exe)
//
// Written by:  (your name)

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

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

// Prints a vector of numbers as {1, 2, 3}.
void print_numbers(std::vector<int> numbers)
{
    std::cout << '{';
    for (size_t i{0}; i < numbers.size(); ++i)
    {
        std::cout << (i == 0 ? "" : ", ") << numbers.at(i);
    }
    std::cout << '}';
}

// Prints one PASS or FAIL line for a vector of numbers. Returns 1 or 0.
int check_numbers(std::string label, std::vector<int> got, std::vector<int> expected)
{
    if (got == expected)
    {
        std::cout << "[PASS] " << label << " -> ";
        print_numbers(got);
        std::cout << '\n';
        return 1;
    }
    std::cout << "[FAIL] " << label << ": got ";
    print_numbers(got);
    std::cout << ", expected ";
    print_numbers(expected);
    std::cout << '\n';
    return 0;
}

// =================================================================
// YOUR CODE. Write your function here, above the CHECKS line.
// =================================================================

std::string vowels_to_end(std::string text) {
    std::string non_vowel_pile {};
    std::string vowel_pile {};
    std::string vowels {"aeiou"};

    for (char c : text) {
        if (vowels.find(std::tolower(c)) == std::string::npos) {
            non_vowel_pile.push_back(c);
        } else {
            vowel_pile.push_back(c);
        }
    }

    return non_vowel_pile + vowel_pile;
}

// =================================================================
// CHECKS (provided). Once your function exists, delete the
// [CHECKS START] and [CHECKS END] lines. Do not edit the checks.
// =================================================================


void run_checks()
{
    std::cout << "== Vowels to the end checks ==\n";
    int passed{0};
    passed += check_text("vowels_to_end(\"program\")", vowels_to_end("program"), "prgrmoa");
    passed += check_text("vowels_to_end(\"banana\")", vowels_to_end("banana"), "bnnaaa");
    passed += check_text("vowels_to_end(\"Apple\")", vowels_to_end("Apple"), "pplAe");
    passed += check_text("vowels_to_end(\"sky\")", vowels_to_end("sky"), "sky");
    passed += check_text("vowels_to_end(\"aeiou\")", vowels_to_end("aeiou"), "aeiou");
    passed += check_text("vowels_to_end(\"C++ is fun\")", vowels_to_end("C++ is fun"), "C++ s fniu");
    passed += check_text("vowels_to_end(\"\")", vowels_to_end(""), "");
    std::cout << "Vowels to the end: " << passed << " / 7 checks passed\n";
}


int main()
{
    // Un-comment the next line together with the check block above.
    run_checks();
    return 0;
}
