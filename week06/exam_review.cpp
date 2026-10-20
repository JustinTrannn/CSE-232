#include <iostream>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::vector<char>> Enlarge(std::vector<std::vector<char>> input) {
    // std::vector<std::vector<char>> final_vector {input};
    // std::vector<char> added_row {};
    // std::vector<char> added_col {};
    // int row_length {static_cast<int>(input.at(0).size()) - 1};
    // int col_length {static_cast<int>(input.size()) - 1};
    

    // for (int i {0}; static_cast<int>(input.at(0).size()) > i; ++i) {
    //     added_row.push_back((input.at(row_length)).at(i));
    // }

    // final_vector.push_back(added_row);

    // for (int i {0}; static_cast<int>(input.size()) > i; ++i) {
    //     added_col.push_back((input.at(i)).at(col_length));
    // }

    // for (int i {0}; static_cast<int>(input.size()) > i; ++i) {
    //     final_vector.at(i).push_back(added_col.at(i));
    // }

    // return final_vector;

    // -------------- Professor's Solution -------------------
    
    for (std::vector<char> &row : input) {
        row.push_back(row.back());
    }

    input.push_back(input.back());

    return input;


}

int main() {
  // Feel free to change the debugging code here
  std::vector<std::vector<char>> input = { 
    {'a', 'b', 'c'},
    {'D', 'E', 'F'},
  };
  std::vector<std::vector<char>> result = Enlarge(input);
  std::vector<std::vector<char>> expected = { 
    {'a', 'b', 'c', 'c'},
    {'D', 'E', 'F', 'F'},
    {'D', 'E', 'F', 'F'},
  };
  // Note the input was a 2 x 3 matrix and the result should be a 3 x 4 
  std::cout << ( result == expected ) << '\n'; // Should output 1 (true)
}