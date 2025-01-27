#include <iostream>
#include <string.h>
#include <string>               // The C++ string class library   
#include <person.h>
using namespace std;            // makes the std:: stuff optional

int main()
{
    /*int x = 42;
    double z = 3.14;
    float y = 3.14f;

    // C-style strings
    char name[32] = "Bob Jones";        // C-style (a changeable array)
    const char* name2 = "Sally Smith";  // C-style (an unchangeable string literal)
    strcpy(name, "Robert Jones");       // Copy a new literal into name
    x = strlen(name);                   // 12
    if (strcmp(name, "mmmm") < 0)
        printf("name is alphabetically less than mmm\n");

    std::string cpp_name = "Bob Jones"; // internally, the # of chars is still important
    cpp_name = "Robert Jones";          // no strcpy necessary
    x = cpp_name.length();              // like strlen
    if (cpp_name < "mmmm")
        std::cout << "cpp_name is alphabetically less than mmm\n";
    name2 = cpp_name.c_str();           // Getting the UNDERLYING C char pointer!

    // Our goal with data structures will be to make constructs like this
    // that simplify the job of the user.

    cout << "x=" << x << "abc" << "Hello World!\n";*/

    // Some code that uses the Person class (defined STATICALLY)
    Person p(42, "Bob", "Jones");
    Person q(43, "Sally", "Smith");

    p.set_hourly_rate(15.0f);
    p.set_hours_worked(38);
    q.set_hourly_rate(16.75f);
    q.set_hours_worked(42);

    // We can also DYNAMICALLY allocate a person object
    Person* pptr = new Person(44, "Eric", "Davis");     // like malloc (new is preferred
    //   b/c it works with Classes)
    pptr->set_hourly_rate(12.15f);
    pptr->set_hours_worked(23);
    (*pptr).set_hourly_rate(12.35f);        // Same as line 45, but uglier

    delete pptr;                            // Like free -- frees up the memory
    //  pptr points to.  The C++ runtime
    //  calls the destructor right before
    //  the memory is freed.
    pptr = NULL;        // NULL is just a macro for 0
    int y = NULL;       // valid, but "weird"
    pptr = nullptr;     // A C++-only thing
    //y = nullptr;        // Error b/c pointers are only ones to use nullptr

    pptr = new Person(45, "Kim", "Young");
    // Do things with it
    delete pptr;


    std::cout << p.get_id() << " " << p.get_first_name() << "\n";

    // p and q were allocated on the STACK (an area of memory).  STACK is
    // where "temporary" variables (parameters in functions, p and q here.  
    // HEAP memory is where dynamically allocated memory comes from.
    // STACK and HEAP memory are shared.  If one gets too big, a STACK OVERFLOW

    // When p and q go out of SCOPE (where you can access the variable)
    // stack variables go away.  The destructor gets called right before this
    // happens.  You shouldn't call the destructor manually.
}