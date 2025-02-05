#include "person_database.h"

namespace example {

    PersonDatabase::PersonDatabase(const std::string& file)
        : people(nullptr), capacity(10), num_people(0), filename(file) {
        people = new Person[capacity];  // Allocate memory for a fixed number of people

        std::fstream infile(file, std::ios::in);  // Open file for reading
        if (!infile) {
            // File doesn't exist or couldn't be opened
            return; // No data is loaded if the file doesn't exist
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

            // Only add person if we have space in the array
            if (num_people < capacity) {
                people[num_people++] = Person(id, first_name, last_name);
                people[num_people - 1].set_hourly_rate(hourly_rate);
                people[num_people - 1].set_hours_worked(hours_worked);
            }
        }
        infile.close();
    }

    PersonDatabase::~PersonDatabase() {
        // Write the database to the file using fstream
        std::fstream outfile(filename, std::ios::out); // Open file for writing
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

    void PersonDatabase::add_person(const Person& new_person) {
        // Check if there is space in the array to add a new person
        if (num_people < capacity) {
            // Add new person to the array
            people[num_people++] = new_person;
        }
        else {
            capacity = capacity * 2;
        }
    }

    bool PersonDatabase::remove_person(int id) {
        for (int i = 0; i < num_people; ++i) {
            if (people[i].get_id() == id) {
                // Shift remaining elements to remove the person
                for (int j = i; j < num_people - 1; ++j) {
                    people[j] = people[j + 1];
                }
                --num_people;

                // After removal, we need to rewrite the file to reflect the change
                std::fstream outfile(filename, std::ios::out | std::ios::trunc);  // Open file for overwriting
                if (outfile) {
                    for (int i = 0; i < num_people; ++i) {
                        outfile << people[i].get_id() << " "
                            << people[i].get_first_name() << " "
                            << people[i].get_last_name() << " "
                            << people[i].get_hourly_rate() << " "
                            << people[i].get_hours_worked() << "\n";
                    }
                    std::cout << "Person removed and file updated successfully.\n";
                }
                else {
                    std::cerr << "Failed to open the file for updating.\n";
                }

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
        oss << "===============================================================================================================\n"
            << "===============================================================================================================\n";

        for (int i = 0; i < num_people; ++i) {
            const Person& person = people[i];
            float wage = person.calculate_wage();
            total_salary += wage;
            oss << "||ID||=||First Name||=||Last Name||=||Hours Worked||=||Hourly Rate||====||Wage||\n  "
                << person.get_id() << "   \t "
                << person.get_first_name() << "\t\t"
                << person.get_last_name() << "\t\t"
                << person.get_hours_worked() << "hrs"
                << "\t" << person.get_hourly_rate() << "$/hr"
                << "\t\t$" << wage << "\n";
        }

        oss << "===============================================================================================================\n"
            << "===============================================================================================================\n"
            << "Total: $" << total_salary << "\n";
        return oss.str();
    }

} // namespace example
