#include <iostream>

int main() {
    int bad_practice; // might cause undefined behavior

    int x = 5; // copy assignment style
    int y (5); // direct initialization style

    int a {5};
    int b { }; // initialized to 0

    int good {5};
    // int bad {3.5}; // error! double to int narrowing

    int risky = 3.5; // compiles to be 3. Int to double

    std::cout << bad_practice << " " << x << " " << y << " " << a << " " << b << " " << good << " " << risky << std::endl;

    return 0;
}