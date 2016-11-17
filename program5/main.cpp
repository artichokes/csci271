/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 4, Due Tuesday, Nov. 1
 * Compile with -std=c++0x -O3
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <set>

#ifdef DEBUG
const std::string DATA_FILE = "./resources/p4load.dat";
const std::string SEARCH_FILE = "./resources/p4search.dat";
#else
const std::string DATA_FILE = "/home/win.thackerw/271/p4load.dat";
const std::string SEARCH_FILE = "/home/win.thackerw/271/p4search.dat";
#endif

/// \brief Prints the help for the program
void print_help();


/// \brief Abstract class for a hash set
class HashSet {
public:
    HashSet(int capacity) : _capacity(capacity) {}

    virtual bool insert(std::string key) = 0;

    virtual bool search(std::string key) = 0;

    int capacity() { return _capacity; };

    int size() { return _size; }

    int probes() { return _probes; };

    double avg_probes() {
        if (_unsuccessful_searches > 0 || _successful_searches > 0)
            return static_cast<double>(probes()) / (unsuccessfulSearches() + successfulSearches());
        else
            return 0;
    };

    int unsuccessfulSearches() { return _unsuccessful_searches; };

    int successfulSearches() { return _successful_searches; };

protected:
    int _size = 0;
    int _probes = 0;
    int _unsuccessful_searches = 0;
    int _successful_searches = 0;

    /// \brief Hashes a string
    /// \param key The string key to hash
    /// \return An integer within the interval [0, capacity)
    int hash(std::string key) {
        // Reads the char of the key 4 bytes at a time
        // (lkey[0] is first 4 bytes as an unsigned int)
        const unsigned *lkey = reinterpret_cast<const unsigned *>(key.data());

        // Sum 4 bytes at a time
        int intlength = key.length() / 4;
        unsigned sum = 0;
        for (int i = 0; i < intlength; ++i)
            sum += lkey[i];

        // Extra chars at end
        int extra = key.length() - intlength * 4;
        char temp[4] = {0, 0, 0, 0};
        lkey = reinterpret_cast<const unsigned *>(temp);
        for (int i = 0; i < extra; ++i)
            temp[i] = key[intlength * 4 + i];
        sum += lkey[0];

        return sum % capacity();
    }

private:
    const int _capacity;
};


/// \brief A hash set using closed hashing (with linear probing)
class ClosedHashSet : public HashSet {
public:
    ClosedHashSet(int capacity) : HashSet(capacity) {
        this->_hash_table = new std::string[capacity];
    };

    ~ClosedHashSet() {
        delete[](this->_hash_table);
    }

    bool insert(std::string key) {
        if (size() == capacity())
            return false; // Table full

        int home, pos;
        home = pos = this->hash(key);

        // If position is already taken
        for (int i = 1; _hash_table[pos] != ""; ++i) {
            pos = (home + i) % capacity(); // Linear probe

            if (key == _hash_table[pos]) // If duplicate
                return false;
        }

        _hash_table[pos] = std::string(key);

        ++this->_size;
        return true;
    };

    bool search(std::string key) {
        int home, pos;
        home = pos = this->hash(key);

        // If position is taken and the key does not match
        for (int i = 1;
             ++this->_probes // Increment probes
             && (_hash_table[pos] != "") // Position taken
             && (key != _hash_table[pos]) // Key does not match
             && (i < capacity()); // Have not checked all possible slots
             ++i)
            pos = (home + i) % capacity(); // Linear probe

        if (key == _hash_table[pos]) {
            ++this->_successful_searches;
            return true;
        } else {
            ++this->_unsuccessful_searches;
            return false;
        }
    };

private:
    std::string *_hash_table;
};


/// \brief A hash set using open hashing
class OpenHashSet : public HashSet {
public:
    OpenHashSet(int capacity) : HashSet(capacity) {
        this->_hash_table = new std::set<std::string>[capacity];
    };

    ~OpenHashSet() {
        delete[](this->_hash_table);
    }

    bool insert(std::string key) {
        int pos = this->hash(key);

        if (_hash_table[pos].insert(key).second) {
            // Not duplicate
            ++this->_size;
            return true;
        } else {
            return false;
        }
    };

    bool search(std::string key) {
        int pos = this->hash(key);

        auto it = _hash_table[pos].begin();

        while (++this->_probes // Increment probes
               && (it != _hash_table[pos].end()) // Have not checked all values
               && (*it < key)) // The value is less than the key
            ++it;

        if (it != _hash_table[pos].end() && *it == key) {
            ++this->_successful_searches;
            return true;
        } else {
            ++this->_unsuccessful_searches;
            return false;
        }
    };

private:
    std::set<std::string> *_hash_table;
};


int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    // Ensure sort algorithm and line count arguments
    if (args.size() < 3) {
        print_help();
        return 1;
    }

    // Make sure algorithm is implemented
    std::transform(args[1].begin(), args[1].end(), args[1].begin(), ::tolower);
    if (args[1] != "closed" && args[1] != "open") {
        print_help();
        return 1;
    }

    // Make sure table size is a number and is >= 100000
    int table_size = 0;
    try {
        table_size = std::stoi(args[2]);
        if (table_size < 100000) throw std::exception();
    } catch (...) {
        print_help();
        return 1;
    }

    HashSet *hashSet;
    if (args[1] == "closed")
        // Use closed hashing (open addressing)
        hashSet = new ClosedHashSet(table_size);
    else
        // Use open hashing (separate chaining)
        hashSet = new OpenHashSet(table_size);


    // Open data file
    std::ifstream dataFile;
    dataFile.open(DATA_FILE);
    if (dataFile.fail()) {
        std::cout << "Failed to read file '" << DATA_FILE << "'!" << std::endl;
        return 1;
    }

    // Read from data file
    for (std::string line; dataFile >> line;)
        hashSet->insert(line);

    // Close data file
    dataFile.close();


    // Open search file
    std::ifstream searchFile;
    searchFile.open(SEARCH_FILE);
    if (searchFile.fail()) {
        std::cout << "Failed to open file '" << SEARCH_FILE << "'!" << std::endl;
        return 1;
    }

    // Search for lines from search file
    for (std::string line; searchFile >> line;)
        hashSet->search(line);

    // Close search file
    searchFile.close();

    std::cout << std::left << "| " << "------------"
              << " | " << std::setw(12) << "------------"
              << " | " << std::setw(22) << "----------------------"
              << " | " << std::setw(22) << "----------------------"
              << " |" << std::endl;

    std::cout << std::left << "| " << std::setw(12) << "Probes"
              << " | " << std::setw(12) << "Avg. Probes"
              << " | " << std::setw(22) << "Unsuccessful Searches"
              << " | " << std::setw(22) << "Successful Searches"
              << " |" << std::endl;

    std::cout << std::left << "| " << "------------"
              << " | " << std::setw(12) << "------------"
              << " | " << std::setw(22) << "----------------------"
              << " | " << std::setw(22) << "----------------------"
              << " |" << std::endl;

    std::cout << std::left << "| " << std::setw(12) << hashSet->probes()
              << " | " << std::setw(12) << hashSet->avg_probes()
              << " | " << std::setw(22) << hashSet->unsuccessfulSearches()
              << " | " << std::setw(22) << hashSet->successfulSearches()
              << " |" << std::endl;

    std::cout << std::left << "| " << "------------"
              << " | " << std::setw(12) << "------------"
              << " | " << std::setw(22) << "----------------------"
              << " | " << std::setw(22) << "----------------------"
              << " |" << std::endl;

    return 0;
}

void print_help() {
    std::cout << "Usage: p5 [open|closed] [TABLE_SIZE]" << std::endl;
    std::cout << "TABLE_SIZE must be greater than or equal to 100,000." << std::endl;
}
