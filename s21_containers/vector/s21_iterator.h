#ifndef CPP2_S21_CONTAINERS_VECTOR_S21_ITERATOR_H_
#define CPP2_S21_CONTAINERS_VECTOR_S21_ITERATOR_H_

#include <cstddef>
#include <iterator>

namespace s21 {
template <class T>
class s21_iterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  // constructor
  explicit s21_iterator(pointer ptr) : ptr_(ptr){};

  // compairson
  bool operator==(const s21_iterator &other) const noexcept {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const s21_iterator &other) const noexcept {
    return !(*this == other);
  }

  // increment, decrement
  s21_iterator &operator++() noexcept {
    // prefix
    ++ptr_;
    return *this;
  }

  s21_iterator operator++(int) noexcept {
    // postfix
    s21_iterator res = *this;
    ++ptr_;
    return res;
  }

  s21_iterator &operator--() noexcept {
    // prefix
    --ptr_;
    return *this;
  }

  s21_iterator operator--(int) noexcept {
    // postfix
    s21_iterator res = *this;
    --ptr_;
    return res;
  }

  // accessors
  reference operator*() const noexcept { return *ptr_; }
  pointer operator->() const noexcept { return ptr_; }

 private:
  pointer ptr_;
};

template <class T>
class s21_reverse_iterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  // constructor
  explicit s21_reverse_iterator(pointer ptr) : ptr_(ptr){};

  // compairson
  bool operator==(const s21_reverse_iterator &other) const noexcept {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const s21_reverse_iterator &other) const noexcept {
    return !(*this == other);
  }

  // increment, decrememnt
  s21_reverse_iterator &operator++() noexcept {
    // prefix
    --ptr_;
    return *this;
  }

  s21_reverse_iterator operator++(int) noexcept {
    // postfix
    s21_reverse_iterator res = *this;
    --ptr_;
    return res;
  }

  s21_reverse_iterator &operator--() noexcept {
    // prefix
    ++ptr_;
    return *this;
  }

  s21_reverse_iterator operator--(int) noexcept {
    // postfix
    s21_reverse_iterator res = *this;
    ++ptr_;
    return res;
  }

  // accessors
  reference operator*() const noexcept { return *ptr_; }
  pointer operator->() const noexcept { return ptr_; }

 private:
  pointer ptr_;
};
}  // namespace s21

#endif  //  CPP2_S21_CONTAINERS_VECTOR_S21_ITERATOR_H_
