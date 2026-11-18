#include <iostream>

class BankAccount {
private:
    int balance {};

public:
    void depost(int amount) {
        balance += amount;
        std::cout << "Balance: $" << balance << "\n";
    }
};

