#include <iostream>
#include <unordered_map>

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



    // HASHMAP
    std::unordered_map<Animal, int> animal_count;
    std::unordered_map<Animal, std::string> animal_sound;
    animal_count[Animal::DOG]++;
    animal_sound[Animal::DOG] = "woof woof";
    
    for (auto pair : animal_count) {
        std::cout << static_cast<int>(pair.first) << ": " << pair.second << "\n";
    }

    for (auto [key, value] : animal_sound) {
        std::cout << static_cast<int>(key) << " : " << value << "\n";
    }

    return 0;
}