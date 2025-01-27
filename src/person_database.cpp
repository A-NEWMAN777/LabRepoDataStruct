#include "person_database.h"

namespace example {

    PersonDatabase::PersonDatabase(const std::string& file)
        : people(nullptr), capacity(0), num_people(0), filename(file) {
        std::ifstream infile(file);
        if (!infile) {
            // File doesn't exist or couldn't be opened
            return; // No allocation needed
        }

        // Read data from the file
        std::string line;
        while (std::getline(infile, line)) {
            // Parsing logic for each person (ID, first_name, last_name, hourly_rate, hours_worked)
            int id;
            std::string first_name, last_name;
            float hourly_rate;
            unsigned int hours_worked;

            std::istringstream ss(line);
            ss >> id >> first_name >> last_name >> hourly_rate >> hours_worked;

            // Add person to the database
            if (num_people >= capacity) {
                resize();
            }
            people[num_people++] = Person(id, first_name, last_name);
            people[num_people - 1].set_hourly_rate(hourly_rate);
            people[num_people - 1].set_hours_worked(hours_worked);
        }
        infile.close();
    }

    PersonDatabase::~PersonDatabase() {
        // Write the database to the file
        std::ofstream outfile(filename);
        if (outfile) {
            for (int i = 0; i < num_people; ++i) {
                outfile << people[i].get_id() << " "
                    << people[i].get_first_name() << " "
                    << people[i].get_last_name() << " "
                    << people[i].get_hourly_rate() << " "
                    << people[i].get_hours_worked() << "\n";
            }
        }
        delete[] people;
    }

    void PersonDatabase::resize() {
        // Resize the array by doubling the capacity
        int new_capacity = (capacity == 0) ? 2 : capacity * 2;
        Person* new_people = new Person[new_capacity];
        for (int i = 0; i < num_people; ++i) {
            new_people[i] = people[i];
        }
        delete[] people;
        people = new_people;
        capacity = new_capacity;
    }

    void PersonDatabase::add_person(const Person& new_person) {
        // Check if the person with the same ID already exists
        for (int i = 0; i < num_people; ++i) {
            if (people[i].get_id() == new_person.get_id()) {
                throw std::runtime_error("ID already exists in the database.");
            }
        }

        // Resize if necessary
        if (num_people >= capacity) {
            resize();
        }

        // Add new person to the array
        people[num_people++] = new_person;
    }

    bool PersonDatabase::remove_person(int id) {
        for (int i = 0; i < num_people; ++i) {
            if (people[i].get_id() == id) {
                // Shift remaining elements to remove the person
                for (int j = i; j < num_people - 1; ++j) {
                    people[j] = people[j + 1];
                }
                --num_people;
                return true;
            }
        }
        return false;
    }

    int PersonDatabase::get_num_people() const {
        return num_people;
    }

    std::string PersonDatabase::to_string() const {
        std::ostringstream oss;
        float total_salary = 0.0f;

        oss << "Person Database\n";
        oss << "==============================================================================================================\n"
            << "==============================================================================================================\n";


        for (int i = 0; i < num_people; ++i) {
            const Person& person = people[i];
            float wage = person.calculate_wage();
            total_salary += wage;
            oss << "||ID||=||First Name||=||Last Name||=||Hours Worked||=||Hourly Rate||====||Wage||\n  " << person.get_id()
                << "   \t "<< person.get_first_name() 
                << "\t\t" << person.get_last_name() 
                << "\t" << person.get_hours_worked() <<"hrs" 
                << "\t\t" << person.get_hourly_rate() <<"$/hr"
                << "\t$" << wage << "\n\n";
        }

        oss << "===============================================================================================================\n"
            << "===============================================================================================================\n" << "Total: $" << total_salary << "\n";
        return oss.str();
    }
    

} // namespace example
