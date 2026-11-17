#pragma once
#include <iostream>

struct Node
{
    int value{};
    Node *next{};
};

class Stack
{
private:
    Node *topNode{}; // pointer to the top of the stack
    int n{};         // number of elements

public:
    Stack();
    ~Stack(); // destructor to release memory
    bool empty();
    int size();
    void push(int v);
    bool pop(int &out);
    bool peek(int &out);
};