#include <iostream>
#include <string>

int main() {
    int count = 0;
    std::string line;
    while(std::getline(std::cin, line)) {
        for(size_t i = 0; i < line.size(); ++i) {
            if(line[i] == 'a' || line[i] == 'A') {
                ++count;
            }
        }
    }

    std::cout << "amount of letters a and A: " <<  count << std::endl;
    return 0;
}