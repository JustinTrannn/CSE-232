#pragma once
#include <string>

class Pet {
    private:
        std::string name {""};
        int fullness {50};
        int energy {50};
        int happiness {50};
        int age {};

    public:
        Pet(std::string petName);
        std::string getName();
        int getFullness();
        int getHappiness();
        int getEnergy();
        int getAge();
        bool rename(std::string newName);
        bool feed(int amount);
        bool play();
        void sleep();
        void tick();
        bool isAlive();
        std::string mood();
        std::string status();
};