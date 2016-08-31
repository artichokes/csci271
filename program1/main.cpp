/*
 * Peter Nguyen
 * CSCI 271, Fall 2016
 * Program 1, Due Thursday, Sept. 1
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>

#ifdef DEBUG
const std::string MASTER_FILE = "./resources/master.dat";
const std::string GROUPS_FILE = "./resources/groups.dat";
#else
const std::string MASTER_FILE = "/home/win.thackerw/271/peer/master.dat";
const std::string GROUPS_FILE = "/home/win.thackerw/271/peer/groups.dat";
#endif

// A structure to represent a person
struct Person {
    std::string last_name; // The person's last name
    long grade_average; // The person's average grade

    Person(std::string last_name, long grade_average) :
            last_name(last_name), grade_average(grade_average) {}
};

// A structure to represent a group
struct Group {
    std::string last_name; // The person's last name as the origin
    unsigned size; // The size of the group

    Group(std::string last_name, unsigned size) :
            last_name(last_name), size(size) {}
};

// Reads in people from the filename.
// @param[in]  filename The filename to read from.
// @param[out] people The list of persons to append the people to.
// @returns True, if file is read successfully.
bool readPeople(std::string filename, std::list<Person> &people);

// Reads in groups from the filename.
// @param[in]  filename The filename to read from.
// @param[out] groups The list of groups to append to.
// @return bool True, if file is read successfully.
bool readGroups(std::string filename, std::list<Group> &groups);

// Defines sorting order for people.
// Sorts people by the difference in average grade from an origin
struct ByAverageGradeDifference {
    const Person &origin;

    ByAverageGradeDifference(const Person &origin) : origin(origin) {}

    bool operator()(const Person &lp, const Person &rp) {
        return diff(origin, lp) < diff(origin, rp);
    }

    static long diff(const Person &lp, const Person &rp) {
        return std::abs(lp.grade_average - rp.grade_average);
    }
};

// Returns the n closest people by average grade
// @param[in]  population A list of people.
// @param[in]  last_name The last name of the person to query for.
// @param[in]  n The number of closest people.
// @param[out] closest The list of n people.
// @return bool True, if the person is found.
bool closest_n(std::list<Person> &population, std::string last_name, unsigned n, std::list<Person> &closest);

int main() {
    // Read list of people
    std::list<Person> people;
    if (!readPeople(MASTER_FILE, people)) {
        std::cout << "Failed to read " << MASTER_FILE << std::endl;
        return 1;
    }

    // Read list of groups
    std::list<Group> groups;
    if (!readGroups(GROUPS_FILE, groups)) {
        std::cout << "Failed to read " << GROUPS_FILE << std::endl;
        return 1;
    }

    // Iterate through each group
    for (std::list<Group>::iterator it = groups.begin(); it != groups.end(); ++it) {
        // Find the n closest people by average grade
        std::list<Person> closest;
        if (!closest_n(people, it->last_name, it->size, closest)) {
            std::cout << "Failed to find person: " << it->last_name << std::endl;
            return 1;
        }

        // Output the list of n closest people
        std::cout << "Closest " << it->size << " people to " << it->last_name << " by average grade:" << std::endl;
        for (std::list<Person>::iterator closest_it = closest.begin(); closest_it != closest.end(); ++closest_it)
            std::cout << closest_it->last_name << ' ' << closest_it->grade_average << std::endl;

        std::cout << std::endl;
    }

    return 0;
}

bool readPeople(std::string filename, std::list<Person> &people) {
    std::fstream master_fs(filename, std::ios::in);

    if (master_fs.fail())
        return false;

    std::string last_name;
    long average;

    while (master_fs >> last_name >> average)
        people.push_back(Person(last_name, average));

    master_fs.close();
    return true;
}

bool readGroups(std::string filename, std::list<Group> &groups) {
    std::fstream groups_fs(filename, std::ios::in);

    if (groups_fs.fail())
        return false;

    std::string last_name;
    unsigned group_size;

    while (groups_fs >> last_name >> group_size)
        groups.push_back(Group(last_name, group_size));

    groups_fs.close();
    return true;
}

bool closest_n(std::list<Person> &population, std::string last_name, unsigned n, std::list<Person> &closest) {
    std::list<Person>::iterator person_iterator = std::find_if(
            population.begin(),
            population.end(),
            [&last_name] (const Person &person) { return person.last_name == last_name; }
    );

    if (person_iterator == population.end())
        return false;

    ByAverageGradeDifference difference(*person_iterator);

    // Create a temporary list of the population and sort it by the
    // average grade difference from the selected person
    std::list<Person> temp(population);

    // Remove the person from the list
    std::list<Person>::iterator temp_it = temp.begin();
    std::advance(temp_it, std::distance(population.begin(), person_iterator));
    temp.erase(temp_it);

    // Sort the list using the difference object
    temp.sort(difference);

    // Append the closest n people to the output list
    size_t i = 0;
    for (std::list<Person>::iterator it = temp.begin(); it != temp.end() && i < n; ++it) {
        closest.push_back(*it);
        ++i;
    }

    return true;
}
