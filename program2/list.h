/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Sept. 22
 */

#ifndef LIST_H
#define LIST_H

#include "listNode.h"
#include "iter.h"

template<typename T>
class list {
public:
    list() : length(0) {
        this->headPtr = new listNode<T>(nullptr);
        this->tailPtr = new listNode<T>(nullptr, this->headPtr);
        this->headPtr->nextNodePtr = tailPtr;
    }

    list(const list<T> &other) : list() {
        (*this) = other;
    }

    ~list() {
        for (iter<T> it = this->begin(); it != this->end();)
            erase(it);

        delete(this->headPtr);
        delete(this->tailPtr);
    }

    void operator=(const list<T> &other) {
        this->clear();

        for (iter<T> it = other.begin(); it != other.end(); ++it)
            this->push_back(*it);
    }

    bool empty() const {
        return this->length == 0;
    }

    int size() const {
        return this->length;
    }

    iter<T> begin() const {
        return iter<T>(this->headPtr->nextNodePtr);
    }

    iter<T> end() const {
        return iter<T>(this->tailPtr);
    }

    T &front() const {
        return *this->begin();
    }

    T &back() const {
        return *--this->end();
    }

    void clear() {
        iter<T> it = this->begin();
        while (it != this->end())
            erase(it);
    }

    void erase(iter<T> &it) {
        listNode<T> *currNode = it.nodePtr;
        currNode->prevNodePtr->nextNodePtr = currNode->nextNodePtr;
        currNode->nextNodePtr->prevNodePtr = currNode->prevNodePtr;

        ++it;
        delete (currNode);
        --this->length;
    }

    void push_back(T value) {
        listNode<T> *newNode = new listNode<T>(new T(value), this->tailPtr->prevNodePtr, this->tailPtr);
        this->tailPtr->prevNodePtr->nextNodePtr = newNode;
        this->tailPtr->prevNodePtr = newNode;

        ++this->length;
    }

    void push_front(T value) {
        listNode<T> *newNode = new listNode<T>(new T(value), this->headPtr, this->headPtr->nextNodePtr);
        this->headPtr->nextNodePtr->prevNodePtr = newNode;
        this->headPtr->nextNodePtr = newNode;

        ++this->length;
    }

    void pop_front() {
        listNode<T> *front = this->headPtr->nextNodePtr;
        this->headPtr->nextNodePtr = front->nextNodePtr;
        this->headPtr->nextNodePtr->prevNodePtr = this->headPtr;
        delete (front);

        --this->length;
    }

    void pop_back() {
        listNode<T> *back = this->tailPtr->prevNodePtr;
        this->tailPtr->prevNodePtr = back->prevNodePtr;
        this->tailPtr->prevNodePtr->nextNodePtr = this->tailPtr;
        delete (back);

        --this->length;
    }

private:
    listNode<T> *headPtr;
    listNode<T> *tailPtr;
    int length;
};

#endif //LIST_H
