// references.cpp
// Lab 09, Milestone 1: References
//
// Build:  g++ -std=c++20 -Wall references.cpp -o references
// Run:    ./references        (Windows: .\references.exe)
//
// Written by:  (your name)

#include <iostream>
#include <string>
#include <vector>

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

// Gives every distinct address a small box number, in the order it is first seen,
// so the checks can show which variables share a box.
std::vector<const void*> seenAddresses{};
std::string box(const void* address)
{
    if (address == nullptr)
    {
        return "nullptr";
    }
    for (size_t i{0}; i < seenAddresses.size(); ++i)
    {
        if (seenAddresses.at(i) == address)
        {
            return "#" + std::to_string(i + 1);
        }
    }
    seenAddresses.push_back(address);
    return "#" + std::to_string(seenAddresses.size());
}

// Provided on purpose: this takes score BY VALUE, so it changes a copy.
// The checks show what that does. Compare it with your addPoints.
void addPointsToCopy(int score, int points)
{
    score = score + points;
}

// =================================================================
// YOUR CODE. Write your functions here, above the CHECKS line.
// =================================================================

void addPoints(int &score, int points) {
    score += points;
}

bool sameBox(int &a, int &b) {
    if (&a == &b) {
        return true;
    } else {
        return false;
    }
}

void swapValues(int &a, int &b) {
    int temp {a};
    a = b;
    b = temp;
}

int &pickLarger(int &a, int &b) {
    if (a > b) {
        return a;
    } else if (b > a) {
        return b;
    } else {
        return a;
    }
}

// =================================================================
// CHECKS (provided). Once a group's functions exist, delete its
// [GROUP n START] and [GROUP n END] lines and un-comment its call in main.
// Do not edit the checks.
// =================================================================

// [GROUP 1 START] delete this line and the [GROUP 1 END] line below to enable
int group_1()
{
    std::cout << "== Group 1: addPoints ==\n";
    int passed{0};
    int score{10};
    std::cout << "  score lives in box " << box(&score) << " and holds 10\n";
    addPointsToCopy(score, 5);
    std::cout << "  [NOTE] after addPointsToCopy(score, 5), score is still " << score << ": the function changed a copy\n";
    addPoints(score, 5);
    passed += check("score after addPoints(score, 5)", score, 15);
    addPoints(score, 5);
    passed += check("score after a second addPoints(score, 5)", score, 20);
    std::cout << "Group 1: " << passed << " / 2\n\n";
    return passed;
}


// [GROUP 2 START] delete this line and the [GROUP 2 END] line below to enable
int group_2()
{
    std::cout << "== Group 2: sameBox ==\n";
    int passed{0};
    int x{5};
    int y{5};
    int& r{x};
    int c{x};
    std::cout << "  x is box " << box(&x) << ", r is box " << box(&r) << ", y is box " << box(&y) << ", c is box " << box(&c) << "\n";
    passed += check("sameBox(x, x)", sameBox(x, x), true);
    passed += check("sameBox(x, r)   r is a reference to x", sameBox(x, r), true);
    passed += check("sameBox(x, y)   same value, different box", sameBox(x, y), false);
    passed += check("sameBox(x, c)   c is a copy of x", sameBox(x, c), false);
    std::cout << "Group 2: " << passed << " / 4\n\n";
    return passed;
}


// [GROUP 3 START] delete this line and the [GROUP 3 END] line below to enable
int group_3()
{
    std::cout << "== Group 3: swapValues and pickLarger ==\n";
    int passed{0};
    int a{3};
    int b{9};
    swapValues(a, b);
    passed += check("a after swapValues(a, b)", a, 9);
    passed += check("b after swapValues(a, b)", b, 3);

    int x{3};
    int y{9};
    std::cout << "  x is box " << box(&x) << ", y is box " << box(&y)
              << ", pickLarger(x, y) refers to box " << box(&pickLarger(x, y)) << "\n";
    passed += check("pickLarger(x, y)", pickLarger(x, y), 9);
    pickLarger(x, y) = 0;
    passed += check("y after pickLarger(x, y) = 0", y, 0);
    passed += check("x after pickLarger(x, y) = 0", x, 3);
    int e1{4};
    int e2{4};
    passed += check("pickLarger(e1, e2) is e1 when they are equal", &pickLarger(e1, e2) == &e1, true);
    std::cout << "Group 3: " << passed << " / 6\n\n";
    return passed;
}


int main()
{
    int total{0};
    // Un-comment each call together with its group above.
    total += group_1();
    total += group_2();
    total += group_3();
    std::cout << "References: " << total << " / 12 checks passed\n";
    return 0;
}
