#pragma once

#include "array_list.h"
#include <random>
#include <functional>
#include <algorithm>

namespace ssuds {
    enum class SortType { ASCENDING, DESCENDING };
    // Quicksort: recursively sorts the ArrayList in-place and returns the number of swaps.
    template <typename T>
    int quicksort(ArrayList<T>& alist, SortType order) {
        int swapCount = 0;

        auto partition = [&](int low, int high) -> int {
            T pivot = alist[high];
            int i = low - 1;
            for (int j = low; j < high; j++) {
                bool condition = (order == SortType::ASCENDING) ? (alist[j] < pivot) : (alist[j] > pivot);
                if (condition) {
                    i++;
                    std::swap(alist[i], alist[j]);
                    swapCount++;
                }
            }
            std::swap(alist[i + 1], alist[high]);
            swapCount++;
            return i + 1;
            };

        // Recursive lambda for quicksort.
        std::function<void(int, int)> quickSortRecursive = [&](int low, int high) {
            if (low < high) {
                int pi = partition(low, high);
                quickSortRecursive(low, pi - 1);
                quickSortRecursive(pi + 1, high);
            }
            };

        if (alist.size() > 0)
            quickSortRecursive(0, alist.size() - 1);

        return swapCount;
    }

    // Binary search: returns the index of the value (or -1 if not found). Assumes the list is sorted.
    template <typename T>
    int binary_search(const ArrayList<T>& alist, SortType order, const T& value) {
        int low = 0;
        int high = alist.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (alist[mid] == value)
                return mid;
            if (order == SortType::ASCENDING) {
                if (alist[mid] < value)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            else { // DESCENDING order
                if (alist[mid] > value)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return -1;
    }

    // Bubble sort: sorts the list using the bubble sort algorithm and returns the number of swaps.
    template <typename T>
    int bubble_sort(ArrayList<T>& alist, SortType order) {
        int swapCount = 0;
        bool swapped;
        for (unsigned int i = 0; i < alist.size(); i++) {
            swapped = false;
            for (unsigned int j = 0; j < alist.size() - i - 1; j++) {
                bool condition = (order == SortType::ASCENDING) ? (alist[j] > alist[j + 1]) : (alist[j] < alist[j + 1]);
                if (condition) {
                    std::swap(alist[j], alist[j + 1]);
                    swapCount++;
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
        return swapCount;
    }

    // Shuffle: re-arranges the ArrayList using the Fisher–Yates algorithm.
    template <typename T>
    void shuffle(ArrayList<T>& alist) {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = alist.size() - 1; i > 0; i--) {
            std::uniform_int_distribution<> dis(0, i);
            int j = dis(gen);
            std::swap(alist[i], alist[j]);
        }
    }

} // namespace ssuds
