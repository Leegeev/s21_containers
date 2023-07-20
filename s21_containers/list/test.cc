#include <iostream>
#include <list>
#include "s21_list.h"
#include <algorithm>

using namespace std;

int main () {
    s21::list<int> test {1,2,3,4,5};
    for (s21::list<int>::ListIterator it = test.begin(); it != test.end(); ++it) {
        cout << *it << endl;
    }

    /*
    splice
    reverse
    */
}