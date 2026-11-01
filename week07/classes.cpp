#include <iostream>
#include <string>

class Person {
public:
    std::string name {"Alice"};
    int age {20};

    void introduce() {
        std::cout << "Hi, I'm " << name << " and I'm " << age << " years old." << std::endl;
    }
};

int main() {
    Person a;
    a.introduce();

    Person b;
    b.age = 18;
    b.name = "Alex";
    b.introduce();

    return 0;
}