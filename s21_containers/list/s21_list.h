#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_LIST_S21_LIST_H_

// бля короче сначала сделаю реализацию, а потом уже буду смотреть как инкапсулировать все это дело пиздец
// 

#include <initializer_list>
#include <limits>
#include <algorithm>

namespace s21 {
    template <typename T>
    class list {
        private:
        class ListNode;

        public:
        class ListIterator;
        class ListConstIterator;

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = list<value_type>::ListIterator<value_type>;
        using const_iterator = list<value_type>::ListConstIterator<value_type>;
        using size_type = std::size_t;

        list() : head_(nullptr), size_(value_type{}) {}

        explicit list(size_type n) {
            for (; n > 0; n--, push_back(value_type{}))
        }

        list(std::initializer_list<value_type> const &items); // посмотри видос про списки инициализации

        list(const list &l);

        list(list &&l);

        ~list() {
            while (head_ != nullptr) pop_front();
        }

        list& operator=(list &&l);
        list& operator=(const list& other)

        const_reference front() {
            return *begin();
        }
        const_reference back() {
            return *(end()--);
        }

        ListIterator begin() {
            return ListIterator(head_->next_);
        }
        ListIterator end() {
            return ListIterator(head_);
        }

        ListConstIterator cbegin() const {
            // return ListConstIterator(head_->next_);
        }
        ListConstIterator cend() const {
            // return ListConstIterator(head_);
        }

        bool empty() {
            return size_ == 0;
        }

        size_type size() const {
            return size_;
        }
        size_type max_size();

        void clear() { // тут нужно выбрать самый оптимальный метод удаления элемента
            while (size_) {
                pop_front();
            }
        }
        iterator insert(iterator pos, const_reference value) {
            ListNode *new_node = new ListNode(value); // конструктор узла по значению создает узел, заполняет его значением и в обе стороны указывает на нулптр
            
            pos.node_->BindBeforeCurrent(new_node);
            ++size_;

            return iterator(new_node); // можно ли вернуть текущий итератор, но +1?
        }
        void erase(iterator pos) {
            if (pos != head_) {
                pos.node_->UnBind();
                delete pos.node_;
                --size_;
            }
        }
        void push_back(const_reference value) {
            insert(this->end(), value);
        }
        void pop_back() {
            erase(--end());
        }
        void push_front(const_reference value) {
            insert(this->begin(), value);
        }
        void pop_front() {
            erase(begin());
        }

        void swap(list& other) {
            std::swap(head_, other.head_);
            std::swap(size_, other.size_);
        }
        void merge(list& other) {
            if (this != other) {
                ListIterator this_begin = begin(), this_end = end(), other_begin = other.begin(), other_end = other.end();
                while (this_begin != this_end && other_begin != other_end) {
                    if (*other_begin < *this_begin) {
                        ListNode *tmp = other_begin.node_;
                        ++other_begin;
                        tmp->UnBind();
                        this_begin.node->BindBeforeCurrent(tmp);
                        ++size_;
                    } else {
                        ++this_begin;
                    }
                }
            }
            splice(end(), other);
            other.size_ = 0;
        }
        void splice(ListConstIterator pos, list& other) {
            ListIterator pre_pos = pos - 1, olast = --other.end(), ofirst = other.begin();
            olast.node_->next = pos.node_;
            pos.node_->prev_ = olast.node_;

            pre_pos.node_->next = ofirst.node_;
            ofirst.node_->prev = pre_pos.node_;
            
            size_ += other.size_;
            other.size_ = 0;
            other.head_->next_ = other.head_;
            other.head_->prev_ = other.head_;
        }
        void reverse() {

        }
        void unique() {
            ListIterator begin_it = begin(), end_it = end(), begin_plus_it = ++begin();
            while (begin_plus_it != end_it) {
                if (*begin_it == *begin_plus_it) {
                    erase(begin_plus_it);
                    begin_plus_it = begin_it + 1;
                } else {
                    ++begin_it;
                    ++begin_plus_it;
                }
            }
        }
        void sort();
        
        class ListIterator {
            public:
            // friend class list;

            ListIterator() = delete;
            ListIterator(const List& it);

            ListIterator& operator++();
            ListIterator& operator--();
            ListIterator operator++(int);
            ListIterator operator--(int);
            bool operator==(const ListIterator &other) const;
            bool operator!=(const ListIterator &other) const;
            ListIterator operator+(size_type n) const;
            ListIterator operator-(size_type n) const;
            reference operator*() const;
            
            private:
            ListNode* node_{nullptr};
        };


        class ListConstIterator : public ListIterator {
            public:
            // friend class list;

            ListConstIterator() = delete;
            ListConstIterator(const List& it);

            ListConstIterator& operator++();
            ListConstIterator& operator--();
            ListConstIterator operator++(int);
            ListConstIterator operator--(int);
            bool operator==(const ListConstIterator &other) const;
            bool operator!=(const ListConstIterator &other) const;
            ListConstIterator operator+(size_type n) const;
            ListConstIterator operator-(size_type n) const;
            reference operator*() const;

            private:
            ListNode* node_{nullptr};
        };

        private:
        ListNode *head_;
        size_type size_;

        class ListNode { // инкапсуляция для класса, дружественный класс лист для доступа ко всем полям и методам. звучит как норм тема
            // public:
            // friend class list;
            private:
            friend class ListIterator;

            ListNode() : next_(this), prev_(this), data_(value_type{}) {}
            explicit ListNode(const_reference value) : next_(nullptr), prev_(nullptr), data_(value) {}
            explicit ListNode(ListNode) // кароч конструктор по другому узлу

            BindBeforeCurrent(ListNode* new_node) {
                new_node->next_ = this;
                new_node->prev_ = prev_;
                prev_->next_ = new_node;
                prev_ = new_node;
            }

            Unbind() {
                prev_->next_ = next_;
                next_->prev_ = prev_;
                next_ = nullptr; // u antona po drugomu, poch?
                prev_ = nullptr; // u antona po drugomu, poch?
            }

            private:
            value_type data_;
            ListNode *prev_;
            ListNode *next_;
        };


    };



}

// #include "list.tpp"
/*

следить за тем, что необязательно реализовывать все методы,
некоторые возможно будут дублироваться,
а некоторых возможно и вовсе не хватает

*/
#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_LIST_S21_LIST_H_