#include "list.h"

namespace s21 {

template <typename value_type>
list<value_type>::ListNode::ListNode(const value_type& val, ListNode* p, ListNode* n) : data(val), prev(p), next(n) {}

template <typename value_type>
list<value_type>::list() : head(nullptr), tail(nullptr) {}


template <typename value_type>
list<value_type>::list(size_type n) {
    for (; n > 0; n--, push_back(value_type{}))
}


template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {

}   


template <typename value_type>
list<value_type>::list(const list &l) {
    for (const_iterator it = l.cbegin(); it != l.cend(); ++it) {
        push_back(*it);
    }
}


template <typename value_type>
list<value_type>::list(list &&l) {
    swap(l);
}


template <typename value_type>
list<value_type>::~list() {
    while (head != nullptr) pop_front();
}   


template <typename value_type>
list<value_type>& list<value_type>::operator=(list &&l) {

}   


template <typename value_type>
list<value_type>& list<value_type>::operator=(const list& other) {

}


template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
    if (empty()) {
        static const_reference val{};
        return val;
    } else {
        return *begin;
    }
}


template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
    if (empty()) {
        static const_reference val{};
        return val;
    } else {
        return *(--end());
    }
}

template <typename value_type>
typename list<value_type>::ListIterator list<value_type>::begin() {
    // у дани по другому, у него в классе итератора он хранит текущую позицию, голову и хвост
    // мне в итераторе придется обрабатывать возможность перемещения при вызове 
    if (head_) {
        return iterator(head_);
    } else {
        return ListIterator(end_);
    }
}

template <typename value_type>
typename list<value_type>::ListIterator list<value_type>::end() {
    return ListIterator(tail_);
}

template <typename value_type>
typename list<value_type>::ListConstIterator list<value_type>::cbegin() const {
    return ListConstIterator(head_);
}


template <typename value_type>
typename list<value_type>::ListConstIterator list<value_type>::cend() const {
    return ListConstIterator(tail_);
}


template <typename value_type>
bool list<value_type>::empty() {
    return head == nullptr;
}


template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() const { // const ot menya
    size_type i = 0;
    for (ListConstIterator it = cbegin(); it != cend(); it++, i++);
    return i;
}


template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {

}


template <typename value_type>
void list<value_type>::clear() {
    this->~list(); // вот так вот вручную можно вызвать деструктор?
}


template <typename value_type>
typename list<value_type>::ListIterator list<value_type>::insert(ListIterator pos, const_reference value) {
    // че он возвращает?
    // вставляет на текущую позицию, возвращает итератор на новый элемент?
    
}


template <typename value_type>
void list<value_type>::erase(iterator pos) {
    
}


template <typename value_type>
list<value_type>::void push_back(const_reference value) {
    // вставляет в конец
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