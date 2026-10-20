/* 
Write a function named split_sum() that takes 3 input arguments:​

* Integer x​
* A reference to an integer called even_sum​
* A reference to an integer called odd_sum​

The function should add x to even_sum if x is even, or to odd_sum if x is odd.​
*/

#include <iostream>

void split_sum(int x, int &even_sum, int &odd_sum) {
    // If even, add x to even sum
    if (x % 2 == 0) {
        even_sum += x;
    } else {
        // If odd, add x to odd sum
        odd_sum += x;
    }
}

int main()
{
  // Feel free to add debugging code here
  int even_sum{0};
  int odd_sum{0};
  split_sum(4, even_sum, odd_sum);
  split_sum(4, even_sum, odd_sum);
  split_sum(5, even_sum, odd_sum);
  std::cout << even_sum << ' ' << odd_sum << std::endl;
  // Should print "8 5";
  return 0;
}
