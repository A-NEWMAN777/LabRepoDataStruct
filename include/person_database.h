#ifndef PERSON_DATABASE_H
#define PERSON_DATABASE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "person.h"

namespace example {

    class PersonDatabase {
    private:
        Person* people; // Dynamic array of Person objects
        int capacity;    // Current capacity of the array
        int num_people;  // Number of Person objects in the array
        std::string filename; // File to read from and write to

        // Helper method to resize the array when adding a person
        void resize();

    public:
        // Constructor takes a filename to load the database
        PersonDatabase(const std::string& file);

        // Destructor saves data and frees memory
        ~PersonDatabase();

        // Adds a new person to the database
        void add_person(const Person& new_person);

        // Removes a person by ID from the database
        bool remove_person(int id);

        // Returns the number of people in the database
        int get_num_people() const;

        // Returns a string representation of the entire database
        std::string to_string() const;
    };

} // namespace example

#endif
