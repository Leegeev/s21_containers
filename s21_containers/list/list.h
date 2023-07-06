#ifndef S21_CONTAINERS_LIST_H
#define S21_CONTAINERS_LIST_H

namespace s21 {
    template <typename T>
    class list {
        public:
        class Node;
        class iterator; // название как в стандартной библиотеке
        class const_iterator;

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = list<T>::ListIterator<T>;
        using const_iterator = list<T>::ListConstIterator<T>;
        using size_type = std::size_t;

        list();                                                  //  default constructor, creates empty list 
        list(size_type n);                                       // parameterized constructor, creates the list of size n
        list(std::initializer_list<value_type> const &items);    // initializer list constructor, creates list initizialized using std::initializer_list
        list(const list &l);                                     // copy constructor
        list(list &&l);                                          // move constructor
        ~list();                                                 // destructor
        operator=(list &&l);                                     // assignment operator overload for moving object

        const_reference front();
        const_reference back();
        const_iterator cbegin() const;
        const_iterator cend() const;

        iterator begin();
        iterator end();

        bool empty();
        size_type size();
        size_type max_size();

        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(list& other);
        void merge(list& other);
        void splice(const_iterator pos, list& other);
        void reverse();
        void unique();
        void sort();
        

        private:
        Node *head{nullptr};
        Node *tail{nullptr};
    };

    template <typename T>
    class list<T>::Node {
        public:
        Node(const T& value = T{}, Node* prev = nullptr, Node* next = nullptr);
        T data;
        Node *prev;
        Node *next;
    }

    template <typename T>
    class list<T>::iterator {

    }

    template <typename T>
    class list<T>::const_iterator : iterator {

    }
}


#endif