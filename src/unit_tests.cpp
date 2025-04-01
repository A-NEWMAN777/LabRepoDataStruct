

#include <gtest/gtest.h>
#include <iostream>

    TEST(ArrayListTest, BasicTest) {
        ssuds::ArrayList<float> float_list;

        float_list.append(2.3f);
        float_list.append(2.6f);

        EXPECT_EQ(float_list.size(), 2);
        EXPECT_FLOAT_EQ(float_list.at(0), 2.3f);
        EXPECT_FLOAT_EQ(float_list.at(1), 2.6f);

        float_list.at(0) -= 0.1f;
        float_list.at(1)++;

        EXPECT_FLOAT_EQ(float_list.at(0), 2.2f);
        EXPECT_FLOAT_EQ(float_list.at(1), 3.6f);
    }

    TEST(ArrayListTest, InsertTest) {
        ssuds::ArrayList<float> float_list;

        float_list.append(2.3f);
        float_list.append(2.6f);

        float_list.insert(1.8f, 0);
        float_list.insert(4.2f, 3);
        float_list.insert(2.2f, 1);

        EXPECT_FLOAT_EQ(float_list.at(0), 1.8f);
        EXPECT_FLOAT_EQ(float_list.at(1), 2.2f);
        EXPECT_FLOAT_EQ(float_list.at(2), 2.3f);
        EXPECT_FLOAT_EQ(float_list.at(3), 2.6f);
        EXPECT_FLOAT_EQ(float_list.at(4), 4.2f);
    }

    TEST(ArrayListTest, GrowTest) {
        ssuds::ArrayList<float> float_list;

        float_list.append(2.3f);
        float_list.append(2.6f);
        float_list.append(1.8f);
        float_list.append(4.2f);
        float_list.append(2.2f);

        EXPECT_EQ(float_list.size(), 5);
        EXPECT_EQ(float_list.capacity(), 5);

        float_list.append(5.6f);
        float_list.append(2.2f);

        EXPECT_EQ(float_list.size(), 7);
        EXPECT_GE(float_list.capacity(), 7);
    }

    TEST(ArrayListTest, FindAllTest) {
        ssuds::ArrayList<float> float_list;

        float_list.append(1.8f);
        float_list.append(2.2f);
        float_list.append(2.2f);
        float_list.append(3.6f);
        float_list.append(4.2f);
        float_list.append(5.6f);
        float_list.append(2.2f);

        int index = float_list.find(2.2f, 0);
        EXPECT_EQ(index, 1);
        index = float_list.find(2.2f, index + 1);
        EXPECT_EQ(index, 2);
        index = float_list.find(2.2f, index + 1);
        EXPECT_EQ(index, 6);
    }

    TEST(ArrayListTest, RemoveAllTest) {
        ssuds::ArrayList<float> float_list;

        float_list.append(1.8f);
        float_list.append(2.2f);
        float_list.append(2.2f);
        float_list.append(3.6f);
        float_list.append(4.2f);
        float_list.append(5.6f);
        float_list.append(2.2f);

        EXPECT_EQ(float_list.size(), 7);
        EXPECT_EQ(float_list.capacity(), 7);

        int removed = float_list.remove_all(2.2f);
        EXPECT_EQ(removed, 3);
        EXPECT_EQ(float_list.size(), 4);
        EXPECT_EQ(float_list.capacity(), 5);

        EXPECT_FLOAT_EQ(float_list.at(0), 1.8f);
        EXPECT_FLOAT_EQ(float_list.at(1), 3.6f);
        EXPECT_FLOAT_EQ(float_list.at(2), 4.2f);
        EXPECT_FLOAT_EQ(float_list.at(3), 5.6f);
    }

    TEST(ArrayListTest, ReserveAndPersonsTest) {
        ssuds::ArrayList<example::Person> plist;

        EXPECT_EQ(plist.size(), 0);
        EXPECT_EQ(plist.capacity(), 5);

        plist.reserve(26);
        EXPECT_EQ(plist.capacity(), 26);

        char temp_string[4] = { 0, 0, 0, 0 };

        for (unsigned int i = 0; i < 26; i++) {
            temp_string[0] = 'A' + i;
            temp_string[1] = temp_string[2] = 'a' + i;
            example::Person p(std::string(temp_string), "Smith", 100 + i, i + 0.5f);
            plist.append(p);
            plist.at(plist.size() - 1).set_hours_worked(i * 2);
        }

        plist.insert(example::Person("---", "###", 5000, 0.0f), 1);

        EXPECT_EQ(plist.size(), 26);
        EXPECT_EQ(plist.capacity(), 26);

        std::cout << std::setprecision(2) << std::fixed;
        for (unsigned int i = 0; i < plist.size(); i++) {
            example::Person p = plist.at(i);
            std::cout << "\t" << p.get_name(false) << " ";
            std::cout << " $" << p.get_salary() << "\n";
        }
        TEST(ArrayListTest, AppendTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
                EXPECT_EQ(list.size(), i);
                EXPECT_GE(list.capacity(), i);  // Ensure capacity is at least size
            }
        }

        TEST(ArrayListTest, AccessTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
            }

            for (unsigned int i = 0; i < list.size(); ++i) {
                EXPECT_EQ(list.at(i), i + 1);
            }
        }

        TEST(ArrayListTest, InsertTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
            }

            list.insert(100, 5);

            EXPECT_EQ(list.size(), 11);
            EXPECT_EQ(list.at(5), 100);  // Ensure the value is inserted at the correct index
        }

        TEST(ArrayListTest, FindTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
            }

            int index = list.find(100);
            EXPECT_EQ(index, -1);  // Should not find element 100

            index = list.find(5);
            EXPECT_EQ(index, 4);  // Element 5 should be found at index 4 (0-based index)
        }

        TEST(ArrayListTest, RemoveAllTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
            }

            list.insert(100, 5);  // Insert element 100 at index 5
            list.remove_all(100);

            EXPECT_EQ(list.size(), 10);  // Should have removed 1 element
            EXPECT_EQ(list.capacity(), 10);  // Ensure capacity is unchanged
            EXPECT_EQ(list.find(100), -1);  // Element 100 should no longer be present
        }

        TEST(ArrayListTest, IteratorTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
            }

            std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it) {
                EXPECT_EQ(*it, expected[idx++]);
            }
        }

        TEST(ArrayListTest, ReserveTest) {
            ArrayList<int> list;

            list.reserve(20);

            EXPECT_GE(list.capacity(), 20);  // Reserved capacity should be at least 20
        }

        TEST(ArrayListTest, ClearTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
            }

            list.clear();

            EXPECT_EQ(list.size(), 0);  // Size should be 0 after clearing
            EXPECT_GE(list.capacity(), 10);  // Capacity should remain intact or shrink
        }

        TEST(ArrayListTest, ShrinkTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 15; ++i) {
                list.append(i);
            }

            list.remove_all(1);  // Remove all occurrences of 1

            EXPECT_EQ(list.size(), 14);  // Should have 14 elements left
            EXPECT_LT(list.capacity(), 15);  // Capacity should shrink after removal
        }

        TEST(ArrayListTest, OutOfRangeTest) {
            ArrayList<int> list;

            for (int i = 1; i <= 10; ++i) {
                list.append(i);
            }

            EXPECT_THROW(list.at(100), std::out_of_range);  // Accessing out of bounds should throw exception
        }

        int main(int argc, char** argv) {
            ::testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
