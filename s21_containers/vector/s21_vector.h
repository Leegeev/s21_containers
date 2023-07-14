#ifndef CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

#include <initializer_list>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>

#include "s21_iterator.h"

namespace s21 {

template <class T>
class s21_vector {
 public:
  // types
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = s21_iterator<value_type>;
  using const_iterator = s21_iterator<const value_type>;
  using reverse_iterator = s21_reverse_iterator<value_type>;
  using const_reverse_iterator = s21_reverse_iterator<const value_type>;

  // constructors and destructors
  explicit s21_vector() : size_(0U), capacity_(0U), arr_(nullptr){};

  explicit s21_vector(size_type n)
      : size_(n), capacity_(n), arr_(n ? new T[n]() : nullptr){};

  explicit s21_vector(size_type n, const T &value)
      : size_(n), capacity_(n), arr_(n ? new T[n]() : nullptr) {
    for (auto i = 0; i < size_; i++) {
      arr_[i] = value;
    }
  }

  s21_vector(std::initializer_list<value_type> const &items)
      : arr_(new T[items.size()]()),
        size_(items.size()),
        capacity_(items.size()) {
    size_type i = 0;
    for (auto element = items.begin(); element != items.end(); element++) {
      arr_[i] = *element;
      i++;
    }
  }

  s21_vector(const s21_vector &other)
      : size_(other.size_), capacity_(other.capacity_) {
    if (arr_) delete[] arr_;
    arr_ = (capacity_ ? new T[capacity_]() : nullptr);
    for (auto otherIt = other.begin(), thisIt = this->begin();
         otherIt != other.cend(); otherIt++, thisIt++) {
      *thisIt = *otherIt;
    }
  }

  s21_vector(s21_vector &&other) noexcept
      : size_(other.size_), capacity_(other.capacity_) {
    if (arr_) delete[] arr_;
    arr_ = other.arr_;
  }

  ~s21_vector() { delete[] arr_; }

  // accessors and mutators

  T at(size_type index) const {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return arr_[index];
  }
  reference operator[](size_type pos) const { return arr_[pos]; }
  size_type size() const noexcept { return size_; }
  size_type capacity() const noexcept { return capacity_; }

  reference front() noexcept { return arr_[0]; }
  reference back() noexcept { return arr_[size_ - 1]; }

  // iterators
  iterator begin() noexcept { return iterator(arr_); }
  iterator end() noexcept { return iterator(arr_ + size_); }
  const_iterator cbegin() const noexcept { return const_iterator(arr_); }
  const_iterator cend() const noexcept { return const_iterator(arr_ + size_); }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(arr_ + size_ - 1);
  }
  reverse_iterator rend() noexcept { return reverse_iterator(arr_ - 1); }
  const_reverse_iterator rcbegin() const noexcept {
    return const_reverse_iterator(arr_ + size_ - 1);
  }
  const_reverse_iterator rcend() const noexcept {
    return const_reverse_iterator(arr_ - 1);
  }

 private:
  T *arr_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
