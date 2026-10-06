#include <iostream>
#include <string>

int main() {
    for (int i {0}; i < 5; i++) {
        std::cout << i << ' ';
    }

    std::string s {"Hi"};
    for (char c : s) {
        std::cout << c << "\n";
    }

    // WHILE LOOP
    int x {0};
    while (x < 3) {
        std::cout << x << "\n";
        x++;
    }

    

    for (int i {1}; i <= 3; ++i) {
        for (int j {1}; j <= 2; ++j) {
            std::cout << "i=" << i << ", j=" << j << '\n';
        }
    }




    // LOOP CONTROL
    for (int i {0}; i < 10; ++i) {
        if (i == 5) continue;   // skip this iteration
        if (i == 8) break;      // exit loop
        std::cout << i << ' ';
    }

    // READ UNTIL EOF
    std::string word {};
    while (std::cin >> word) {
        std::cout << word << "\n";
    }


    return 0;
}