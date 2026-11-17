#pragma once
#include "Puppet.hpp"
#include <string>

class Puppeteer {
private:
    std::string name;
    Puppet *hand = nullptr;
public:
    Puppeteer(std::string puppetName);
    std::string getName();
    Puppet *getPuppet();
    void grab(Puppet &hand);
    void letGo();
    bool perform(std::string pose);
    bool passTo(Puppeteer &puppeteer);
    void trade(Puppeteer &puppeteer);
};