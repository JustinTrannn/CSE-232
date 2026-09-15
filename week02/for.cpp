#include <iostream>
#include <string>

int main() {
    for (int i {0}; i < 5; i++) {
        std::cout << i << ' ';
    }

    std::string s {"Hi"};
    for (char c : s) {
        std::cout << c << "\n";
    }

    return 0;
}