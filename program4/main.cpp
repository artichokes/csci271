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
#include <iterator>
#include <algorithm>

#ifdef DEBUG
const std::string SORT_FILE = "./resources/sort.dat";
#else
const std::string SORT_FILE = "/home/win.thackerw/271/sort.dat";
#endif

const std::string OUT_FILE = "./sorted.dat";

/// \brief Prints the help for the program
void print_help();

/// \brief Bubble sorts a vector of elements
///
/// \param vec The vector of elements
template<typename T>
void bubble_sort(std::vector<T> &vec);

/// \brief Heap sorts a vector of elements
///
/// \param vec The vector of elements
template<typename T>
void heap_sort(std::vector<T> &vec);

namespace insertion_sort {
    /// \brief Insertion sorts a vector of elements
    ///
    /// \param vec The vector of elements
    template<typename T>
    void sort(std::vector<T> &vec);

    namespace details {
        /// \brief Insertion sorts the elements [begin, end)
        ///
        /// \param begin The beginning of the container
        /// \param end One past the end of the container
        template<typename It>
        void sort(It begin, It end);
    }
}

namespace quick_sort {
    /// \brief Quicksorts a vector of elements
    ///
    /// \param vec The vector of elements
    template<typename T>
    void sort(std::vector<T> &vec);

    namespace details {
        template<typename T>
        /// \brief Returns the middle of the three arguments
        ///
        /// \param a The first value
        /// \param b The second value
        /// \param c The third value
        /// \return The middle of the three values
        T middle(T a, T b, T c);

        /// \brief Returns the middle of the three middle-of-threes in [first, last)
        ///
        /// \param first The beginning of the container
        /// \param last One past the end of the container
        /// \return An approximate middle value
        template<typename It, typename T = typename std::iterator_traits<It>::value_type>
        T ninther(It first, It last);

        /// \brief Quicksorts the elements [begin, end)
        ///
        /// \param begin The beginning of the container
        /// \param end One past the end of the container
        template<typename It, typename T = typename std::iterator_traits<It>::value_type>
        void quick_sort(It first, It last);
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    // Ensure sort algorithm and line count arguments
    if (args.size() < 3) {
        print_help();
        return 1;
    }

    // Make sure algorithm is implemented
    if (args[1] != "bubble"
        && args[1] != "heap"
        && args[1] != "insertion"
        && args[1] != "quick") {
        print_help();
        return 1;
    }

    // Make sure line count is a number
    long long num_lines = 0;
    try {
        num_lines = std::stoi(args[2]);
        if (num_lines < 0) throw std::exception();
    } catch (...) {
        print_help();
        return 1;
    }


    // Initialize vector of specified size
    std::vector<std::string> sortme;
    sortme.reserve(static_cast<unsigned long long>(num_lines));


    // Open input file
    std::ifstream infile;
    infile.open(SORT_FILE);
    if (infile.fail()) {
        std::cout << "Failed to read file '" << SORT_FILE << "'!" << std::endl;
        return 1;
    }

    // Read from file
    std::copy_n(std::istream_iterator<std::string>(infile),
                num_lines, std::back_inserter(sortme));

    // Close file
    infile.close();


    // Sort using chosen algorithm
    if (args[1] == "bubble")
        bubble_sort(sortme);
    else if (args[1] == "heap")
        heap_sort(sortme);
    else if (args[1] == "insertion")
        insertion_sort::sort(sortme);
    else if (args[1] == "quick")
        quick_sort::sort(sortme);
    else {
        print_help();
        return 1;
    }


    // Open output file
    std::ofstream outfile;
    outfile.open(OUT_FILE);
    if (outfile.fail()) {
        std::cout << "Failed to open file '" << OUT_FILE << "'!" << std::endl;
        return 1;
    }

    // Output sorted lines to output file
    std::copy(sortme.begin(), sortme.end(),
              std::ostream_iterator<std::string>(outfile, "\n"));


    // Check if sorted
    //std::cout << std::is_sorted(sortme.begin(), sortme.end()) << std::endl;

    return 0;
}

void print_help() {
    std::cout << "Usage: p4 [bubble|heap|insertion|quick] [LINES]" << std::endl;
    std::cout << "Sorts LINES of '" << SORT_FILE << "' to file 'sorted.dat'" << std::endl;
}

template<typename T>
void bubble_sort(std::vector<T> &vec) {
    size_t end = vec.size();

    while (end != 0) {
        size_t new_end = 0;

        // Bubble sort until `end`
        for (size_t i = 0; i < end - 1; ++i) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                new_end = i + 1;
            }
        }

        // Items after `end` are sorted
        end = new_end;
    }
}

template<typename T>
void heap_sort(std::vector<T> &vec) {
    std::make_heap(vec.begin(), vec.end());
    std::sort_heap(vec.begin(), vec.end());
}

namespace insertion_sort {
    template<typename T>
    void sort(std::vector<T> &vec) {
        details::sort(vec.begin(), vec.end());
    }

    namespace details {
        template<typename It>
        void sort(It begin, It end) {
            for (auto it = begin; it != end; ++it) {
                // Search for first greater value than `*it` via `upper_bound`
                // and move `*it` before the the greater value
                std::rotate(std::upper_bound(begin, it, *it), it, it + 1);
            }
        }
    }
}

namespace quick_sort {
    namespace details {
        template<typename T>
        T middle(T a, T b, T c) {
            // Returns the middle of three numbers
            return a > b ? (c > a ? a : (b > c ? b : c)) : (c > b ? b : (a > c ? a : c));
        }

        template<typename It, typename T = typename std::iterator_traits<It>::value_type>
        T ninther(It first, It last) {
            It middle1 = std::next(first, std::distance(first, last) / 3); // 1n / 3
            It middle2 = std::next(middle1, std::distance(first, last) / 3); // 2n / 3

            return middle(
                    // middle(0n / 3, 1n / 6, 1n / 3)
                    middle(*first, *std::next(first, std::distance(first, middle1) / 2), *middle1),
                    // middle(1n / 3, 3n / 6, 2n / 3)
                    middle(*middle1, *std::next(middle1, std::distance(middle1, middle2) / 2), *middle2),
                    // middle(2n / 3, 5n / 6, 3n / 3)
                    middle(*middle2, *std::next(first, std::distance(middle2, last) / 2), *--last)
            );
        }

        template<typename It, typename T = typename std::iterator_traits<It>::value_type>
        void quick_sort(It first, It last) {
            if (first == last) return;
            T pivot = ninther(first, last);

            // [first, middle1) < pivot
            // [middle1, middle2) == pivot
            // [middle2, last) > pivot
            It middle1 = std::partition(first, last, [pivot](const T &element) { return element < pivot; });
            It middle2 = std::partition(middle1, last, [pivot](const T &element) { return pivot >= element; });

            // Insertion sort if less than 10 items left
            if (std::distance(first, middle1) < 10)
                insertion_sort::details::sort(first, middle1);
            else
                quick_sort(first, middle1);

            if (std::distance(middle2, last) < 10)
                insertion_sort::details::sort(middle2, last);
            else
                quick_sort(middle2, last);
        }
    }

    template<typename T>
    void sort(std::vector<T> &vec) {
        details::quick_sort(vec.begin(), vec.end());
    }
}
