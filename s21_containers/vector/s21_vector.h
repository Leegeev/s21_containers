#ifndef CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>

namespace s21 {

template <class T>
class s21_vector {
 public:
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

    // operators
    s21_iterator operator+(int n) noexcept {
      s21_iterator res = *this;
      ptr_ += n;
      return res;
    }

    s21_iterator &operator-(int n) noexcept {
      s21_iterator res = *this;
      ptr_ -= n;
      return res;
    }

    difference_type operator-(const s21_iterator &other) noexcept {
      return ptr_ - other.ptr_;
    }

    difference_type operator+(const s21_iterator &other) noexcept {
      return ptr_ + other.ptr_;
    }

    // accessors
    reference operator*() const noexcept { return *ptr_; }
    pointer operator->() const noexcept { return ptr_; }

   private:
    pointer ptr_;
  };

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

    // operators
    s21_reverse_iterator operator+(int n) noexcept {
      s21_iterator res = *this;
      ptr_ -= n;
      return res;
    }

    s21_reverse_iterator &operator-(int n) noexcept {
      s21_iterator res = *this;
      ptr_ += n;
      return res;
    }

    difference_type operator-(const s21_reverse_iterator &other) noexcept {
      return ptr_ + other.ptr_;
    }

    difference_type operator+(const s21_reverse_iterator &other) noexcept {
      return ptr_ - other.ptr_;
    }

    // accessors
    reference operator*() const noexcept { return *ptr_; }
    pointer operator->() const noexcept { return ptr_; }

   private:
    pointer ptr_;
  };
  // types
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = s21_iterator;
  using const_iterator = s21_iterator;
  using reverse_iterator = s21_reverse_iterator;
  using const_reverse_iterator = s21_reverse_iterator;

  // constructors and destructors
  explicit s21_vector() : arr_(nullptr), size_(0U), capacity_(0U){};

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

  reference at(size_type index) const {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return arr_[index];
  }
  reference operator[](size_type pos) const { return arr_[pos]; }
  reference front() noexcept { return arr_[0]; }
  reference back() noexcept { return arr_[size_ - 1]; }
  pointer data() noexcept { return arr_; }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }
  void reserve(size_type new_capacity) {
    if (new_capacity > capacity_) {
      if (new_capacity > max_size())
        throw std::out_of_range("value out of range");
      pointer new_arr = new value_type[new_capacity];
      std::copy(arr_, arr_ + size_, new_arr);
      delete[] arr_;
      arr_ = new_arr;
      capacity_ = new_capacity;
    }
  }
  size_type capacity() const noexcept { return capacity_; }
  void shrink_to_fit() {
    if (size_ < capacity_) {
      pointer new_arr = new value_type[size_];
      std::copy(arr_, arr_ + size_, new_arr);
      delete[] arr_;
      arr_ = new_arr;
      capacity_ = size_;
    }
  }

  void clear() noexcept { size_ = 0U; }

  iterator insert(iterator pos, const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    size_type index = pos - begin();
    iterator new_pos = begin() + index;
    for (auto it = end(); it != new_pos; --it) {
      *it = (*it - 1);
    }
    *new_pos = value;
    ++size_;
    return new_pos;
  }

  void erase(iterator pos) {
    for (iterator it = pos; pos != end() - 1; ++it) {
      *it = *(it + 1);
    }
    --size_;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    auto end_ = end();
    *end_ = value;
    ++size_;
  }

  void pop_back() noexcept { --size_; }

  void resize()

  // iterators
  iterator begin() noexcept { return iterator(arr_); }
  iterator end() noexcept { return iterator(arr_ + size_); }
  const_iterator cbegin() const noexcept { return const_iterator(arr_); }
  const_iterator cend() const noexcept { return const_iterator(arr_ + size_); }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(arr_ + size_ - 1);
  }
  reverse_iterator rend() noexcept { return reverse_iterator(arr_ - 1); }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(arr_ + size_ - 1);
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(arr_ - 1);
  }

 private:
  T *arr_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
