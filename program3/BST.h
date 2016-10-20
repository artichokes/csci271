/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 3, Due Thursday, Oct. 20
 */

#ifndef BST_H
#define BST_H

template<typename T>
class BST {
public:
    BST() : rootPtr(nullptr),
            comparator(defaultCmp) {}

    BST(bool (*cmp)(T, T)) : rootPtr(nullptr),
                             comparator(cmp) {}

    ~BST() {
        this->clear();
    }

    void insert(const T &key) {
        this->rootPtr = insert(this->rootPtr, key);
    }

    bool find(const T &key) {
        return find(this->rootPtr, key) != nullptr;
    }

    bool remove(const T &key) {
        const T *const temp = find(this->rootPtr, key);
        if (temp != nullptr) {
            remove(this->rootPtr, key);
            return true;
        } else
            return false;
    }

    void clear() {
        clear(this->rootPtr);
        this->rootPtr = nullptr;
    }

    void preorder(void (*func)(T)) {
        preorder(this->rootPtr, func);
    }

    void inorder(void (*func)(T)) {
        inorder(this->rootPtr, func);
    }

    void postorder(void (*func)(T)) {
        postorder(this->rootPtr, func);
    }

private:
    struct Node {
        Node(T key, Node *left = nullptr, Node *right = nullptr) :
                key(key), leftPtr(left), rightPtr(right) {}

        T key;
        Node *leftPtr;
        Node *rightPtr;
    };

    Node *insert(Node *&root, const T &key) {
        if (root == nullptr)
            return new Node(key);

        if (comparator(key, root->key)) // key < root->key
            root->leftPtr = insert(root->leftPtr, key);
        else                            // key >= root->key
            root->rightPtr = insert(root->rightPtr, key);

        return root;
    }

    const T *const find(Node *root, const T &key) const {
        if (root == nullptr)
            return nullptr;

        if (comparator(key, root->key))      // key < root->key
            return find(root->leftPtr, key);
        else if (comparator(root->key, key)) // key > root->key
            return find(root->rightPtr, key);
        else                                 // key == root->key
            return &root->key;
    }

    Node *deleteMin(Node *&root) {
        if (root->leftPtr == nullptr)
            return root->rightPtr;
        else {
            root->leftPtr = deleteMin(root->leftPtr);
            return root;
        }
    }

    Node *getMin(Node *&root) {
        if (root->leftPtr == nullptr)
            return root;
        else return getMin(root->leftPtr);
    }

    Node *remove(Node *&root, const T &key) {
        if (root == nullptr)
            return nullptr;
        else if (comparator(key, root->key)) // key < root->key
            root->leftPtr = remove(root->leftPtr, key);
        else if (comparator(root->key, key)) // key > root->key
            root->rightPtr = remove(root->rightPtr, key);
        else {                               // key == root->key
            Node *temp = root;

            if (root->leftPtr == nullptr) {
                root = root->rightPtr;
            } else if (root->rightPtr == nullptr)
                root = root->leftPtr;
            else {
                temp = getMin(root->rightPtr);
                root->key = temp->key;
                root->rightPtr = deleteMin(root->rightPtr);
            }

            delete temp;
        }

        return root;
    }

    void preorder(Node *root, void (*func)(T)) {
        if (root == nullptr) return;
        func(root->key);
        preorder(root->leftPtr, func);
        preorder(root->rightPtr, func);
    }

    void inorder(Node *root, void (*func)(T)) {
        if (root == nullptr) return;
        inorder(root->leftPtr, func);
        func(root->key);
        inorder(root->rightPtr, func);
    }

    void postorder(Node *root, void (*func)(T)) {
        if (root == nullptr) return;
        postorder(root->leftPtr, func);
        postorder(root->rightPtr, func);
        func(root->key);
    }

    void clear(Node *root) {
        if (root == nullptr) return;
        clear(root->leftPtr);
        clear(root->rightPtr);
        delete root;
    }

    static bool defaultCmp(T left, T right) {
        return left < right;
    }

    Node *rootPtr;

    bool (*comparator)(T, T);
};

#endif //BST_H
