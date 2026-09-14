// Write a program that calculates the area of a circle with a radius equal to 10.
// You can assume PI to be 3.14

// Write a program that calculates the area of a circle with a radius given by the user.
// You can assume PI to be 3.14.

// Write a function named calculateArea() that calculates the area of a circle with a
// radius given by the user. You can assume PI to be 3.14.​

#include <iostream>


int main() {
    int num1 {10}, num2 {3};

    std::cout << num1 + num2 << "\n";
    std::cout << num1 % num2 << "\n";

    std::cout << "Enter 2 more numbers: ";
    std::cin >> num1 >> num2;
    std::cout << num1 + num2 << "\n";
    std::cout << num1 % num2 << "\n";

    if (num1 > num2) {
        std::cout << num1 << " is bigger\n";
    } else if (num2 > num1) {
        std::cout << num2 << " is bigger\n";
    } else {
        std::cout << "They are equal\n";
    }   


    return 0;
}