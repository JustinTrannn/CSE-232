#include <iostream>

int main() {
    enum class Animal {
        DOG, // 0
        CAT, // 1
        BIRD, // 2
    };

    Animal pet = Animal::DOG;

    if (pet == Animal::DOG) {
        std::cout << "The pet is a dog\n";
    } 
    
    switch (pet) {
        case Animal::DOG:
            std::cout << "Dog\n";
            break;
    }

    std::cout << "Enum Value: " << static_cast<int>(pet) << "\n";
    return 0;

    return 0;
}