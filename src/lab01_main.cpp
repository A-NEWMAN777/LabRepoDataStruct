#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "person.h"
#include "person_database.h"

using namespace example;

void display_menu() {
    std::cout << "\nMenu Options:\n";
    std::cout << "1. Add Person\n";
    std::cout << "2. Remove Person\n";
    std::cout << "3. Print Database\n";
    std::cout << "4. Quit\n";
    std::cout << "Please enter your choice (1-4): ";
}

int main() {
    // Create the PersonDatabase object, assuming the file is stored in a "media" folder
    PersonDatabase db("../media/p_database.txt");

    bool running = true;
    while (running) {
        display_menu();

        int choice = 0;
        std::cin >> choice;

        // Input validation for choice
        if (!std::cin) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input! Please enter a number between 1 and 4.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            // Add Person
            int id;
            std::string first_name, last_name;
            float hourly_rate;
            unsigned int hours_worked;

            // Collect information from the user
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter First Name: ";
            std::cin >> first_name;
            std::cout << "Enter Last Name: ";
            std::cin >> last_name;
            std::cout << "Enter Hourly Rate: ";
            std::cin >> hourly_rate;
            std::cout << "Enter Hours Worked: ";
            std::cin >> hours_worked;

            // Check for input validity
            if (!std::cin) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input for one or more fields! Please try again.\n";
                continue;
            }

            try {
                // Create Person and add to the database
                Person new_person(id, first_name, last_name);
                new_person.set_hourly_rate(hourly_rate);
                new_person.set_hours_worked(hours_worked);

                db.add_person(new_person);
                std::cout << "Person added successfully.\n";
            }
            catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 2: {
            // Remove Person
            int id;
            std::cout << "Enter ID to remove: ";
            std::cin >> id;

            // Check for valid input
            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a valid ID number.\n";
                continue;
            }

            bool success = db.remove_person(id);
            if (success) {
                std::cout << "Person removed successfully.\n";
            }
            else {
                std::cout << "Person with ID " << id << " not found.\n";
            }
            break;
        }

        case 3: {
            // Print Database
            std::cout << db.to_string() << std::endl;
            break;
        }

        case 4:
            // Quit the program
            running = false;
            std::cout << "Exiting the program.\n";
            break;

        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}
