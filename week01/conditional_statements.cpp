#include <iostream>

int main() {
    int x;
    std::cout << "Enter a number: ";

    std::cin >> x;

    if (x > 10) {
        std::cout << "Your number is greater than 10\n";
    }

    if (x < 10) {
        std::cout << "Your number is less than 10\n";
    }

    if (x == 10) {
        std::cout << "Your number is 10\n";
    }

    if (x >= 10 && x % 2 == 0) {
        std::cout << "Your number is greater or equal to 10 and is divisible by 2\n";
    }

    if (x > 10) {
        std::cout << "X is a large number\n";
    } else if (x < 10) {
        std::cout << "X is a small number";
    } else {
        std::cout << "X is 10";
    }

    // The operation || means "OR"
    // The operation != means "not equal"
    // The operation && means "AND"

    return 0;
}