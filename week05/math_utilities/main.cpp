// This is where you use the header. Be sure to include the header file.

#include <iostream>
#include "math_util.hpp"

int main()
{
    int a{};

    std::cout << "Enter a number: \n";
    std::cin >> a;

    int b{};

    std::cout << "Enter a number: \n";
    std::cin >> b;

    std::cout << mult(a, b) << "\n";
    std::cout << pow(a, b) << "\n";
    return 0;
}