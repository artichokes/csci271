/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 2, Due Thursday, Sept. 22
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
    // Creates a new list node with the specified arguments
    listNode(T *value, listNode<T> *prevNodePtr = nullptr, listNode<T> *nextNodePtr = nullptr) :
            prevNodePtr(prevNodePtr), nextNodePtr(nextNodePtr), value(value) {}

    // Destroys the node, deleting the value it contains
    ~listNode() {
        delete (this->value);
    }

private:
    listNode<T> *prevNodePtr;
    listNode<T> *nextNodePtr;
    T *value;
};

#endif //LISTNODE_H
