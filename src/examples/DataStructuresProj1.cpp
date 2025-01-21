// DataStructuresProj1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "person.h"
#include <string.h>
#include <string> // The C++ string class library
using namespace std; // makes the std:: stuff optional

int main()
{
    size_t x = 42;
    double z = 3.14;
    float y = 3.14f;
    char name[32] = "Bob James"; //C-style (a changeable string array)
    const char* name2 = "Sally Smith"; //C-style (an unchangeable string literal)
    strcpy_s(name, "Robert Jones");
    x = strlen(name); // 12
    if (strcmp(name, "mmmm") < 0)
        printf("name is alphabetically less than mmm");
    
    std::string cpp_name = "Bob Jones"; //internally, the # of chars is still important
    x = cpp_name.length();
    if (cpp_name < "mmmm")
        cout << "cpp_name is alphabetically less than mmm";
    name2 = cpp_name.c_str();

    //Our goal will be to make structures like this
    //that will simplify the job of the user.


    cout << "x=" << x << "abc" << "Hello World!\n";

    Person p;
    Person q;

    p.id = 42;
    q.id = 43;
    p.first_name = "Bob";
    q.first_name = "Sally";

    std::cout << p.id << " " << p.first_name;

    

    cin >> x; //waiting fot the user to enter a value for x



    
    
}

