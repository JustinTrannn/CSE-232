#include <vector>
#include <iostream>

// O(1): constant time
int getFirst(std::vector<int> & v) {
    return v.at(0);
}

// O(n): one loop through all elements
int sum(std::vector<int> & v) {
    int total = 0;
    for (int x : v) total += x;
    return total;
}

// O(n²): two nested loops
void printPairs(std::vector<int> & v) {
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        for (int j = 0; j < static_cast<int>(v.size()); ++j) {
            std::cout << v.at(i) << "," << v.at(j) << " ";
        }
    }
}

bool binarySearch(std::vector<int> &data, int target) {
    int low = 0;
    int high = static_cast<int>(data.size() - 1);
    int count {1};
    while (low <= high) {
        std::cout << "Loop #" << count << "\n";
        int mid = ((low + high) / 2);
        if (data.at(static_cast<size_t>(mid)) == target) return true;
        if (data.at(static_cast<size_t>(mid)) < target) {
            low = mid + 1;
            std::cout << "Low = " << low << "\n";
        } else {
            high = mid - 1;
            std::cout << "High = " << low << "\n";
        }
        count++;
    }
    return false;
}

int main() {
    std::vector<int> data {3, 24, 450, 49, 199, 305, 44, 958, 88, 285, 293, 694, 33};
    std::cout << binarySearch(data, 3);
    
}