// #pragma once       // does the same compiler guard as below
#ifndef _PERSON_H_    // "compiler guard" -- makes sure this
#define _PERSON_H_    //   header file (and the stuff within it...our
					  //   class declaration) is only seen once by the
					  //   compiler
#include <string>

class Person
{
	// These are ATTRIBUTES -- variables that each instance of the class
	// gets a copy of.
	// By default all members of a class are PRIVATE (we can only
	//   access them in a method).  Normally we make our attributes private
	//   but methods public.
private:
	int id;
	std::string first_name;
	std::string last_name;
	float hourly_rate;
	unsigned int hours_worked;

public:
	// This is the CONSTRUCTOR -- a method that has no return type and MUST 
	// have the same name as the class.  This is a DEFAULT CONSTRUCTOR (no parameters)
	Person();

	// This is ANOTHER CONSTRUCTOR (this is an OVERLOAD...alternate version) of the constructor
	Person(int start_id, std::string start_fname, std::string start_lname);

	// This is the DESTRUCTOR.  This is called when an instance is about to go "away",
	// This method gets called.  It is unusual to call this manually.  More often, it's
	// called when an instance goes out of scope (scope is where that variable is visible, or
	// is defined).  Do any kind of cleanup you wish.  Biggie: if you dynamically allocated
	// any memory, this is a good place to clean it up.
	~Person();

	// This is a METHOD -- a function that all instances of the class can
	// use.  This is a DECLARATION.  
	float calculate_pay();

	// These are examples of SETTERS
	void set_hourly_rate(float new_rate);
	void set_hours_worked(unsigned int new_hours);

	// These are examples of GETTERS
	int get_id();
	std::string get_first_name();
	std::string get_last_name();
	unsigned int get_hours_worked();
	float get_hourly_rate();

};

#endif