#include <iostream>
#include <string>

int main() {
    int size{0};
    std::cout << "Enter a size: ";
    std::cin >> size;

    std::string line {"*"};

    for (int i = 0; i < size; ++i) {
        std::cout << line << "\n";
        line += "*";
    }

    return 0;
}