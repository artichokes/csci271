/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Sept. 22
 */

#ifndef ITER_H
#define ITER_H

#include "listNode.h"

template<typename T>
class iter {
    friend class list<T>;

public:
    iter<T>(listNode<T> *nodePtr) : nodePtr(nodePtr) {}

    iter<T>(const iter<T> &other) : iter(other.nodePtr) {}

    iter<T> &operator++() {
        this->nodePtr = this->nodePtr->nextNodePtr;
        return *this;
    }

    iter<T> operator++(int) {
        iter<T> temp(this->nodePtr);
        ++(*this);
        return temp;
    }

    iter<T> &operator--() {
        this->nodePtr = this->nodePtr->prevNodePtr;
        return *this;
    }

    iter<T> operator--(int) {
        iter<T> temp(this->nodePtr);
        --(*this);
        return temp;
    }

    T &operator*() {
        return *this->nodePtr->value;
    }

    bool operator==(const iter<T> &other) const {
        return this->nodePtr == other.nodePtr;
    }

    bool operator!=(const iter<T> &other) const {
        return !(*this == other);
    }

private:
    listNode<T> *nodePtr;
};

#endif //ITER_H
