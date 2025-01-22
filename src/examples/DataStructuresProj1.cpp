#include <person.h>
#include <iostream>
#include <string>

void func()
{
	Person a(45, "Sally", "Smith");
	std::cout << "Doing something...\n";
}

int main(int argc, char** argv)
{
	// Making two instances (or object) of the Person class
	Person p(42, "Bob", "Jones");		// using the "real" constructor
	Person q;							// using the default constructor

	//p.id = 42;
	//p.hours_worked = 17;
	//p.hourly_rate = 13.5f;
	p.set_hourly_rate(13.5f);
	p.set_hours_worked(17);

	func();

	Person* pptr;                      // Declaring a pointer to a Person (NOT A PERSON!!!)
	//    uninitialized at the moment;
	pptr = NULL;				// NULL is a macro (the value 0)
	int x = NULL;               // Assigning the VALUE 0 to x (x is NOT a pointer)
	pptr = nullptr;				// Like NULL but can only be assigned to pointer types
	//x = nullptr;				// Error because x is not a pointer

	pptr = new Person(46, "Jim", "Price");   // new is like malloc in that it dynamically allocates
	// memory from the HEAP.  Returns a pointer to a Person.
	// malloc doesn't do anything with constructors or destructors

// Examples of DE-REFERENCING the pointer
	pptr->set_hourly_rate(11.3f);
	(*pptr).set_hourly_rate(11.3f);			// Same as line before.
	std::cout << "Doing some more stuff with the Person pointed to by pptr\n";
	// Free up that Person object
	delete pptr;							// Freeing the memory pointed to by pptr.  pptr's still 
	//   holding the same address (DANGLING-POINTER) -- don't 
	//   use that address or bad things will happen.  Calling
	//   delete causes the destructor to get run AND then
	//   the memory is freed up.
	pptr = nullptr;

	// Make a new person using pptr
	pptr = new Person(47, "Julia", "Young");
	pptr->set_hourly_rate(14.5f);
	delete pptr;							// This calls the Destructor, then frees up this chunk
	//   of memory pointed to by pptr.


	std::cout << "The pay for p is " << p.calculate_pay() << "\n";
	std::cout << "The pay for q is " << q.calculate_pay() << "\n";

	return 0;
}