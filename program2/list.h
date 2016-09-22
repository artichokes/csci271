/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Sept. 22
 */

#ifndef LIST_H
#define LIST_H

#include "listNode.h"
#include "iter.h"

// Class list
template<typename T>
class list {
public:
    // Creates an empty list
    list() : length(0) {
        this->headPtr = new listNode<T>(nullptr);
        this->tailPtr = new listNode<T>(nullptr, this->headPtr);
        this->headPtr->nextNodePtr = tailPtr;
    }

    // Creates a list with the same elements as the other list
    list(const list<T> &other) : list<T>() {
        (*this) = other;
    }

    // Creates a list with the specified elements
    list(std::initializer_list<T> list) : list<T>() {
        for (const auto elem : list)
            this->push_back(elem);
    }

    // Destroys the list, deleting its contents
    ~list() {
        for (iter<T> it = this->begin(); it != this->end();)
            erase(it);

        delete (this->headPtr);
        delete (this->tailPtr);
    }

    // Copies the elements of the other list
    void operator=(const list<T> &other) {
        this->clear();

        for (iter<T> it = other.begin(); it != other.end(); ++it)
            this->push_back(*it);
    }

    // Checks if the list is empty
    // @return True if the list is empty
    bool empty() const {
        return this->length == 0;
    }

    // Returns the length of the list
    // @return The number of elements in the list
    int size() const {
        return this->length;
    }

    // Returns an iterator pointing to the first element of the list.
    // If there are no elements in the array, the iterator points to the end of the list.
    // @return An iterator at the beginning of the list
    iter<T> begin() const {
        return iter<T>(this->headPtr->nextNodePtr);
    }

    // Returns an iterator pointing to the after the last element of the list.
    // @return An iterator after the end of the list
    iter<T> end() const {
        return iter<T>(this->tailPtr);
    }

    // Returns the value of the first node
    // If the list is empty, the program exhibits undefined behavior
    // @return The first element of the list
    T &front() const {
        return *this->begin();
    }

    // Returns the value of the last node
    // If the list is empty, the program exhibits undefined behavior
    // @return The last element of the list
    T &back() const {
        return *--this->end();
    }

    // Removes all elements form the list
    void clear() {
        iter<T> it = this->begin();
        while (it != this->end())
            erase(it);
    }

    // Removes the node pointed to by the iterator
    //
    // Before:
    //   1 2 3 4 5 6 7 8 9 10
    //     ^
    // After:
    //   1 3 4 5 6 7 8 9 10
    //     ^
    // @postcondition The iterator points to the next node in the list
    void erase(iter<T> &it) {
        listNode<T> *currNode = it.nodePtr;
        currNode->prevNodePtr->nextNodePtr = currNode->nextNodePtr;
        currNode->nextNodePtr->prevNodePtr = currNode->prevNodePtr;

        ++it;
        delete (currNode);
        --this->length;
    }

    // Appends an element to the list
    void push_back(T value) {
        listNode<T> *newNode = new listNode<T>(new T(value), this->tailPtr->prevNodePtr, this->tailPtr);
        this->tailPtr->prevNodePtr->nextNodePtr = newNode;
        this->tailPtr->prevNodePtr = newNode;

        ++this->length;
    }

    // Prepends an element to the list
    void push_front(T value) {
        listNode<T> *newNode = new listNode<T>(new T(value), this->headPtr, this->headPtr->nextNodePtr);
        this->headPtr->nextNodePtr->prevNodePtr = newNode;
        this->headPtr->nextNodePtr = newNode;

        ++this->length;
    }

    // Removes the first element from the list
    // If the list is empty, the program exhibits undefined behavior
    // @return The value of the first node
    T pop_front() {
        listNode<T> *front = this->headPtr->nextNodePtr;
        T value = *front->value;

        this->headPtr->nextNodePtr = front->nextNodePtr;
        this->headPtr->nextNodePtr->prevNodePtr = this->headPtr;

        delete (front);
        --this->length;

        return value;
    }

    // Removes the last element from the list
    // If the list is empty, the program exhibits undefined behavior
    // @return The value of the last node
    T pop_back() {
        listNode<T> *back = this->tailPtr->prevNodePtr;
        T value = *back->value;

        this->tailPtr->prevNodePtr = back->prevNodePtr;
        this->tailPtr->prevNodePtr->nextNodePtr = this->tailPtr;

        delete (back);
        --this->length;

        return value;
    }

private:
    listNode<T> *headPtr;
    listNode<T> *tailPtr;
    int length;
};

#endif //LIST_H
