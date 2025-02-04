#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
/// <summary>
/// Class for a single person object that contains a person's ID, First Name, Last Name, hourly rate, and hours worked.
/// Contains Getter methods for ID, first and last name, hours worked, and hourly rate.
/// Contains Setter methods for hours worked and hourly rate.
/// Contains a method to calculate the wage of the person.
/// </summary>
class Person
 
{
private:
    /// <summary>
    /// This is the ID# of the person
    /// </summary>
    int id;
    /// <summary>
    /// This is the First Name of the person
    /// </summary>
    std::string first_name;
    /// <summary>
    /// This is the Last Name of the person
    /// </summary>
    std::string last_name;
    /// <summary>
    /// This is the hourly rate of the person
    /// </summary>
    float hourly_rate;
    /// <summary>
    /// This is the # of hours worked by the person
    /// </summary>
    unsigned int hours_worked;

public:
    // Constructors
    Person();
    Person(int starting_id, std::string start_fname, std::string start_lname);

    // Destructor
    ~Person();

    /// <summary>
    /// Getter method for ID
    /// </summary>
    /// <returns>returns an integer</returns>
    int get_id() const;
    /// <summary>
    /// Getter method for first name
    /// </summary>
    /// <returns>returns a string</returns>
    std::string get_first_name() const;
    /// <summary>
    /// Getter method for last name
    /// </summary>
    /// <returns>returns a string</returns>
    std::string get_last_name() const;
    /// <summary>
    /// Getter method for hourly rate
    /// </summary>
    /// <returns>returns a float</returns>
    float get_hourly_rate() const;
    /// <summary>
    /// Getter method for hours worked
    /// </summary>
    /// <returns>returns an unsigned int</returns>
    unsigned int get_hours_worked() const;

    /// <summary>
    /// Setter method for hourly rate; requires new rate as parameter
    /// </summary>
    /// <param name="new_rate">this is a float that represents the new rate</param>
    void set_hourly_rate(float new_rate);
    /// <summary>
    /// Setter method for hours worked; required new hours as parameter
    /// </summary>
    /// <param name="new_hours">this is an unsigned int that represents the new # of hours worked</param>
    void set_hours_worked(unsigned int new_hours);

    /// <summary>
    /// Simple method that calculates the wage of a person by multplying their hours worked by their hourly rate
    /// </summary>
    /// <returns>returns a float</returns>
    float calculate_wage() const;
};

#endif
