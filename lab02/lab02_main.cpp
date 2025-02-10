#include <iostream>
#include "array_list.h"

int main() {
    // Basic test program (for floats)
    ssuds::ArrayList<float> float_list;
    std::cout << "Test 1 (Append and Size):\n====================\n";
    float_list.append(2.1f); // Append 2.1
    float_list.append(3.6f); // Append 3.6
    std::cout << "\tsize=" << float_list.size() << std::endl; // Expected: 2
    std::cout << "\titem0=" << float_list.at(0) << std::endl;  // Expected: 2.1
    std::cout << "\titem1=" << float_list.at(1) << std::endl;  // Expected: 3.6

    std::cout << "\nTest 2 (Insert at Index):\n====================\n";
    float_list.insert(1.8f, 0); // Insert at index 0
    float_list.insert(4.2f, 3); // Insert at index 3 (end of list)
    float_list.insert(2.0f, 1); // Insert at index 1
    for (int i = 0; i < float_list.size(); i++) {
        std::cout << "\titem" << i << "=" << float_list.at(i) << std::endl;
    }
    // Expected output: 
    // item0=1.8
    // item1=2.0
    // item2=2.1
    // item3=3.6
    // item4=4.2

    std::cout << "\nTest 3 (Find Method):\n====================\n";
    int index = float_list.find(2.0f); // Should return 1
    std::cout << "\tIndex of 2.0: " << index << std::endl; // Expected: 1
    index = float_list.find(5.0f); // Should return -1 (not found)
    std::cout << "\tIndex of 5.0: " << index << std::endl; // Expected: -1

    std::cout << "\nTest 4 (Remove Method):\n====================\n";
    float removed_item = float_list.remove(1); // Remove item at index 1
    std::cout << "\tRemoved item: " << removed_item << std::endl; // Expected: 2.0
    std::cout << "\tsize after removal: " << float_list.size() << std::endl; // Expected: 4

    std::cout << "\nTest 5 (Remove All Occurrences):\n====================\n";
    float_list.append(2.1f); // Add another 2.1 for testing remove_all
    float count = float_list.remove_all(2.1f); // Should remove 2.1 twice
    std::cout << "\tRemoved count for 2.1: " << count << std::endl; // Expected: 2
    std::cout << "\tsize after remove_all: " << float_list.size() << std::endl; // Expected: 3

    std::cout << "\nTest 6 (Out of Range Access):\n====================\n";
    try {
        std::cout << "\tAccessing item at index 10: " << float_list.at(10) << std::endl;
    }
    catch (...) {
        std::cout << "\tCaught out of range exception for index 10." << std::endl;
    }

    // Basic test program (for integers)
    ssuds::ArrayList<int> int_list;
    std::cout << "\nTest 7 (Append and Size for Integers):\n====================\n";
    int_list.append(5);
    int_list.append(10);
    std::cout << "\tsize=" << int_list.size() << std::endl; // Expected: 2
    std::cout << "\titem0=" << int_list.at(0) << std::endl; // Expected: 5
    std::cout << "\titem1=" << int_list.at(1) << std::endl; // Expected: 10

    std::cout << "\nTest 8 (Insert at Index for Integers):\n====================\n";
    int_list.insert(7, 0); // Insert 7 at index 0
    int_list.insert(2, 3); // Insert 2 at index 3 (end of list)
    for (int i = 0; i < int_list.size(); i++) {
        std::cout << "\titem" << i << "=" << int_list.at(i) << std::endl;
    }
    // Expected output: 
    // item0=7
    // item1=5
    // item2=10
    // item3=2

    std::cout << "\nTest 9 (Find Method for Integers):\n====================\n";
    index = int_list.find(10); // Should return 2
    std::cout << "\tIndex of 10: " << index << std::endl; // Expected: 2
    index = int_list.find(3); // Should return -1 (not found)
    std::cout << "\tIndex of 3: " << index << std::endl; // Expected: -1

    std::cout << "\nTest 10 (Remove Method for Integers):\n====================\n";
    removed_item = int_list.remove(0); // Remove item at index 0 (7)
    std::cout << "\tRemoved item: " << removed_item << std::endl; // Expected: 7
    std::cout << "\tsize after removal: " << int_list.size() << std::endl; // Expected: 3

    // Test the reserve method
    std::cout << "\nTest 11 (Reserve Method):\n====================\n";
    int_list.reserve(10); // Should not change size, but capacity should be 10
    std::cout << "\tCapacity after reserve: " << int_list.capacity() << std::endl; // Expected: 10



    return 0;
}
