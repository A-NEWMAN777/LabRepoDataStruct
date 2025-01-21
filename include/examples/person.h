#ifndef _PERSON_H_
#define _PERSON_H_

//prevents the compiler from ever seeing the declaration
//of this class twice.
//same as #ifndef _PERSON_H_
//		  #define _PERSON_H_

#include <string>

class Person
{	//by default everything is private
	
public:
	//Attributes -- a variable that all instances of the class have
	int id;
	std::string first_name;
	std::string last_name;
	float hourly_rate;
	unsigned int hours_worked;


	//METHOD -- a function that instances of the class can call
	float calulate_wage();

};
#endif
