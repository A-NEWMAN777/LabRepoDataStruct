#include <iostream>
#include <stdexcept>
#include <string>
#include "array_list.h"  // Include your header file (ArrayList definition)

using namespace ssuds;

int main() {
    try {
        // Creating an ArrayList of integers
        ArrayList<int> list;

        // Test 1: Append elements
        std::cout << "Test 1: Append elements" << std::endl;
        for (int i = 1; i <= 10; ++i) {
            list.append(i);
            std::cout << "Appended: " << i << ", Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;
        }

        // Test 2: Access elements using 'at' function
        std::cout << "\nTest 2: Access elements using 'at' function" << std::endl;
        for (unsigned int i = 0; i < list.size(); ++i) {
            std::cout << "Element at index " << i << ": " << list.at(i) << std::endl;
        }

        // Test 3: Insert element at a specific position
        std::cout << "\nTest 3: Insert element at index 5" << std::endl;
        list.insert(100, 5);
        std::cout << "Inserted 100 at index 5, Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;
        for (unsigned int i = 0; i < list.size(); ++i) {
            std::cout << "Element at index " << i << ": " << list.at(i) << std::endl;
        }

        // Test 4: Find element in the list
        std::cout << "\nTest 4: Find element" << std::endl;
        int index = list.find(100);
        if (index != -1) {
            std::cout << "Element 100 found at index: " << index << std::endl;
        }
        else {
            std::cout << "Element 100 not found!" << std::endl;
        }

        // Test 5: Remove all occurrences of an element
        std::cout << "\nTest 5: Remove all occurrences of element 100" << std::endl;
        list.remove_all(100);
        std::cout << "After removal of 100, Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;
        for (unsigned int i = 0; i < list.size(); ++i) {
            std::cout << "Element at index " << i << ": " << list.at(i) << std::endl;
        }

        // Test 6: Iterate over the list using an iterator
        std::cout << "\nTest 6: Iterate using an iterator" << std::endl;
        std::cout << "List elements: ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // Test 7: Reserve capacity and ensure list resizes
        std::cout << "\nTest 7: Reserve capacity" << std::endl;
        list.reserve(20);
        std::cout << "Reserved new capacity: " << list.capacity() << std::endl;

        // Test 8: Clear the list
        std::cout << "\nTest 8: Clear the list" << std::endl;
        list.clear();
        std::cout << "After clear, Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;

        // Test 9: Shrinking the list when necessary
        std::cout << "\nTest 9: Shrink the list" << std::endl;
        for (int i = 1; i <= 15; ++i) {
            list.append(i);
        }
        std::cout << "After appending 15 elements, Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;
        list.remove_all(1);  // Removing a few elements to potentially shrink the capacity
        std::cout << "After removing all occurrences of 1, Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;

        // Test 10: Edge case for out-of-range access
        std::cout << "\nTest 10: Access out of range" << std::endl;
        try {
            std::cout << "Accessing out-of-bounds element: " << list.at(100) << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
