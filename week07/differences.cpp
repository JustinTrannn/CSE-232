// differences.cpp
// Lab 07, Practice 2: Differences
//
// Build:  g++ -std=c++20 -Wall differences.cpp -o differences
// Run:    ./differences        (Windows: .\differences.exe)
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

std::vector<int> differences(std::vector<int> vec) {
    std::vector<int> diff_vec {};
    int size {static_cast<int>(vec.size())};

    // Base case if vec is size 1 or less, return empty vector
    if (size <= 1) {
        return diff_vec;
    }

    // go through each pair, starting with 1 index and 0 index
    // keep going through until the last index subtracts from second to last index
    for (int i {0}; size-1 > i; ++i) {
        int difference = vec.at(i+1) - vec.at(i);
        diff_vec.push_back(difference);
    }

    return diff_vec;
}

// =================================================================
// CHECKS (provided). Once your function exists, delete the
// [CHECKS START] and [CHECKS END] lines. Do not edit the checks.
// =================================================================


void run_checks()
{
    std::cout << "== Differences checks ==\n";
    int passed{0};
    passed += check_numbers("differences({3, 5, 9})", differences({3, 5, 9}), {2, 4});
    passed += check_numbers("differences({10, 7, 7, 12})", differences({10, 7, 7, 12}), {-3, 0, 5});
    passed += check_numbers("differences({1, 2, 3, 4, 5})", differences({1, 2, 3, 4, 5}), {1, 1, 1, 1});
    passed += check_numbers("differences({5, -2})", differences({5, -2}), {-7});
    passed += check_numbers("differences({4})", differences({4}), {});
    passed += check_numbers("differences({})", differences({}), {});
    std::cout << "Differences: " << passed << " / 6 checks passed\n";
}


int main()
{
    // Un-comment the next line together with the check block above.
    run_checks();
    return 0;
}
