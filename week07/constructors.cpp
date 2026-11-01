#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age{}; // Make sure to initialize member variables!

public:
    Person() : name(""), age(0) {} // Default Constructor

    Person(std::string n, int a) {
        name = n;
        age = a;
    }

    void introduce() {
        std::cout << "Hi, I'm " << name << " and I'm " << age << " years old." << std::endl;
    }
};

int main() {
    Person p("Alice", 20); // constructor is called automatically
    p.introduce();
}