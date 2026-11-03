#include "Pet.hpp"
#include <iostream>
#include <string>
#include <format>

Pet::Pet(std::string petName) : name(petName) {}

std::string Pet::getName() {
    return name;
}

int Pet::getFullness() {
    if (fullness < 0) {
        fullness = 0;
    }
    return fullness;
}

int Pet::getHappiness() {
    return happiness;
}

int Pet::getEnergy() {
    return energy;
}

int Pet::getAge() {
    return age;
}

bool Pet::rename(std::string newName) {
    if (newName == "") {
        return false;
    } else {
        name = newName;
        return true;
    }
}

bool Pet::feed(int amount) {
    if (fullness == 100) {
        return false;
    } else {
        fullness += amount;
        if (fullness > 100) {
            fullness = 100;
        }
    }
    return true;
}

bool Pet::play() {
    if (energy < 20) {
        return false;
    } else {
        happiness += 15;
        energy -= 20;
        fullness -= 10;
        return true;
    }
}

void Pet::sleep() {
    energy += 40;
    fullness -= 10;
}

void Pet::tick() {
    fullness -= 10;
    energy -= 5;
    happiness -= 5;
    age += 1;
}

bool Pet::isAlive() {
    if (fullness > 0) {
        return true;
    }
    return false;
}

std::string Pet::mood() {
    if (fullness < 30) {
        return "hungry";
    } else if (energy < 30) {
        return "tired";
    } else if (happiness < 30) {
        return "sad";
    } else if (happiness > 70) {
        return "happy";
    } else {
        return "okay";
    }
}

std::string Pet::status() {
    std::string result = std::format("{} | fullness {} energy {} happiness {} | {}", name, fullness, energy, happiness, Pet::mood());
    return result;
}