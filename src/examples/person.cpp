// person.cpp -- houses the BODIES (DEFINITIONS) of all methods
#include <person.h>
#include <iostream>

// General structure:     ReturnType ClassName::MethodName(PARAMETERS) { .... }

float Person::calculate_pay()
{
	// We have access to all attributes since we're a part of the class
	return hourly_rate * hours_worked;
}


void Person::set_hourly_rate(float new_rate)
{
	// Imagine that we COULD do data validation rules to make sure new_rate
	// makes sense (according to company policy) before assigning it.  
	// We can also set breakpoints here to DETECT any time a change is made
	hourly_rate = new_rate;
}


void Person::set_hours_worked(unsigned int new_hours)
{
	hours_worked = new_hours;
}



int Person::get_id()
{
	return id;
}


std::string Person::get_first_name()
{
	return first_name;
}


std::string Person::get_last_name()
{
	return last_name;
}


float Person::get_hourly_rate()
{
	return hourly_rate;
}


unsigned int Person::get_hours_worked()
{
	return hours_worked;
}


Person::Person()
{
	id = -1;
	first_name = "?";
	last_name = "?";
	hours_worked = 0;
	hourly_rate = 0.0f;
}


Person::Person(int start_id, std::string start_fname, std::string start_lname)
{
	id = start_id;
	first_name = start_fname;
	last_name = start_lname;
	hours_worked = 0;
	hourly_rate = 0.0f;
}


Person::~Person()
{
	std::cout << "The person named " << first_name << " " << last_name << " is about to go away.\n";
}