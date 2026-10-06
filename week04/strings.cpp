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

    if (text.find("World") == std::string::npos) {
        std::cout << "Substring not found!";
    }

    std::string s1 {"Hello"};
    std::string s2 {"C++"};
    std::string combined = s1 + " " + s2;  // Concatenation

    s1.append(" there");                   // "Hello there"
    s1.insert(5, ",");                     // "Hello, there"
    s1.erase(5, 1);                        // "Hello there"
    s1.replace(6, 5, "World");             // "Hello World"

    std::cout << combined << '\n';
    std::cout << s1 << '\n';
}