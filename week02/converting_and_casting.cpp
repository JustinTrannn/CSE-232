#include <iostream>

int main() {
    int i {42};
    double d = i;              // int -> double (42.0)

    char c {'A'};
    int code = c;              // char -> int (ASCII value)

    bool flag = i;             // nonzero int -> true
    int back = flag;           // true -> 1

    double pi {3.14};
    int truncated = pi;        // double -> int (loses fractional part)

    int n = (int)pi;   // works, but not explicit about intent
    int n2 = static_cast<int>(pi);   // safer, clearer
    
    return 0;
}