#ifndef S21_CONTAINERS_LIST_H
#define S21_CONTAINERS_LIST_H

namespace s21 {
    template <typename T>
    class list {
        public:
        class ListNode;
        class ListIterator; // название как в стандартной библиотеке
        class ListConstIterator;

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using ListIterator = list<value_type>::ListIterator<value_type>;
        using ListConstIterator = list<value_type>::ListConstIterator<value_type>;
        using size_type = std::size_t;

        list();                                                  //  default constructor, creates empty list 
        list(size_type n);                                       // parameterized constructor, creates the list of size n
        list(std::initializer_list<value_type> const &items);    // initializer list constructor, creates list initizialized using std::initializer_list
        list(const list &l);                                     // copy constructor
        list(list &&l);                                          // move constructor
        ~list();                                                 // destructor
        list& operator=(list &&l);                               // assignment operator overload for moving object
        list& operator=(const list& other);

        const_reference front();
        const_reference back();
        ListConstIterator cbegin() const;
        ListConstIterator cend() const;

        ListIterator begin();
        ListIterator end();

        bool empty();
        size_type size();
        size_type max_size();

        void clear();
        ListIterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(list& other);
        void merge(list& other);
        void splice(ListConstIterator pos, list& other);
        void reverse();
        void unique();
        void sort();
        

        private:
        ListNode *head{nullptr};
        ListNode *tail{nullptr};
    };

    template <typename value_type>
    class list<value_type>::ListNode {
        public:
        ListNode(const value_type& value = value_type{}, ListNode* prev = nullptr, ListNode* next = nullptr);
        value_type data;
        ListNode *prev;
        ListNode *next;
    };

    template <typename value_type>
    class list<value_type>::ListIterator {
        public:
        friend class list;
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

    template <typename value_type>
    class list<value_type>::ListConstIterator : public ListIterator {
        public:
        friend class list;
    };
}


#endif