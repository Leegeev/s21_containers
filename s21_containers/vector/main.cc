#include <iostream>
#include <stdexcept>
#include <vector>

#include "s21_vector.h"

int main(void) {
  s21::s21_vector<int> vec = {1, 2, 3};
  auto cit = vec.begin();
  *cit = 8;
  std::cout << *cit << std::endl;
  ++cit;
  *cit = 10;
  std::cout << *cit << std::endl;
  --cit;
  std::cout << *cit << std::endl;
  return 0;
}
