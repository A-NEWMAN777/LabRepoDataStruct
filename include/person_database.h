#ifndef PERSON_DATABASE_H
#define PERSON_DATABASE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "person.h"

namespace example {
    /// <summary>
    /// This is the class for the Person Database which contains Person objects as well as integer values for the capacity of the array, 
    /// how many people are currently in the array,
    /// the name of the txt file that is given when a Person Database object is created. This class includes methods to add/remove a person
    /// from the file and array, a Getter method for num_people, 
    /// and a method the convert the database to a string(for printing to txt file more efficiently).
    /// </summary>
    class PersonDatabase {
    private:
        /// <summary>
        /// This is a Dynamic array of Person objects
        /// </summary>
        Person* people;
        /// <summary>
        /// This is the current capacity of the array
        /// </summary>
        int capacity;
        /// <summary>
        /// This is the current # of people in the array
        /// </summary>
        int num_people;
        /// <summary>
        /// This is the name of the file that the methods read/write to
        /// </summary>
        std::string filename;


    public:
        /// <summary>
        /// Constructor for PersonDatabase that requires the name of a file that the program will use to store data;
        /// if the file does not exist, the program will create it.
        /// </summary>
        /// <param name="file">this is the name of the file in relation to the projects location</param>
        PersonDatabase(const std::string& file);

        /// <summary>
        /// Deconstructor method; correctly saves data so that it does not need to be reentered after a restart.
        /// </summary>
        ~PersonDatabase();

        /// <summary>
        /// Method to add a new Person object to the array and the txt file.
        /// </summary>
        /// <param name="new_person">new person object</param>
        void add_person(const Person& new_person);

        /// <summary>
        /// Method to remove an existing Person odject from the array and the txt file; requires the user to enter an existing ID
        /// </summary>
        /// <param name="id">id of the person object</param>
        /// <returns>returns 0 or 1</returns>
        bool remove_person(int id);

        /// <summary>
        /// Getter method for the number of people in the array
        /// </summary>
        /// <returns>returns an integer</returns>
        int get_num_people() const;

        /// <summary>
        /// Method that converts the entire database into a string.
        /// </summary>
        /// <returns>returns an integer</returns>
        std::string to_string() const;
    };

} // namespace example

#endif
