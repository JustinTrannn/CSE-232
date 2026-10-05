#include <iostream>

int add(int x, int y);

int main() {
    std::cout << add(1, 3);
    return 0;
}

int add(int x, int y) {
    return x + y;
}