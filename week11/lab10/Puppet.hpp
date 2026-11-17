// Puppet.hpp
// Lab 10: The Puppet Show. PROVIDED. Do not edit.
//
// One puppet on the stage. A puppet cannot move by itself: something has to
// call setPose on it.

#pragma once

#include <string>

class Puppet
{
public:
    Puppet(std::string puppetName)
    {
        name = puppetName;
    }

    std::string getName()
    {
        return name;
    }

    // "stand", "wave", "cheer", "bow", "sit" or "jump". Every puppet starts
    // out standing.
    std::string getPose()
    {
        return pose;
    }

    void setPose(std::string newPose)
    {
        pose = newPose;
    }

private:
    std::string name{};
    std::string pose{"stand"};
};
