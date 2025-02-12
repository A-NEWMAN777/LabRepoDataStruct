#include <iostream>
#include "array_list.h"
#include "person.h" // Assuming this is the class you've defined elsewhere

int main() {

    // Test 1: Basic operations with float
    ssuds::ArrayList<float> float_list;
    std::cout << "test1 (basic operations with float):\n=====\n";

    // Append
    float_list.append(2.1f);
    float_list.append(3.6f);

    // Output size and items
    std::cout << "\tsize=" << float_list.size() << std::endl;
    std::cout << "\titem0=" << float_list.at(0) << std::endl;
    std::cout << "\titem1=" << float_list.at(1) << std::endl;

    // Test 2: Insert operations for float
    std::cout << "test2 (insert operations with float):\n=====\n";
    float_list.insert(1.8f, 0);  // Insert at beginning
    float_list.insert(4.2f, 3);  // Insert at the end
    float_list.insert(2.0f, 1);  // Insert in the middle

    // Output all items after insertions
    for (int i = 0; i < float_list.size(); i++) {
        std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";
    }

    // Test 3: Remove an element from float
    std::cout << "test3 (remove an element from float):\n=====\n";
    float_list.remove(2); // Remove item at index 2 (value 2.1)
    std::cout << "After remove(2):\n";
    for (int i = 0; i < float_list.size(); i++) {
        std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";
    }

    // Test 4: Remove all occurrences of a value in float
    std::cout << "test4 (remove_all occurrences of value in float):\n=====\n";
    float_list.append(2.0f);
    float_list.append(1.8f);
    float_list.append(1.8f);  // Adding more 1.8 values

    unsigned int removedCount = float_list.remove_all(1.8f);
    std::cout << "\tRemoved " << removedCount << " occurrences of 1.8f\n";
    for (int i = 0; i < float_list.size(); i++) {
        std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";
    }
    std::cout << "\n";

    // Test 5: Test find method for float
    std::cout << "test5 (find method for float):\n=====\n";
    int index = float_list.find(4.2f);
    std::cout << "\tIndex of 4.2f: " << index << std::endl;

    // Test 6: Reserve method for float
    std::cout << "test6 (reserve capacity for float):\n=====\n";
    float_list.reserve(20);  // Reserve more space than needed
    std::cout << "\tAfter reserve(20), capacity=" << float_list.capacity() << std::endl;

    // Test 7: Test with Person object
    std::cout << "test7 (operations with Person objects):\n=====\n";

    ssuds::ArrayList<example::Person> person_list;
    example::Person p1("John","Newman", 1, 45), p2("Jane", "Whithers", 2, 30);

    person_list.append(p1);
    person_list.append(p2);

    // Output size and items
    std::cout << "\tsize=" << person_list.size() << std::endl;
    std::cout << "\titem0=" << person_list.at(0).get_first_name() << " " <<person_list.at(0).get_last_name()<< " ID# "<< person_list.at(0).get_id() << std::endl;
    std::cout << "\titem1=" << person_list.at(1).get_first_name() <<" "<< 
        person_list.at(1).get_last_name() << " ID#" << person_list.at(1).get_id() << std::endl;
    std::cout << '\n';

    // Insert more people into the list
    person_list.insert(example::Person("Alice","Robinson", 3, 22), 1);
    person_list.insert(example::Person("Bob", "Billiamson", 4, 27), 3);

    std::cout << "After inserts with Person objects:\n";
    for (int i = 0; i < person_list.size(); i++) {
        std::cout << "\titem" << i << "=" << person_list.at(i).get_first_name() << " "
            << person_list.at(i).get_last_name() 
            << ", " << person_list.at(i).get_id() << "\n";
    }
    std::cout << '\n';

    // Test remove on Person object
    person_list.remove(1);  // Remove second item (Alice)
    std::cout << "After remove(1) on Person object:\n";
    for (int i = 0; i < person_list.size(); i++) {
        std::cout << "\titem" << i << "=" << person_list.at(i).get_first_name() << " " 
            << person_list.at(i).get_last_name()<< " ID# " << person_list.at(i).get_id() << "\n";
    }
    std::cout << '\n';

    // Test find with Person object
    std::cout << "test8 (find method for Person):\n=====\n";
    int personIndex = person_list.find(p2); // Find "Bob"
    std::cout << "\tIndex of Bob: " << personIndex << std::endl;

    // Test reserve with Person object
    std::cout << "test9 (reserve capacity for Person):\n=====\n";
    person_list.reserve(10);  // Reserve more space for the list
    std::cout << "\tAfter reserve(10), capacity=" << person_list.capacity() << std::endl;
    return 0;
}


