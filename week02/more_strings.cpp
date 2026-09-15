#include <iostream>
#include <string>

int main() {
    std::string name {};
    std::cout << "Enter your name: ";
    std::cin >> name;                 // stops at whitespace
    if (name == "Alice") {
        std::cout << "Hello Alice!\n";
    }


    std::string line {};
    std::cout << "Enter a line: ";
    std::getline(std::cin, line);     // reads spaces too
    std::cout << "You entered: \n" << line << std::endl;


    std::string s {"hello"};
    std::cout << s.length() << "\n";   // 5 

    std::string numStr {"123"};
    int value = std::stoi(numStr);          // string -> int

    int x {42};
    std::string s2 = std::to_string(x);     // int -> string

    return 0;
}