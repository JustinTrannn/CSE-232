// remove_zeros.cpp
// Lab 07, Practice 1: Remove the zeros
//
// Build:  g++ -std=c++20 -Wall remove_zeros.cpp -o remove_zeros
// Run:    ./remove_zeros        (Windows: .\remove_zeros.exe)
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

int remove_zeros(int x) {
    std::string x_string {std::to_string(x)};
    std::string x_result {};

    // First base case if zero then return 0
    if (x_string == "0") {
        return 0;
    }
    // iterate through x_string
    // if its not 0, append it to x_result
    for (char c : x_string) {
        if (c != '0') {
            x_result.push_back(c);
        }
    }
    return std::stoi(x_result);
}

// =================================================================
// CHECKS (provided). Once your function exists, delete the
// [CHECKS START] and [CHECKS END] lines. Do not edit the checks.
// =================================================================


void run_checks()
{
    std::cout << "== Remove zeros checks ==\n";
    int passed{0};
    passed += check("remove_zeros(105030)", remove_zeros(105030), 153);
    passed += check("remove_zeros(909)", remove_zeros(909), 99);
    passed += check("remove_zeros(1000)", remove_zeros(1000), 1);
    passed += check("remove_zeros(123)", remove_zeros(123), 123);
    passed += check("remove_zeros(7)", remove_zeros(7), 7);
    passed += check("remove_zeros(0)", remove_zeros(0), 0);
    passed += check("remove_zeros(2000002)", remove_zeros(2000002), 22);
    passed += check("remove_zeros(10)", remove_zeros(10), 1);
    std::cout << "Remove zeros: " << passed << " / 8 checks passed\n";
}


int main()
{
    // Un-comment the next line together with the check block above.
    run_checks();
    return 0;
}
