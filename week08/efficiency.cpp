#include <iostream>
#include <vector>

bool containsLinear(std::vector<int> & numbers, int target) {
    for (int n : numbers) {
        if (n == target)
            return true; // Found
    }
    return false; // Not found
}

bool hasDuplicate(std::vector<int> & numbers) {
    for (int i = 0; i < static_cast<int>(numbers.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(numbers.size()); ++j) {
            if (numbers.at(i) == numbers.at(j)) {
                return true; // Found duplicate
            }
        }
    }
    return false;
}

int main() {
    std::vector<int> data{1, 2, 3, 4, 5, 2};
    std::cout << containsLinear(data, 4) << std::endl; // Fast
    std::cout << hasDuplicate(data) << std::endl;  // Much slower
}