#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> v1; // EMPTY VECTOR
    std::vector<int> v2 {1, 2, 3}; // initialized with values 1, 2, and 3
    std::vector<int> v3 (5, 10); // 5 elements, each with a value of 10

    v1.push_back(7);
    v1.push_back(8); // v1 now contains {7, 8}

    std::cout << v2[0] << " "; // direct access
    // std::cout << v2[1000] << " "; // it will give an error
    std::cout << v2.at(1);

    for (size_t i {0}; i < v2.size(); ++i) {
        std::cout << v2.at(i) << "\n";
    }



    std::vector<std::string> names {"Charlie", "Bob"};
    names.push_back("Joe");


    // Matrix vectors
    std::vector<std::vector<int>> matrix{
        {1, 2},
        {3, 4}};

    for (unsigned int i{0}; i < matrix.size(); i++)
    {
        for (unsigned int j{0}; j < matrix.at(i).size(); j++)
        {
            std::cout << matrix.at(i).at(j) << ' ';
        }
        std::cout << '\n';
    }




    std::vector<int> numbers {1, 2, 3, 4, 5};
    std::cout << numbers.size();   // number of elements
    numbers.clear();               // remove all elements

    return 0;
}