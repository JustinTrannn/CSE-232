#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream in {"inputFile.txt"};

    if (!in)
    {
        // the file could not be opened
        std::cout << "File couldn't be opened.\n";
        return 1;
    }

    std::string aWord{};
    int count{0};

    while (in >> aWord)
    {
        if (aWord.length() >= 5)
        {
            ++count;
            std::cout << aWord << " ";
        }
    }

    std::cout << "The number of words is " << count << "\n";
    return 0;
}