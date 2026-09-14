#include <iostream>

void displayBigger(int num1, int num2) {
    if (num1 > num2) {
        std::cout << num1 << " is bigger\n";
    } else if (num2 > num1) {
        std::cout << num2 << " is bigger\n";
    } else {
        std::cout << "They are equal\n";
    }   
    return;
}

double returnBigger(int num1, int num2) {
if (num1 > num2) {
        return num1;
    } else if (num2 > num1) {
        return num2;
    }
    
}

int main() {
    int num1 {9}, num2 {34};

    displayBigger(num1, num2);




    return 0;
}