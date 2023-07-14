#include <iostream>
#include <stdexcept>
#include <vector>

#include "s21_vector.h"

int main(void) {
  s21::s21_vector<int> vec = {1, 2, 3};
  for (s21::s21_vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  for (s21::s21_vector<int>::reverse_iterator it = vec.rbegin();
       it != vec.rend(); it++) {
    std::cout << *it << " ";
  }
  std::cout << "\n";
  return 0;
}
