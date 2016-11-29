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

#ifdef DEBUG
const std::string COURSES_FILE = "./resources/courses.dat";
#endif

class Graph {
public:
    Graph() {}

    void insert_vertex(std::string vertex) {
        this->adjlist[vertex];
    }

    void insert_edge(std::string in, std::string out) {
        this->adjlist[out].insert(in);
    }

    void list_graph() {
        for (const auto &v : this->adjlist) {
            std::cout << v.first << " -> ";
            for (const auto &e : v.second) {
                std::cout << e << ' ';
            }
            std::cout << '\n';
        }
    }

    std::map<std::string, std::set<std::string>> adjlist;
};

namespace topsort {
    namespace details {
        void tophelp(Graph &graph,
                     std::map<std::string, bool> &visited,
                     std::list<std::string> &acc,
                     std::string const &v) {
            visited[v] = true;

            for (const auto &w : graph.adjlist[v])
                if (!visited[w])
                    tophelp(graph, visited, acc, w);

            acc.push_front(v);
        }
    }

    // Uses DFS
    std::list<std::string> sort(Graph &graph) {
        std::map<std::string, bool> visited;
        std::list<std::string> result;

        for (const auto &v : graph.adjlist)
            visited[v.first] = false;

        for (const auto &v : graph.adjlist)
            if (!visited[v.first])
                details::tophelp(graph, visited, result, v.first);

        return result;
    }
}

void readCourses(std::istream &courses_stream, Graph &graph) {
    for (std::string innode; courses_stream >> innode;) {
        graph.insert_vertex(innode);

        for (std::string outnode; courses_stream >> outnode && outnode != "#";) {
            graph.insert_edge(innode, outnode);
        }
    }
}

int main(int argc, char *argv[]) {
    Graph courses;

    // Open courses file
    std::ifstream coursesFile;
    coursesFile.open(COURSES_FILE);
    if (coursesFile.fail()) {
        std::cout << "Failed to open file '" << COURSES_FILE << "'!" << std::endl;
        return 1;
    }

    readCourses(coursesFile, courses);

    for (const auto &v : topsort::sort(courses))
        std::cout << v << '\n';

    // Close courses file
    coursesFile.close();

    return 0;
}
