/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 3, Due Thursday, Oct. 20
 */

#include <iostream>
#include <fstream>
#include <cstring>

#include "BST.h"

using namespace std;

const int LINE_LENGTH = 20;

/// \brief Compares two cstrings
///
/// \param left Left cstring
/// \param right Right cstring
/// \return True, if left occurs before right in lexicographic ordering
bool cstrcmp(const char *left, const char *right);

/// \brief Prints a menu and prompts user for selection
///
/// \return The selection or -1 if an invalid selection
int promptMenu();

/// \brief Provides respective action based on input
///
/// \param tree The tree to mutate
/// \param input The user selection
/// \return True, to reprompt the menu
bool handleInput(BST<const char *> &tree, int input);

/// \brief Prompts the user for a file
///
/// \param tree The tree to add keys to
void insertFromFile(BST<const char *> &tree);

/// \brief Opens the file adds the keys to the tree
///
/// \param tree The tree to add keys to
/// \param filename The file to read
/// \return -1 if invalid file, else the number of keys added
int readFile(BST<const char *> &tree, string filename);

/// \brief Prompts the user for a key to add to the tree
///
/// \param tree The tree to add the key to
void insertFromKeyboard(BST<const char *> &tree);

/// \brief Prompts the user for a key
/// and searches the tree for the key
///
/// \param tree The tree to search
void findKey(BST<const char *> &tree);

/// \brief Prompts the user for a key
/// and attempts to delete the key
///
/// \param tree The tree to remove the key from
void deleteKey(BST<const char *> &tree);

/// \brief Prints the cstring
///
/// \param value The cstring to print
void printValue(const char *value);

int main() {
    BST<const char *> tree(&cstrcmp);
    while (handleInput(tree, promptMenu()));
}

bool cstrcmp(const char *left, const char *right) {
    return strcmp(left, right) < 0;
}

int promptMenu() {
    cout << endl;
    cout << "1 - Insert from a File\n";
    cout << "2 - Insert from the Keyboard\n";
    cout << "3 - Find\n";
    cout << "4 - Delete\n";
    cout << "5 - Print In-order\n";
    cout << "6 - Print Pre-order\n";
    cout << "7 - Print Post-order\n";
    cout << "8 - Exit\n";
    cout << endl;
    cout << "Choose an option (1-8): ";

    int input;
    cin >> input;

    if (cin.fail() || input < 1 || input > 8) return -1;
    else return input;
}

bool handleInput(BST<const char *> &tree, int input) {
    switch (input) {
        case 1:
            cout << endl;
            insertFromFile(tree);
            break;
        case 2:
            cout << endl;
            insertFromKeyboard(tree);
            break;
        case 3:
            cout << endl;
            findKey(tree);
            break;
        case 4:
            cout << endl;
            deleteKey(tree);
            break;
        case 5:
            cout << "\033[1;33m";
            cout << "\n------------------------------\n\n";
            tree.inorder(printValue);
            cout << "\n------------------------------\n";
            cout << "\033[0m";
            break;
        case 6:
            cout << "\033[1;33m";
            cout << "\n------------------------------\n\n";
            tree.preorder(printValue);
            cout << "\n------------------------------\n";
            cout << "\033[0m";
            break;
        case 7:
            cout << "\033[1;33m";
            cout << "\n------------------------------\n\n";
            tree.postorder(printValue);
            cout << "\n------------------------------\n";
            cout << "\033[0m";
            break;
        case 8:
            return false;
        default:
            cin.clear();
            cin.ignore();
            cout << "\n\033[1;31m" <<
                 "Invalid input!\n" <<
                 "Please enter a number between 1 and 8." <<
                 "\033[0m\n";
            break;
    }

    return true;
}

void insertFromFile(BST<const char *> &tree) {
    string filepath;
    cout << "Enter the file path: ";
    cin >> filepath;

    int result = readFile(tree, filepath);

    if (result < 0)
        cout << "\n\033[1;31m"
             << "Could not read file: " << filepath
             << "\033[0m\n";
    else
        cout << "\n\033[1;32m"
             << "Read " << result << " lines from file: " << filepath
             << "\033[0m\n";
}

int readFile(BST<const char *> &tree, string filename) {
    ifstream infile;
    infile.open(filename);
    if (infile.fail()) return -1;

    unsigned lines = 0;

    for (char line[LINE_LENGTH + 1];
         !infile.getline(line, LINE_LENGTH + 1).eof();) {
        tree.insert(strdup(line));
        ++lines;
    }

    infile.close();

    return lines;
}

void insertFromKeyboard(BST<const char *> &tree) {
    string input;

    cout << "Enter a key (20 char. max): ";
    cin >> input;

    if (input.length() < 1 || input.length() > 20)
        cout << "\n\033[1;31m"
             << "Invalid input!"
             << "\033[0m\n";
    else {
        tree.insert(strdup(input.c_str()));
        cout << "\n\033[1;32m"
             << "Inserted key: " << input.c_str()
             << "\033[0m\n";
    }
};

void findKey(BST<const char *> &tree) {
    string input;

    cout << "Enter a key (20 char. max): ";
    cin >> input;

    if (input.length() < 1 || input.length() > 20)
        cout << "\n\033[1;31m"
             << "Invalid input!"
             << "\033[0m\n";
    else {
        bool found = tree.find(strdup(input.c_str()));
        if (found)
            cout << "\n\033[1;32m"
                 << "Found key: " << input.c_str() << " !"
                 << "\033[0m\n";
        else
            cout << "\n\033[1;31m"
                 << "Key not found: " << input.c_str() << " !"
                 << "\033[0m\n";
    }
}

void deleteKey(BST<const char *> &tree) {
    string input;

    cout << "Enter a key (20 char. max): ";
    cin >> input;

    if (input.length() < 1 || input.length() > 20)
        cout << "\n\033[1;31m"
             << "Invalid input!"
             << "\033[0m\n";
    else {
        bool removed = tree.remove(strdup(input.c_str()));
        if (removed)
            cout << "\n\033[1;32m"
                 << "Deleted key: " << input.c_str() << " !"
                 << "\033[0m\n";
        else
            cout << "\n\033[1;31m"
                 << "Key not found: " << input.c_str() << " !"
                 << "\033[0m\n";
    }
}

void printValue(const char *value) {
    cout << value << endl;
}
