#include <iostream>
#include <fstream>
#include <chrono>
#include "array_list.h"
#include "array_list_utility.h"

int main() {
    using namespace std::chrono;

    // Open CSV file for writing timing data.
    std::ofstream file("../../data/timing_data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return 1;
    }

    // Write header for CSV file.
    file << "Size,CreateTime(ns),ShuffleTime(ns),CopyTime(ns),ReserveTime(ns),"
        << "QuickSortTime(ns),BubbleSortTime(ns),BinarySearchTime(ns),LinearSearchTime(ns)\n";

    // Loop from 1000 to 1,000,000 in steps of 5000.
    for (size_t n = 1000; n <= 1000000; n += 5000) {
        // Operation i: Create the ArrayList with values: 0.5, 1.5, 2.5, ...
        auto start = high_resolution_clock::now();
        ssuds::ArrayList<float> list;
        for (size_t i = 0; i < n; ++i) {
            list.append(i + 0.5f);
        }
        auto end = high_resolution_clock::now();
        auto createTime = duration_cast<nanoseconds>(end - start).count();

        // Operation ii: Shuffle the ArrayList.
        start = high_resolution_clock::now();
        ssuds::shuffle(list);
        end = high_resolution_clock::now();
        auto shuffleTime = duration_cast<nanoseconds>(end - start).count();

        // Operation iii: Make a copy of the ArrayList.
        start = high_resolution_clock::now();
        ssuds::ArrayList<float> copyList(list);
        end = high_resolution_clock::now();
        auto copyTime = duration_cast<nanoseconds>(end - start).count();

        // Operation iv: Reserve 1000 elements from the unsorted (shuffled) list.
        start = high_resolution_clock::now();
        ssuds::ArrayList<float> reserved;
        // (Assuming the list has at least 1000 elements, which is true here.)
        for (size_t i = 0; i < 1000; ++i) {
            reserved.append(list[i]);
        }
        end = high_resolution_clock::now();
        auto reserveTime = duration_cast<nanoseconds>(end - start).count();

        // Operation v: Sort the original list using quicksort (ascending).
        start = high_resolution_clock::now();
        int quickSwaps = ssuds::quicksort(list, ssuds::SortType::ASCENDING);
        end = high_resolution_clock::now();
        auto quicksortTime = duration_cast<nanoseconds>(end - start).count();

        // Operation vi: Sort the copy using bubble sort (ascending).
        start = high_resolution_clock::now();
        int bubbleSwaps = ssuds::bubble_sort(copyList, ssuds::SortType::ASCENDING);
        end = high_resolution_clock::now();
        auto bubbleSortTime = duration_cast<nanoseconds>(end - start).count();

        // Operation vii: Find each reserved element using binary search.
        start = high_resolution_clock::now();
        for (size_t i = 0; i < reserved.size(); ++i) {
            int index = ssuds::binary_search(list, ssuds::SortType::ASCENDING, reserved[i]);
            // Optionally, check that index != -1.
        }
        end = high_resolution_clock::now();
        auto binarySearchTime = duration_cast<nanoseconds>(end - start).count();

        // Operation viii: Find each reserved element using linear search.
        start = high_resolution_clock::now();
        for (size_t i = 0; i < reserved.size(); ++i) {
            int foundIndex = -1;
            for (size_t j = 0; j < list.size(); ++j) {
                if (list[j] == reserved[i]) {
                    foundIndex = j;
                    break;
                }
            }
        }
        end = high_resolution_clock::now();
        auto linearSearchTime = duration_cast<nanoseconds>(end - start).count();

        // Output the timing data for this test size.
        file << n << ","
            << createTime << ","
            << shuffleTime << ","
            << copyTime << ","
            << reserveTime << ","
            << quicksortTime << ","
            << bubbleSortTime << ","
            << binarySearchTime << ","
            << linearSearchTime << "\n";

        // Optional: output progress to console.
        std::cout << "Completed test for size " << n << std::endl;
    }

    file.close();
    std::cout << "Timing data written to timing_data.csv" << std::endl;
    return 0;
}
