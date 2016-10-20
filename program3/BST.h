/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 3, Due Thursday, Oct. 20
 */

#ifndef BST_H
#define BST_H

/// \class BST
/// \brief A binary sort tree
template<typename T>
class BST {
public:
    /// \brief Creates an empty binary sort tree
    BST() : rootPtr(nullptr),
            comparator(defaultCmp) {}

    /// \brief Creates an empty binary sort tree
    ///
    /// \param cmp A function that takes two arguments
    /// and returns true if the left argument is less
    /// than the right argument
    BST(bool (*cmp)(T, T)) : rootPtr(nullptr),
                             comparator(cmp) {}

    ~BST() {
        this->clear();
    }

    /// \brief Inserts a new node into the tree
    ///
    /// \param key The key of the node
    void insert(const T &key) {
        this->rootPtr = insert(this->rootPtr, key);
    }

    /// \brief Searches the tree for a node
    ///
    /// \param key The key of the node
    /// \return True, if the node exists
    bool find(const T &key) {
        return find(this->rootPtr, key) != nullptr;
    }

    /// \brief Deletes a node from the tree
    ///
    /// \param key The key of the node
    /// \return True, if the node exists
    bool remove(const T &key) {
        const T *const temp = find(this->rootPtr, key);

        if (temp != nullptr) { // If the node exists
            remove(this->rootPtr, key);
            return true;
        } else
            return false;
    }

    /// \brief Deletes all the nodes in the tree
    void clear() {
        clear(this->rootPtr);
        this->rootPtr = nullptr;
    }

    /// \brief Pre-order traversal of the tree
    ///
    /// \param func This function is called when visiting a node.
    void preorder(void (*func)(T)) {
        preorder(this->rootPtr, func);
    }

    /// \brief In-order traversal of the tree
    ///
    /// \param func This function is called when visiting a node.
    void inorder(void (*func)(T)) {
        inorder(this->rootPtr, func);
    }

    /// \brief Post-order traversal of the tree
    ///
    /// \param func This function is called when visiting a node.
    void postorder(void (*func)(T)) {
        postorder(this->rootPtr, func);
    }

private:
    /// \struct Node
    /// \brief A node in a tree
    struct Node {
        /// \brief Creates a new node with the provided key
        ///
        /// \param key The key of the node
        /// \param left A pointer to the left node
        /// \param right A pointer to the right node
        Node(T key, Node *left = nullptr, Node *right = nullptr) :
                key(key), leftPtr(left), rightPtr(right) {}

        T key;
        Node *leftPtr;
        Node *rightPtr;
    };

    /// \brief Recursive helper function to insert a key into a tree
    ///
    /// \param root The tree to insert into
    /// \param key The key to insert
    /// \return A pointer to the tree with the inserted node
    Node *insert(Node *&root, const T &key) {
        // Create a new node at the empty position
        if (root == nullptr)
            return new Node(key);

        if (comparator(key, root->key)) // key < root->key
            root->leftPtr = insert(root->leftPtr, key); // Go left
        else                            // key >= root->key
            root->rightPtr = insert(root->rightPtr, key); // Go right

        return root;
    }

    /// \brief Recursive helper function to find a node
    ///
    /// \param root The tree to search
    /// \param key The key to search for
    /// \return A pointer to the key or nullptr if not found
    const T *const find(Node *root, const T &key) const {
        // nullptr if node not found
        if (root == nullptr)
            return nullptr;

        if (comparator(key, root->key))      // key < root->key
            return find(root->leftPtr, key);
        else if (comparator(root->key, key)) // key > root->key
            return find(root->rightPtr, key);
        else                                 // key == root->key
            return &root->key; // Return a pointer to the key
    }

    /// \brief Recursive helper function to delete the minimum node in a tree
    ///
    /// \param root The tree to delete from
    /// \return A pointer to the tree with the minimum-valued node removed
    Node *deleteMin(Node *&root) {
        if (root->leftPtr == nullptr) // If leftmost node
            return root->rightPtr;
        else { // Keep traversing left
            root->leftPtr = deleteMin(root->leftPtr);
            return root;
        }
    }

    /// \brief Recursive helper function to find the minimum node in a tree
    ///
    /// \param root The tree to search
    /// \return A pointer to the minimum-valued node in the tree
    Node *getMin(Node *&root) {
        if (root->leftPtr == nullptr) // If leftmost node
            return root;
        else return getMin(root->leftPtr); // Keep traversing left
    }

    /// \brief Recursive helper function to remove a node with the specified key
    ///
    /// \param root The tree to remove from
    /// \param key The key of the node to remove
    /// \return A pointer to the tree with the node removed
    Node *remove(Node *&root, const T &key) {
        if (root == nullptr) // The node is not in the tree
            return nullptr;
        else if (comparator(key, root->key)) // key < root->key
            root->leftPtr = remove(root->leftPtr, key);
        else if (comparator(root->key, key)) // key > root->key
            root->rightPtr = remove(root->rightPtr, key);
        else {                               // key == root->key
            // Found the node to delete

            // Save the pointer to the node
            Node *temp = root;

            if (root->leftPtr == nullptr) { // If only right child exists
                root = root->rightPtr;      // point to right child
            } else if (root->rightPtr == nullptr) // If only left child exists
                root = root->leftPtr;             // point to left child
            else {
                // Get the minimum value in the right subtree
                temp = getMin(root->rightPtr);

                // Swap the values with the node to delete
                root->key = temp->key;
                root->rightPtr = deleteMin(root->rightPtr);
            }

            // Delete the necessary node
            delete temp;
        }

        return root;
    }

    /// \brief Recursive helper function to pre-order traverse the tree
    ///
    /// \param root Tree to traverse
    /// \param func Function to call when visiting node
    void preorder(Node *root, void (*func)(T)) {
        if (root == nullptr) return;
        func(root->key);
        preorder(root->leftPtr, func);
        preorder(root->rightPtr, func);
    }

    /// \brief Recursive helper function to in-order traverse the tree
    ///
    /// \param root Tree to traverse
    /// \param func Function to call when visiting node
    void inorder(Node *root, void (*func)(T)) {
        if (root == nullptr) return;
        inorder(root->leftPtr, func);
        func(root->key);
        inorder(root->rightPtr, func);
    }

    /// \brief Recursive helper function to post-order traverse the tree
    ///
    /// \param root Tree to traverse
    /// \param func Function to call when visiting node
    void postorder(Node *root, void (*func)(T)) {
        if (root == nullptr) return;
        postorder(root->leftPtr, func);
        postorder(root->rightPtr, func);
        func(root->key);
    }

    /// \brief Recursive helper function delete all nodes in a tree
    ///
    /// \param root Tree to delete
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
