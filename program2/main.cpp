/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Sept. 22
 */

#include <cassert>
#include <iostream>
#include "list.h"

int main() {
    // Test default constructor
    list<int> testlist;
    assert(testlist.empty());
    assert(testlist.size() == 0);

    // Test push_front
    testlist.push_front(0);
    assert(!testlist.empty());
    assert(testlist.size() == 1);
    assert(testlist.front() == 0);
    assert(testlist.back() == 0);

    // Test push_back
    testlist.push_back(1);
    assert(!testlist.empty());
    assert(testlist.size() == 2);
    assert(testlist.front() == 0);
    assert(testlist.back() == 1);

    // Test pop_front
    assert(testlist.pop_front() == 0);
    assert(!testlist.empty());
    assert(testlist.size() == 1);
    assert(testlist.front() == 1);
    assert(testlist.back() == 1);

    // Test pop_back
    testlist.push_front(0);
    assert(testlist.pop_back() == 1);
    assert(!testlist.empty());
    assert(testlist.size() == 1);
    assert(testlist.front() == 0);
    assert(testlist.back() == 0);

    // Test clear
    testlist.clear();
    assert(testlist.empty());
    assert(testlist.size() == 0);

    // Test initialization list constructor
    list<int> secondlist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int correct_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(!secondlist.empty());
    assert(secondlist.size() == 10);
    assert(secondlist.front() = 1);
    assert(secondlist.back() = 10);

    // Test iterator
    iter<int> secondlist_iter = secondlist.begin();
    for (int i = 0; secondlist_iter != secondlist.end(); ++i) {
        assert(*secondlist_iter == correct_array[i]);
        ++secondlist_iter;
    }

    secondlist_iter = secondlist.begin();
    for (int i = 0; secondlist_iter != secondlist.end(); ++i) {
        assert(*secondlist_iter++ == correct_array[i]);
    }

    secondlist_iter = --secondlist.end();
    for (int i = 9; secondlist_iter != secondlist.begin(); --i) {
        assert(*secondlist_iter == correct_array[i]);
        --secondlist_iter;
    }

    secondlist_iter = --secondlist.end();
    for (int i = 9; secondlist_iter != secondlist.begin(); --i) {
        assert(*secondlist_iter-- == correct_array[i]);
    }

    // Test copy constructor
    list<int> thirdlist(secondlist);
    iter<int> thirdlist_iter = thirdlist.begin();

    assert(!thirdlist.empty());
    assert(thirdlist.size() == 10);
    assert(thirdlist.front() = 1);
    assert(thirdlist.back() = 10);
    for (int i = 0; thirdlist_iter != thirdlist.end(); ++i) {
        assert(*thirdlist_iter == correct_array[i]);
        ++thirdlist_iter;
    }

    // Test assignment operator
    testlist = thirdlist;
    iter<int> testlist_iter = testlist.begin();

    assert(!testlist.empty());
    assert(testlist.size() == 10);
    assert(testlist.front() = 1);
    assert(testlist.back() = 10);
    for (int i = 0; testlist_iter != testlist.end(); ++i) {
        assert(*testlist_iter == correct_array[i]);
        ++testlist_iter;
    }

    // Test erase operator
    testlist_iter = testlist.begin();
    for (int i = 0; testlist_iter != testlist.end(); ++i) {
        assert(*testlist_iter == correct_array[i]);
        testlist.erase(testlist_iter);
    }

    std::cout << "All tests passed!" << std::endl;
}
