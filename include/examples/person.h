#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>

class Person
{
private:
    int id;
    std::string first_name;
    std::string last_name;
    float hourly_rate;
    unsigned int hours_worked;

public:
    // Constructors
    Person();
    Person(int starting_id, std::string start_fname, std::string start_lname);

    // Destructor
    ~Person();

    // Getter methods (const for const-correctness)
    int get_id() const;
    std::string get_first_name() const;
    std::string get_last_name() const;
    float get_hourly_rate() const;
    unsigned int get_hours_worked() const;

    // Setter methods
    void set_hourly_rate(float new_rate);
    void set_hours_worked(unsigned int new_hours);

    // Calculate wage (mark it as const because it doesn't modify the object)
    float calculate_wage() const;
};

#endif
