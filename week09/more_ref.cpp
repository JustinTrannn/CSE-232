#include <iostream>
#include <string>

int main() {
    int number{10};
    int &ref{number};   // ref is another name for number

    ref = 20;  // modifies number
    std::cout << number; // prints 20

    return 0;
}