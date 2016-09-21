/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Feb. 11
 */

#ifndef LISTNODE_H
#define LISTNODE_H

template<typename T>
class list;

template<typename T>
class iter;

template<typename T>
class listNode {
    friend class list<T>;

    friend class iter<T>;

public:
    listNode(T *value, listNode<T> *prevNodePtr = nullptr, listNode<T> *nextNodePtr = nullptr) :
            prevNodePtr(prevNodePtr), nextNodePtr(nextNodePtr), value(value) {}

    ~listNode() {
        delete (this->value);
    }

private:
    listNode<T> *prevNodePtr;
    listNode<T> *nextNodePtr;
    T *value;
};

#endif //LISTNODE_H
