#include <iostream>
#include <iomanip>
#include <vector>

int recursiveSum(std::vector<int> nums, int index);
double average(int total, int count);
double average(double total, int count);
void printResult(std::string label, double value, int precision = 2);

int main()
{   
    std::vector<int> nums {};
    int value {};

    while (std::cin >> value) {
        nums.push_back(value);
    }

    int total = recursiveSum(nums, 0);
    std::cout << "Recursive Sum: " << total << "\n";

    std::cout << nums.size() << "\n";
    return 0;
}

int recursiveSum(std::vector<int> ints, int index)
{
    if (index == ints.size())
    {
        return 0;
    }
    return ints.at(index) + recursiveSum(ints, index + 1);
}