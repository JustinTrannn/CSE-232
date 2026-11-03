#include <iostream>
#include <string>

int main()
{
    int age{25};  // An integer variable
    int copy{age}; // A copy of the variable age - separate memory space
    int &r{age};  // A reference (alias) to 'age' - shares the same memory
    int *p{age}; // A pointer storing the address of 'age' in memory

    std::cout << "age: " << age << "\n";
    std::cout << "r: " << r << "\n";
    std::cout << "p: " << p << "\n";
    std::cout << "Value in p: " << *p << "\n";

    return 0;
}