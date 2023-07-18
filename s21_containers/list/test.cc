#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main () {
    list<int> og = {1,2,3,4,5};
    auto endit = og.end();
    for (int i = 0;endit != og.begin(); endit--, i++) {
        cout << i << ": " << *endit << endl;
    }
}