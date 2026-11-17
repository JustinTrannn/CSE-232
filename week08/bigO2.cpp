#include <vector>
#include <iostream>

int sum(std::vector<int> & v) {
    int total = 0;
    for (int x : v) {            // runs n times
        total += x;               // O(1) each
    }
    return total;                 // O(n) overall
}


void printAndCount(std::vector<int> & v) {
    for (int x : v) {             // O(n)
        std::cout << x << " ";   // treat each as O(1) for analysis
    }
    int cnt = 0;
    for (int x : v) {             // O(n)
        if (x % 2 == 0) ++cnt;
    }
    // Total: O(n) + O(n) = O(n)
}

bool hasDuplicateSlow(std::vector<int> & v) {
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {          // n
        for (int j = i + 1; j < static_cast<int>(v.size()); ++j) {  // ~n
            if (v.at(i) == v.at(j)) return true;                    // compare
        }
    }
    return false;                                              // Total: O(n^2)
}


bool containsLinear(std::vector<int> & v, int target) {
    for (int x : v) {
        if (x == target) return true; // could stop early
    }
    return false;                      // worst case: not found → checks all n
}

// RULE OF THUMB
// Drop constants: 5n + 20 → O(n)
// Keep the dominant term: n^2 + n → O(n^2)
// Sequential code adds: do A then B → O(A) + O(B)
// Nested loops multiply: loop inside a loop → O(outer × inner)
// Conditionals pick the larger branch: if/else → take the bigger Big O.