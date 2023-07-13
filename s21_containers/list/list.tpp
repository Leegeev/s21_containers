#include "list.h"

namespace s21 {

template <typename value_type>
list<value_type>::list() {

}   


template <typename value_type>
list<value_type>::list(size_type n) {

}   


template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {

}   


template <typename value_type>
list<value_type>::list(const list &l) {

}   


template <typename value_type>
list<value_type>::list(list &&l) {

}   


template <typename value_type>
list<value_type>::~list() {

}   


template <typename value_type>
list<value_type>& list<value_type>::operator=(list &&l) {

}   


template <typename value_type>
list<value_type>& list<value_type>::operator=(const list& other) {

}


template <typename value_type>
list<value_type>::const_reference front() {

}


template <typename value_type>
list<value_type>::const_reference back() {

}


template <typename value_type>
list<value_type>::ListConstIterator cbegin() const {

}


template <typename value_type>
list<value_type>::ListConstIterator cend() const {

}


template <typename value_type>
list<value_type>::ListIterator begin() {

}


template <typename value_type>
list<value_type>::ListIterator end() {

}


template <typename value_type>
list<value_type>::bool empty() {

}


template <typename value_type>
list<value_type>::size_type size() {

}


template <typename value_type>
list<value_type>::size_type max_size() {

}


template <typename value_type>
list<value_type>::void clear() {

}


template <typename value_type>
list<value_type>::ListIterator insert(iterator pos, const_reference value) {

}


template <typename value_type>
list<value_type>::void erase(iterator pos) {

}


template <typename value_type>
list<value_type>::void push_back(const_reference value) {

}


template <typename value_type>
list<value_type>::void pop_back() {

}


template <typename value_type>
list<value_type>::void push_front(const_reference value) {

}


template <typename value_type>
list<value_type>::void pop_front() {

}


template <typename value_type>
list<value_type>::void swap(list& other) {

}


template <typename value_type>
list<value_type>::void merge(list& other) {

}


template <typename value_type>
list<value_type>::void splice(ListConstIterator pos, list& other) {

}


template <typename value_type>
list<value_type>::void reverse() {

}


template <typename value_type>
list<value_type>::void unique() {

}


template <typename value_type>
list<value_type>::void sort() {

}


}