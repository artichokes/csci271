/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Feb. 11
 */

#include <cassert>
#include <iostream>
#include "list.h"

int main() {
    list<int> mylist;
    for (int i = 0; i < 10; ++i)
        mylist.push_back(i);

    {
        iter<int> it = mylist.begin();
        int i = 0;

        while (it != mylist.end()) {
            if (i % 2 == 0)
                mylist.erase(it);
            else
                ++it;

            ++i;
        }
    }

    for (iter<int> it = mylist.begin(); it != mylist.end(); ++it)
        std::cout << *it << std::endl;

    std::cout << mylist.front() << std::endl;
    std::cout << mylist.back() << std::endl;
    std::cout << mylist.size() << std::endl;

    list<int> copylist(mylist);

//    for (iter<int> it = copylist.begin(); it != copylist.end();)
//        copylist.erase(it);

    for (iter<int> it = copylist.begin(); it != copylist.end(); ++it)
        std::cout << *it << std::endl;

    assert(false);
}
