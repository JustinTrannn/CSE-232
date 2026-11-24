#include "RollerCoaster.hpp"
#include <iostream>

RollerCoaster::RollerCoaster() : head{nullptr}, tail{nullptr} {}

RollerCoaster::~RollerCoaster() {
    while (head) {
        Node *temp{head};
        head = head->next;
        delete temp;
    }
    tail = nullptr;
} 

bool RollerCoaster::empty() const
{ 
    // if the head of the rollercoaster is nullptr, then return true
    return head == nullptr;
}
  
void RollerCoaster::addRider(const std::string& riderName)
{
    // check if it's empty. if it's empty, make head point to rider
    // if it's not empty, make the tail point to rider and then turn rider into tail
    Node* newNode = new Node(riderName);
    if (empty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail -> next = newNode;
        tail = newNode;
    }
}

void RollerCoaster::ride()
{
    // check if it's empty or only one person in line. if it's empty do nothing
    // if it's not empty, remove the first in line and move head up one. Remove the next in line and move head up one.
    if (head == nullptr || head->next == nullptr) {
        std::cout << "Not enough riders for the RollerCoaster!\n";
        return;
    }
    Node* firstRider {head};
    Node* secondRider = head -> next;
    std::cout << firstRider -> rider << " and " << secondRider->rider << " are riding!\n";

    head = secondRider -> next;
    delete firstRider;
    delete secondRider;

    if (head == nullptr) {
        tail = nullptr;
    }
}

void RollerCoaster::print() const
{
    // Start from head and move down the line of pointers and print each rider
    // while loop: temp pointer which is head. temp pointer prints name and then moves forward
    if (empty()) {
        std::cout << "Line is empty!\n";
    }

    Node* current {head};
    std::cout << "Line: \n";
    while (current != nullptr) {
        std::cout << current->rider;
        if (current -> next != nullptr) {
            std::cout << "->";
        }
        current = current->next;
    }

}