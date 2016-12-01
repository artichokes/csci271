/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 6, Due Friday, Dec. 9
 * Compile with -std=c++0x -O3
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <cstdio>
#include <unistd.h>

class Graph {
public:
    Graph() {}

    void insert_node(std::string node) {
        if (this->adjlist.find(node) == this->adjlist.end()) { // Node not in adjlist
            this->adjlist[node]; // Add node to adjlist
            this->indegree[node] = 0; // Set node's indegree to 0
        }
    }

    void insert_edge(std::string out, std::string in) {
        this->adjlist[out].insert(in); // Add edge
        ++this->indegree[in]; // Increment indegree
    }

    void list_graph() {
        for (const auto &out : this->adjlist) {
            std::cout << out.first << " -> ";
            for (const auto &in : out.second) {
                std::cout << in << ' ';
            }
            std::cout << '\n';
        }
    }

    void list_indegree() {
        for (const auto &v : this->indegree) {
            std::cout << v.first << ' ' << v.second << std::endl;
        }
    }

    std::map<std::string, std::set<std::string>> adjlist;
    std::map<std::string, unsigned> indegree;
};

void readCourses(std::istream &courses_stream, Graph &graph) {
    for (std::string innode; courses_stream >> innode;) {
        graph.insert_node(innode);

        for (std::string outnode; courses_stream >> outnode && outnode != "#";) {
            graph.insert_node(outnode);
            graph.insert_edge(outnode, innode);
        }
    }
}

std::list<std::string> topsort(Graph &graph) {
    std::list<std::string> result; // Result list
    std::queue<std::string> noin; // Set of nodes with no incoming edges

    // Initialize noin
    for (const auto &v : graph.indegree)
        if (v.second == 0)
            noin.push(v.first);

    while (!noin.empty()) {
        const std::string &n = noin.front();
        noin.pop();

        result.push_back(n);

        // For each node m with an edge e from n to m
        for (const auto &m : graph.adjlist[n]) {
            if (--graph.indegree[m] == 0) // If m has no other incoming edges
                noin.push(m);
        }

        // Remove vertex n and all outgoing edges
        graph.adjlist.erase(n);
    }

    if (!graph.adjlist.empty())
        throw "Graph is not a DAG!";
    else
        return result;
}

int main(int argc, char *argv[]) {
    Graph courses;

    if (isatty(fileno(stdin))) {
        std::cout << "Please use stdin redirection,"
                  << " e.g. `p6 < courses.dat`, to read a file."
                  << std::endl;
        return 1;
    }

    readCourses(std::cin, courses);

//    courses.list_graph();
//    courses.list_indegree();

    try {
        // Try to sort the graph
        for (const auto &v : topsort(courses))
            std::cout << v << '\n';
    } catch (const char* err) {
        std::cout << err << std::endl;
        return 1;
    }


    return 0;
}
