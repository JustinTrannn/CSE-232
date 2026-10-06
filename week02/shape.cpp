#include <iostream>

int main() {
    int size {};
    std::cout << "Give me a size: ";
    std::cin >> size;

    for (int i {1}; size >= i; ++i) {
        for (int j {1}; j <= i; ++j) {
            std::cout << "* ";
        }
        std::cout << "\n";
    }



    return 0;
}