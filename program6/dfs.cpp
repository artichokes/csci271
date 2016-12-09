/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 6, Due Friday, Dec. 9
 * Compile with -std=c++0x -O3
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <cstdio>
#include <unistd.h>

/// \brief A graph using an adjacency list
class Graph {
public:
    /// \brief Inserts a node into the graph
    ///
    /// \param node The vertex to add to the graph
    void insert_node(std::string node) {
        this->adjlist[node];
    }

    /// \brief Inserts an edge into the graph
    ///
    /// \param out The source node
    /// \param in The sink node
    void insert_edge(std::string out, std::string in) {
        this->adjlist[out].insert(in);
    }

    /// \brief Lists the adjacency matrix
    void list_graph() {
        for (const auto &out : this->adjlist) {
            std::cout << out.first << " -> ";
            for (const auto &in : out.second) {
                std::cout << in << ' ';
            }
            std::cout << '\n';
        }
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> adjlist;
};

namespace topsort {
    namespace details {
        /// \brief Recursively visits adjacent nodes
        ///
        /// \param graph The graph to traverse
        /// \param visited A map of visited vertices
        /// \param acc A list of visited node
        /// \param v The starting vertex
        void visit(Graph &graph,
                   std::unordered_map<std::string, char> &visited,
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

    /// \brief Topologically sorts a graph using DFS
    ///
    /// \param graph The graph to sort
    /// \return A list of the vertices topologically sorted
    std::list<std::string> sort(Graph &graph) {
        std::unordered_map<std::string, char> visited;
        std::list<std::string> result;

        for (const auto &v : graph.adjlist)
            visited[v.first] = false;

        for (const auto &v : graph.adjlist)
            if (visited[v.first] == 0)
                details::visit(graph, visited, result, v.first);

        return result;
    }
}

/// \brief Reads from an input stream into a graph
///
/// \param courses_stream The stream to read from
/// \param graph The graph to add nodes and edges to
void readCourses(std::istream &courses_stream, Graph &graph) {
    for (std::string innode; courses_stream >> innode && innode != "";) {
        std::transform(innode.begin(), innode.end(), innode.begin(), ::tolower);
        graph.insert_node(innode);

        for (std::string outnode; courses_stream >> outnode && outnode != "#";) {
            std::transform(outnode.begin(), outnode.end(), outnode.begin(), ::tolower);
            graph.insert_node(outnode);
            graph.insert_edge(outnode, innode);
        }
    }
}

int main(int argc, char *argv[]) {
    Graph courses;

    // If stdin is not a file redirection
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
