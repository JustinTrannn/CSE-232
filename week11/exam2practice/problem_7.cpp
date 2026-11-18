#include <vector>
#include <string>
#include <iostream>

class Item {
public:
    std::string name {};
    double price {};

    Item(std::string n, double p) : name(n), price(p) {}
};

int main() {
    Item milk("Milk", 2.50);
    Item bread("Bread", 1.50);
    Item eggs("Eggs", 3.00);
    std::vector<Item> my_items {milk, bread, eggs};

    double total_price {};
    for (Item item : my_items) {
        total_price += item.price;
    }
    std::cout << "Total: " << total_price << "\n";

    return 0;
}