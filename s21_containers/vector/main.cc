#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

#include "s21_vector.h"

int main(void) {
  s21::s21_vector<int> vecs = {1, 2, 3};
  std::cout << "vecs.size()=" << vecs.size() <<"\tvecs.capacity()=" << vecs.capacity() << std::endl;
  vecs.resize(7, 10);
  std::cout << "vecs.size()=" << vecs.size() <<"\tvecs.capacity()=" << vecs.capacity() << std::endl;
  for (auto it = vecs.cbegin(); it != vecs.cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  vecs.resize(2);
  std::cout << "vecs.size()=" << vecs.size() <<"\tvecs.capacity()=" << vecs.capacity() << std::endl;
  for (auto it = vecs.cbegin(); it != vecs.cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  
  return 0;
}
