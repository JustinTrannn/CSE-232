#pragma once
#include "Puppet.hpp"
#include <string>

class Narrator {
private:
    Puppet &star;
public:
    Narrator(Puppet& starPuppet) : star{starPuppet} {}

    std::string getStarName() {
        return star.getName();
    }

    void cue(std::string pose) {
        star.setPose(pose);
    }

    Puppet &getStar() {
        return star;
    }

};