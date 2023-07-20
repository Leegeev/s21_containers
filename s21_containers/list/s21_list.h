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
        class ListNode; // добавил френд, потому что поле даты в узле не видело свой тип
        friend class ListNode;

        public:
        class ListIterator;
        class ListConstIterator;

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = list<value_type>::ListIterator;
        using const_iterator = list<value_type>::ListConstIterator;
        using size_type = std::size_t;

        list() : head_(new ListNode{}), size_(value_type{}) {}

        explicit list(size_type n) : list() {
            for (; n > 0; n--, push_back(value_type{}));
        }

        list(std::initializer_list<value_type> const &items) : list() {
            for (auto item : items) {
                push_back(item);
            }
        } // посмотри видос про списки инициализации

        list(const list &l) : list() {
            for (auto item : l) {
                push_back(item);
            }
        }

        list(list &&l) : list() {
            splice(begin(), l);
        }

        ~list() {
            clear();
            delete head_;
            head_ = nullptr;
        }

        list& operator=(list &&l) {
            if (this != l) {
                clear();
                splice(begin(), l);
            }
            return *this;
        }
        
        list& operator=(const list& other) {
            if (this != other) {
                iterator tbegin = begin(), tend = end();
                const_iterator obegin = other.begin(), oend = other.end();

                while (tbegin != tend && obegin != oend) {
                    *tbegin = *obegin;
                    ++tbegin;
                    ++obegin;
                }

                iterator tmp = tbegin;
                while (tbegin != tend) {
                    ++tbegin;
                    erase(tmp);
                    tmp = tbegin;
                }

                while (obegin != oend) {
                    push_back(*obegin);
                    ++obegin;
                }
            }
        }

        /*
        reference front() {
            return *begin();
        }
        reference back() {
            return *(end()--);
        }
        */
        const_reference front() {
            return *begin();
        }
        const_reference back() {
            return *(end()--);
        }

        iterator begin() {
            return iterator(head_->next_);
        }
        iterator end() {
            return iterator(head_);
        }

        const_iterator cbegin() const {
            return const_iterator(head_->next_);
        }
        const_iterator cend() const {
            return const_iterator(head_);
        }

        bool empty() {
            return size_ == 0;
        }

        size_type size() const {
            return size_;
        }
        size_type max_size() {
            return std::numeric_limits<size_type>::max() / sizeof(ListNode) / 2 - 1;
        }

        void clear() { // тут нужно выбрать самый оптимальный метод удаления элемента
            while (size_) {
                erase(begin());
            }
        }
        iterator insert(iterator pos, const_reference value) {
            ListNode *new_node = new ListNode(value); // конструктор узла по значению создает узел, заполняет его значением и в обе стороны указывает на нулптр
            
            pos.node_->BindBeforeCurrent(new_node);
            ++size_;

            return iterator(new_node); // можно ли вернуть текущий итератор, но +1?
        }
        void erase(iterator pos) {
            if (pos.node_ != head_) {
                pos.node_->Unbind();
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
        void splice(const_iterator pos, list& other) {
            iterator pre_pos = pos - 1, olast = --other.end(), ofirst = other.begin();
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
            iterator begin_it = begin(), end_it = end();
            while (begin_it != end_it) {
                std::swap(begin_it.node->prev_, begin_it.node->next);
                --begin_it;
            }
            std::swap(head_->prev_, head_->next);
        }
        void unique() { // проверить на практике
            iterator begin_it = begin(), end_it = end(), begin_plus_it = ++begin();
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
        void sort() {
            
        }
        
        class ListIterator {
            public:
            // friend class list;
            friend list::iterator list::insert(iterator pos, const_reference value);
            friend void list::erase(iterator pos);
            friend void list::clear();
            friend void list::splice(const_iterator pos, list& other);
            friend void list::reverse();

            ListIterator() = delete;
            // ListIterator(const List& it) {}
            explicit ListIterator(ListNode *node) : node_(node) {}
            // explicit ListIterator(ListIterator it) {} // как будто конструктор по умолчанию должен эту тему сделать сам

            ListIterator& operator++() {
                node_ = node_->next_;
                return *this;
            }
            ListIterator& operator--() {
                node_ = node_->prev_;
                return *this;
            }
            ListIterator operator++(int) {
                ListIterator tmp{node_};
                node_ = node_->next_;
                return tmp;
            }
            ListIterator operator--(int) { 
                ListIterator tmp{node_};
                node_ = node_->prev_;
                return tmp;
            }
            bool operator==(const ListIterator &other) const {
                return node_ == other.node_;
            }
            bool operator!=(const ListIterator &other) const {
                return node_ != other.node_;
            }
            ListIterator operator+(size_type n) const {
                ListIterator tmp{node_};
                for (;n > 0; n--) {
                    ++tmp;
                }
                return tmp;
            }
            ListIterator operator-(size_type n) const {
                ListIterator tmp{node_};
                for (;n > 0; n--) {
                    --tmp;
                }
                return tmp;
            }
            reference operator*() const {
                return node_->data_;
            }
            
            private:
            ListNode* node_{nullptr};
        };


        class ListConstIterator : public ListIterator {
            public:
            // friend class list;

            ListConstIterator() = delete;
            ListConstIterator(const ListNode *node) : node_(node) {}

            ListConstIterator& operator++() {
                node_ = node_->next_;
                return *this;
            }
            ListConstIterator& operator--() {
                node_ = node_->prev_;
                return *this;
            }
            ListConstIterator operator++(int) {
                ListConstIterator tmp{node_};
                node_ = node_->next_;
                return tmp;
            }
            ListConstIterator operator--(int) {
                ListConstIterator tmp{node_};
                node_ = node_->prev_;
                return tmp;
            }
            bool operator==(const ListConstIterator &other) const {
                return node_ == other.node_;
            }
            bool operator!=(const ListConstIterator &other) const {
                return node_ != other.node_;
            }
            ListConstIterator operator+(size_type n) const {
                ListConstIterator tmp{node_};
                for (;n > 0; n--) {
                    ++tmp;
                }
                return tmp;
            }
            ListConstIterator operator-(size_type n) const {
                ListConstIterator tmp{node_};
                for (;n > 0; n--) {
                    --tmp;
                }
                return tmp;
            }
            const_reference operator*() const {
                return node_->data_;
            }

            private:
            ListNode* node_{nullptr};
        };

        private:

        class ListNode { // инкапсуляция для класса, дружественный класс лист для доступа ко всем полям и методам. звучит как норм тема
            // public:
            // friend class list;
            // private: // мне казалось, что если в приватном поле объявить дружественность к листу, то весь класс будет у листа в приватном поле, но это так не работает
            // задумался о варианте с наследованием, если итераторы наследовать от нода, чтобы дополнять его функционал и сохранять инкапсуляцию
            // friend class ListIterator;
            public:

            // friend void list::erase(iterator pos);
            // friend void list::clear();
            ListNode() : next_(this), prev_(this), data_(value_type{}) {}
            explicit ListNode(const_reference value) : next_(nullptr), prev_(nullptr), data_(value) {}
            // explicit ListNode(ListNode); // кароч конструктор по другому узлу. он мне нужен?? 

            void BindBeforeCurrent(ListNode* new_node) {
                new_node->next_ = this;
                new_node->prev_ = prev_;
                prev_->next_ = new_node;
                prev_ = new_node;
            }

            void Unbind() {
                prev_->next_ = next_;
                next_->prev_ = prev_;
                next_ = nullptr; // u antona po drugomu, poch?
                prev_ = nullptr; // u antona po drugomu, poch?
            }

            // private:
            value_type data_;
            ListNode *prev_;
            ListNode *next_;
        };

        ListNode *head_;
        size_type size_;



    };



}  // namespace s21

// #include "list.tpp"
/*

следить за тем, что необязательно реализовывать все методы,
некоторые возможно будут дублироваться,
а некоторых возможно и вовсе не хватает

*/
#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_LIST_S21_LIST_H_