#include <unordered_map>
#include <string>
#include <iostream>

int main()
{
    std::unordered_map<std::string, int> scores{};

    scores["Alice"] = 90;
    scores["Bob"] = 82;

    std::cout << scores["Alice"] << "\n"; // prints 90

    if (scores.find("Bob") != scores.end())
    {
        std::cout << "Bob exists!";
    }

    // You can iterate through a hash map with a for loop
    for (const auto & [ key, value ] : scores) {
        std::cout << key << ": " << value << std::endl;
    }
}