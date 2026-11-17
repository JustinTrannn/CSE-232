#include "Stack.hpp"

Stack::Stack() : topNode(nullptr), n(0) {}

Stack::~Stack()
{
    while (topNode)
    {
        Node *temp{topNode};
        topNode = topNode->next;
        delete temp;
    }
    n = 0;
}

bool Stack::empty() { return topNode == nullptr; }

int Stack::size() { return n; }

void Stack::push(int v)
{
    Node *newNode{new Node{v, topNode}};
    topNode = newNode;
    n++;
}

bool Stack::pop(int &out)
{
    if (empty())
        return false;
    Node *temp{topNode};
    out = temp->value;
    topNode = topNode->next;
    delete temp;
    n--;
    return true;
}

bool Stack::peek(int &out)
{
    if (empty())
        return false;
    out = topNode->value;
    return true;
}