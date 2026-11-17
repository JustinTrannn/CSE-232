#include "Puppeteer.hpp"

Puppeteer::Puppeteer(std::string puppetName) : name(puppetName) {}

std::string Puppeteer::getName() {
    return name;
}

Puppet *Puppeteer::getPuppet() {
    return hand;
}

void Puppeteer::grab(Puppet &puppetAddress) {
    hand = &puppetAddress;
}

void Puppeteer::letGo() {
    hand = nullptr;
}

bool Puppeteer::perform(std::string pose) {
    if (hand == nullptr) {
        return false;
    } else {
        hand -> setPose(pose);
        return true;
    }
    return false;
}

bool Puppeteer::passTo(Puppeteer &puppeteer) {
    if (hand == nullptr || puppeteer.hand != nullptr) {
        return false;
    } else {
        puppeteer.grab(*hand);
        hand = nullptr;
        return true;
    }   
}

void Puppeteer::trade(Puppeteer &puppeteer) {
    auto placeholder = puppeteer.hand;
    puppeteer.hand = hand;
    hand = placeholder;
}