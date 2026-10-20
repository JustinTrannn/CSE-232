// This is the implementation file. Be sure to include the header.

#include "math_util.hpp"

int mult(int a, int b) {
    return a * b;
}

int pow(int a, int b) {
    int answer {1};
    for (int i{1}; i <= b; ++i) {
        answer = answer * a;
    }
    return answer;
}