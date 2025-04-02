#include "gtest/gtest.h"
#include "array_list_utility.h"
// Test quicksort in ascending order.
TEST(ArrayListUtilityTests, QuickSortAscending) {
    ssuds::ArrayList<int> list = { 5, 3, 8, 1, 2 };
    int swaps = ssuds::quicksort(list, ssuds::SortType::ASCENDING);
    for (size_t i = 1; i < list.size(); i++) {
        EXPECT_LE(list[i - 1], list[i]);
    }
    EXPECT_GT(swaps, 0);
}

// Test quicksort in descending order.
TEST(ArrayListUtilityTests, QuickSortDescending) {
    ssuds::ArrayList<int> list = { 5, 3, 8, 1, 2 };
    int swaps = ssuds::quicksort(list, ssuds::SortType::DESCENDING);
    for (size_t i = 1; i < list.size(); i++) {
        EXPECT_GE(list[i - 1], list[i]);
    }
    EXPECT_GT(swaps, 0);
}

// Test binary search in ascending order (value found).
TEST(ArrayListUtilityTests, BinarySearchFoundAscending) {
    ssuds::ArrayList<int> list = { 1, 2, 3, 4, 5 };
    int index = ssuds::binary_search(list, ssuds::SortType::ASCENDING, 3);
    EXPECT_NE(index, -1);
    EXPECT_EQ(list[index], 3);
}

// Test binary search in ascending order (value not found).
TEST(ArrayListUtilityTests, BinarySearchNotFoundAscending) {
    ssuds::ArrayList<int> list = { 1, 2, 3, 4, 5 };
    int index = ssuds::binary_search(list, ssuds::SortType::ASCENDING, 6);
    EXPECT_EQ(index, -1);
}

// Test binary search in descending order (value found).
TEST(ArrayListUtilityTests, BinarySearchFoundDescending) {
    ssuds::ArrayList<int> list = { 5, 4, 3, 2, 1 };
    int index = ssuds::binary_search(list, ssuds::SortType::DESCENDING, 3);
    EXPECT_NE(index, -1);
    EXPECT_EQ(list[index], 3);
}

// Test binary search in descending order (value not found).
TEST(ArrayListUtilityTests, BinarySearchNotFoundDescending) {
    ssuds::ArrayList<int> list = { 5, 4, 3, 2, 1 };
    int index = ssuds::binary_search(list, ssuds::SortType::DESCENDING, 6);
    EXPECT_EQ(index, -1);
}

// Test bubble sort in ascending order.
TEST(ArrayListUtilityTests, BubbleSortAscending) {
    ssuds::ArrayList<int> list = { 10, 7, 8, 9, 1, 5 };
    int swaps = ssuds::bubble_sort(list, ssuds::SortType::ASCENDING);
    for (size_t i = 1; i < list.size(); i++) {
        EXPECT_LE(list[i - 1], list[i]);
    }
    EXPECT_GT(swaps, 0);
}

// Test bubble sort in descending order.
TEST(ArrayListUtilityTests, BubbleSortDescending) {
    ssuds::ArrayList<int> list = { 10, 7, 8, 9, 1, 5 };
    int swaps = ssuds::bubble_sort(list, ssuds::SortType::DESCENDING);
    for (size_t i = 1; i < list.size(); i++) {
        EXPECT_GE(list[i - 1], list[i]);
    }
    EXPECT_GT(swaps, 0);
}

// Test shuffle: verify that after shuffling, the list contains the same elements.
TEST(ArrayListUtilityTests, Shuffle) {
    ssuds::ArrayList<int> original = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    ssuds::ArrayList<int> list = original;
    ssuds::shuffle(list);

    // To test correctness, sort both lists and then compare.
    ssuds::quicksort(list, ssuds::SortType::ASCENDING);
    ssuds::quicksort(original, ssuds::SortType::ASCENDING);
    for (size_t i = 0; i < list.size(); i++) {
        EXPECT_EQ(list[i], original[i]);
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

