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
#include <cstdio>
#include <unistd.h>

class Graph {
public:
    Graph() {}

    void insert_node(std::string node) {
        this->adjlist[node];
    }

    void insert_edge(std::string out, std::string in) {
        this->adjlist[out].insert(in);
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

    std::map<std::string, std::set<std::string>> adjlist;
};

namespace topsort {
    namespace details {
        void visit(Graph &graph,
                   std::map<std::string, char> &visited,
                   std::list<std::string> &acc,
                   std::string const &v) {
            if (visited[v] == 1)
                throw "Graph is not a DAG!";

            if (visited[v] == 0) {
                visited[v] = 1; // Temporarily mark the node

                for (const auto &w : graph.adjlist[v])
                    visit(graph, visited, acc, w);

                visited[v] = 2; // Mark the node as visited

                acc.push_front(v); // Prepend the node to the result
            }
        }
    }

    // Uses DFS
    std::list<std::string> sort(Graph &graph) {
        std::map<std::string, char> visited;
        std::list<std::string> result;

        for (const auto &v : graph.adjlist)
            visited[v.first] = false;

        for (const auto &v : graph.adjlist)
            if (visited[v.first] == 0)
                details::visit(graph, visited, result, v.first);

        return result;
    }
}

void readCourses(std::istream &courses_stream, Graph &graph) {
    for (std::string innode; courses_stream >> innode && innode != "";) {
        graph.insert_node(innode);

        for (std::string outnode; courses_stream >> outnode && outnode != "#";) {
            graph.insert_node(outnode);
            graph.insert_edge(outnode, innode);
        }
    }
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

    try {
        // Try to sort the graph
        for (const auto &v : topsort::sort(courses))
            std::cout << v << '\n';
    } catch (const char* err) {
        std::cout << err << std::endl;
        return 1;
    }


    return 0;
}
