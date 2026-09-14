#include <iostream>

int add(int a, int b) {
    return a + b;
}

void greet() {
    std::cout << "Hello from a function\n";
}

int main() {
    greet();
    std::cout << add(2, 5) << "\n";

    int x, y;
    std::cout << "Enter 2 numbers\n";
    std::cin >> x >> y;
    std::cout << "Your numbers added together equal: " << add(x, y);
    return 0;
}