/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Sept. 22
 */

#ifndef ITER_H
#define ITER_H

#include "listNode.h"

using namespace std;

// Class iter
template<typename T>
class iter {
    friend class list<T>;

public:
    // Creates an iterator pointing to null
    iter<T>() : nodePtr(nullptr) {}

    // Creates an iterator that points to the specified node
    iter<T>(listNode<T> *nodePtr) : nodePtr(nodePtr) {}

    // Creates an iterator that points to the same node as the other iterator
    iter<T>(const iter<T> &other) : iter(other.nodePtr) {}

    // Increments the iterator (prefix)
    // If the next node does not exist, the program exhibits undefined behavior
    // @return The iterator pointing to the next node
    iter<T> &operator++() {
        this->nodePtr = this->nodePtr->nextNodePtr;
        return *this;
    }

    // Increments the iterator (postfix)
    // If the next node does not exist, the program exhibits undefined behavior
    // @postcondition The iterator points to the next node
    // @return An iterator pointing to the same node before incrementing
    iter<T> operator++(int) {
        iter<T> temp(this->nodePtr);
        ++(*this);
        return temp;
    }

    // Decrements the iterator (prefix)
    // If the previous node does not exist, the program exhibits undefined behavior
    // @return The iterator pointing to the previous node
    iter<T> &operator--() {
        this->nodePtr = this->nodePtr->prevNodePtr;
        return *this;
    }

    // Decrements the iterator (postfix)
    // If the previous node does not exist, the program exhibits undefined behavior
    // @postcondition The iterator points to the previous node
    // @return An iterator pointing to the same node before decrementing
    iter<T> operator--(int) {
        iter<T> temp(this->nodePtr);
        --(*this);
        return temp;
    }

    // Derefrences the iterator returning the value of the node
    // @return The value of the iterator's node
    T &operator*() {
        return *this->nodePtr->value;
    }

    // Checks if the iterators point to the same node
    // @return True if the nodes are the same
    bool operator==(const iter<T> &other) const {
        return this->nodePtr == other.nodePtr;
    }

    // Checks if the iterators point to different nodes
    // @return True if the nodes are the different
    bool operator!=(const iter<T> &other) const {
        return !(*this == other);
    }

private:
    listNode<T> *nodePtr;
};

#endif //ITER_H
