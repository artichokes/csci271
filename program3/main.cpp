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

void printValue(const char *value) {
    cout << value << endl;
}

bool cstrcmp(const char *left, const char *right) {
    return strcmp(left, right) < 0;
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

int main() {
    BST<const char *> tree(&cstrcmp);
    while (handleInput(tree, promptMenu()));
}
