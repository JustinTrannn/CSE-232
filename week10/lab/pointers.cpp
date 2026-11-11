// pointers.cpp
// Lab 09, Milestone 2: Pointers
//
// Build:  g++ -std=c++20 -Wall pointers.cpp -o pointers
// Run:    ./pointers        (Windows: .\pointers.exe)
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
// so the checks can show where a pointer points.
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

// Reads through a pointer only if it is not nullptr; -1 otherwise.
int valueAt(const int* p)
{
    if (p == nullptr)
    {
        return -1;
    }
    return *p;
}

// =================================================================
// YOUR CODE. Write your functions (and, for honors, the Tally class)
// here, above the CHECKS line.
// =================================================================

void swapThroughPointers(int *a, int *b) {
    int temp {*a};
    *a = *b;
    *b = temp;
}

int *pointToLarger(int *a, int *b) {
    if (*b > *a) {
        return b;
    } else {
        return a;
    }
}

bool readSafely(int *value, int &out) {
    if(value == nullptr) {
        return false;
    } else {
        out = *value;
        return true;
    }
}

int sumThrough(std::vector<int*> pointers) {
    int sum {0};
    for (int* x : pointers) {
        if (x == nullptr) {
            continue;
        } else {
            sum += *x;
        }
    }
    return sum;
}

int* findFirstEven(std::vector<int>& numbers) {
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers.at(i) % 2 == 0) {
            return &numbers.at(i); 
        }
    }
    return nullptr;
}

// =================================================================
// CHECKS (provided). Once a group's functions exist, delete its
// [GROUP n START] and [GROUP n END] lines and un-comment its call in main.
// Do not edit the checks.
// =================================================================

// [GROUP 1 START] delete this line and the [GROUP 1 END] line below to enable
int group_1()
{
    std::cout << "== Group 1: swapThroughPointers and pointToLarger ==\n";
    int passed{0};
    int a{3};
    int b{9};
    swapThroughPointers(&a, &b);
    passed += check("a after swapThroughPointers(&a, &b)", a, 9);
    passed += check("b after swapThroughPointers(&a, &b)", b, 3);

    int x{3};
    int y{9};
    int* larger{pointToLarger(&x, &y)};
    std::cout << "  x is box " << box(&x) << ", y is box " << box(&y) << ", pointToLarger(&x, &y) points to " << box(larger) << "\n";
    passed += check("pointToLarger(&x, &y) points to y", larger == &y, true);
    passed += check("*pointToLarger(&x, &y)", valueAt(larger), 9);
    int e1{4};
    int e2{4};
    passed += check("pointToLarger(&e1, &e2) points to e1 when they are equal", pointToLarger(&e1, &e2) == &e1, true);
    std::cout << "Group 1: " << passed << " / 5\n\n";
    return passed;
}


// [GROUP 2 START] delete this line and the [GROUP 2 END] line below to enable
int group_2()
{
    std::cout << "== Group 2: readSafely and sumThrough ==\n";
    int passed{0};
    int value{42};
    int out{-1};
    passed += check("readSafely(&value, out) returns true", readSafely(&value, out), true);
    passed += check("out after readSafely(&value, out)", out, 42);
    int untouched{7};
    passed += check("readSafely(nullptr, untouched) returns false", readSafely(nullptr, untouched), false);
    passed += check("untouched stays 7 after readSafely(nullptr, untouched)", untouched, 7);

    int p{1};
    int q{2};
    int r{3};
    std::vector<int*> pointers{&p, nullptr, &q, &r, nullptr};
    std::cout << "  pointers: " << box(&p) << ", nullptr, " << box(&q) << ", " << box(&r) << ", nullptr\n";
    passed += check("sumThrough({&p, nullptr, &q, &r, nullptr})", sumThrough(pointers), 6);
    std::vector<int*> none{};
    passed += check("sumThrough({})", sumThrough(none), 0);
    std::cout << "Group 2: " << passed << " / 6\n\n";
    return passed;
}


// [GROUP 3 START] delete this line and the [GROUP 3 END] line below to enable
int group_3()
{
    std::cout << "== Group 3: findFirstEven ==\n";
    int passed{0};
    std::vector<int> numbers{7, 3, 8, 5, 6};
    int* found{findFirstEven(numbers)};
    std::cout << "  numbers.at(2) is box " << box(&numbers.at(2)) << ", findFirstEven(numbers) points to " << box(found) << "\n";
    passed += check("findFirstEven({7, 3, 8, 5, 6}) points to the 8 at position 2", found == &numbers.at(2), true);
    if (found != nullptr)
    {
        *found = 80;
    }
    passed += check("numbers.at(2) after writing 80 through the pointer", numbers.at(2), 80);
    std::vector<int> odds{1, 3, 5};
    passed += check("findFirstEven({1, 3, 5}) is nullptr", findFirstEven(odds) == nullptr, true);
    std::cout << "Group 3: " << passed << " / 3\n\n";
    return passed;
}


/* [HONORS START] delete this line and the [HONORS END] line below to enable
int group_honors()
{
    std::cout << "== Honors: Tally with this ==\n";
    int passed{0};
    Tally tally{};
    tally.add(2).add(3).add(4);
    passed += check("total() after add(2).add(3).add(4)", tally.total(), 9);
    std::cout << "  tally is box " << box(&tally) << ", tally.add(1) returned box " << box(&tally.add(1)) << "\n";
    passed += check("add() returns the same Tally it was called on", &tally.add(1) == &tally, true);
    passed += check("total() after two more add(1)", tally.total(), 11);
    std::cout << "Honors: " << passed << " / 3\n\n";
    return passed;
}
[HONORS END] */

int main()
{
    int total{0};
    // Un-comment each call together with its group above.
    total += group_1();
    total += group_2();
    total += group_3();
    std::cout << "Pointers: " << total << " / 14 checks passed\n";
    // Honors section only: un-comment the next two lines together with the HONORS group above.
    // int honors{group_honors()};
    // std::cout << "Honors: " << honors << " / 3 checks passed\n";
    return 0;
}
