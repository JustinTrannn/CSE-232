#include <iostream>
#include <string>

int main() {
    std::string text {"Hello World"};

    // Length
    std::cout << text.size() << '\n';        // 11

    // Access characters safely
    std::cout << text.at(0) << '\n';         // 'H'

    // Substrings
    std::cout << text.substr(0, 5) << '\n';  // "Hello"

    // Searching
    std::cout << text.find("World") << '\n'; // 6 (index of match)
}