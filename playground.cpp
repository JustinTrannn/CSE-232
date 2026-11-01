#include <iostream>
#include <string>
#include <vector>
#include <cctype>

int main() {
    std::vector<char> characters {};
    std::string user_input {};

    std::getline(std::cin, user_input);

    for (int i {0}; static_cast<int>(user_input.size()) > i; ++i) {
        if (i > 0) {
            int user_input_char = user_input.at(i);
            int character_char = characters.back();
            if (user_input_char > character_char) {
                characters.push_back(user_input.at(i));
            } else {
                characters.push_back('_');
            }
        } else {
            characters.push_back(user_input.at(i));
        }
    }

    for (char c : characters) {
        std::cout << c;
    }


    return 0;
}