#include "person.h"
#include <iostream>

// Default constructor
Person::Person() : id(-1), first_name("?"), last_name("?"), hourly_rate(0.0f), hours_worked(0) {}

// Parameterized constructor
Person::Person(int starting_id, std::string start_fname, std::string start_lname)
    : id(starting_id), first_name(start_fname), last_name(start_lname), hourly_rate(0.0f), hours_worked(0) {
}

// Destructor
Person::~Person() {
}

// Getter methods (const for const-correctness)

int Person::get_id() const {
    return id;
}

std::string Person::get_first_name() const {
    return first_name;
}

std::string Person::get_last_name() const {
    return last_name;
}

float Person::get_hourly_rate() const {
    return hourly_rate;
}

unsigned int Person::get_hours_worked() const {
    return hours_worked;
}

// Setter methods
void Person::set_hourly_rate(float new_rate) {
    
    hourly_rate = new_rate;
}

void Person::set_hours_worked(unsigned int new_hours) {
    hours_worked = new_hours;
}

// Calculate wage (const method)
float Person::calculate_wage() const {
    return hourly_rate * hours_worked;
}
