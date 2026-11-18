#include <iostream>

class Box {
private:
    int length {};
    int width {};
    int height {};
public:
    Box(int l, int w, int h) : length(l), width(w), height(h) {}

    int volume() {
        return length*width*height;
    }

    bool isLargerThan(Box &other) {
        if (volume() > other.volume()) {
            return true;
        } else {
            return false;
        }
    }
};

