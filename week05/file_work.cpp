#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ofstream out {"data.txt"};  // default: truncates file
    out << "Hello File!";
    out.close();

    std::ifstream in {"data.txt"};
    std::string line;
    std::getline(in, line);
    std::cout << line;
    
    return 0;
}