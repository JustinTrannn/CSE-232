#pragma once

#include <string>

struct Node {
    std::string rider{};
    Node *next{};

    Node(const std::string& r) : rider(r), next(nullptr) {}
};

class RollerCoaster {
private:
    Node *head{};
    Node *tail{};

public:
    RollerCoaster();
    ~RollerCoaster();
    void addRider(const std::string& riderName);
    void ride();
    void print() const;
    bool empty() const;
};
