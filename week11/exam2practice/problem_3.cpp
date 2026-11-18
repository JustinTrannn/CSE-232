#include <iostream>

class Point {
private:
    int x {};
    int y {};

public:
    Point(int nx, int ny) : x(nx), y(ny) {}

    void print() {
        std::cout << "(" << x << ", " << y << ")" << "\n";
    }
};

int main() {
    Point p(3, 4);
    p.print();
    return 0;
}