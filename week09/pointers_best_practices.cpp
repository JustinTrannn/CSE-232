#include <iostream>

void print(const int &value) { 
    std::cout << value; // safe, read-only reference
} 

void addOne(int &value) {
    ++value; // allows modification
} 

int main() {
    int *p{}; // safe initialization

    if (p != nullptr) {
        std::cout << *p;
    }

    // int* getPointer() {
    //     int x{10};
    //     return &x; // ❌ BAD: x is destroyed when the function ends
    // }
}