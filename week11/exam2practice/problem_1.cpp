#include <string>
#include <iostream>

class Dog {
public:
    Dog(std::string dog_name="Unknown") : name(dog_name) {}
    std::string name {"Unknown"};
    int age {0};

    void printNameAndAge() {
        std::cout << name << ", " << age << "\n";
    }
};

int main() {
    Dog my_dog;
    my_dog.printNameAndAge();
    return 0;
}