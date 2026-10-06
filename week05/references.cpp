#include <iostream>

void update(int &ref) {
    ref += 10;
}

int main() {
    int x {5};
    update(x);
    std::cout << x;  // 15
    return 0;
}