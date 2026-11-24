#include <iostream>
#include <vector>

void bubbleSort(std::vector<int> &arr)
{
    bool swapped{};
    for (int i{0}; i < static_cast<int>(arr.size()) - 1; ++i)
    {
        swapped = false;
        for (int j{0}; j < static_cast<int>(arr.size()) - i - 1; ++j)
        {
            if (arr.at(j) > arr.at(j + 1))
            {
                int temp{arr.at(j)};
                arr.at(j) = arr.at(j + 1);
                arr.at(j + 1) = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break; // optimization: stop if already sorted
    }
}

void bubbleSortDescending(std::vector<int> &arr) {
    bool swapped {};

    for (int i{0}; static_cast<int>(arr.size()) - 1 > i; ++i) {
        swapped = false;
        for (int j{0}; static_cast<int>(arr.size()) - 1 > j; ++j) {
            if (arr.at(j+1) > arr.at(j)) {
                int temp {arr.at(j)};
                arr.at(j) = arr.at(j+1);
                arr.at(j+1) = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main()
{
    std::vector<int> nums{5, 1, 4, 2, 8};
    bubbleSort(nums);
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << "\n";

    bubbleSortDescending(nums);
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << "\n";


    return 0;
}