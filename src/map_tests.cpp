#include "Map.h"
#include <gtest/gtest.h>

TEST(MapTest, InsertAndAccess) {
    Map<std::string, int> m;
    EXPECT_EQ(m.size(), 0u);
    m["Alice"] = 10;
    EXPECT_TRUE(m.contains("Alice"));
    EXPECT_EQ(m["Alice"], 10);
}

TEST(MapTest, DefaultValueAndModify) {
    Map<std::string, int> m;
    int& ref = m["Bob"];
    EXPECT_TRUE(m.contains("Bob"));
    EXPECT_EQ(ref, 0);
    ref = 20;
    EXPECT_EQ(m["Bob"], 20);
}

TEST(MapTest, RemoveAndClear) {
    Map<std::string, int> m;
    m["Alice"] = 5;
    EXPECT_TRUE(m.remove("Alice"));
    EXPECT_FALSE(m.contains("Alice"));
    EXPECT_FALSE(m.remove("Alice"));
    m["X"] = 1;
    m["Y"] = 2;
    m.clear();
    EXPECT_EQ(m.size(), 0u);
}

TEST(MapTest, IteratorSum) {
    Map<std::string, int> m;
    m["A"] = 1;
    m["B"] = 2;
    m["C"] = 3;
    int sum = 0;
    for (auto p : m) sum += p.second;
    EXPECT_EQ(sum, 6);
}