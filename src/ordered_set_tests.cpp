#include "gtest/gtest.h"
#include "ordered_set.h"

TEST(OrderedSetBasic, InsertAndContains) {
    OrderedSet<int> s;
    EXPECT_FALSE(s.contains(5));
    s.insert(5);
    EXPECT_TRUE(s.contains(5));
    s.insert(3);
    s.insert(7);
    EXPECT_TRUE(s.contains(3));
    EXPECT_TRUE(s.contains(7));
    EXPECT_EQ(s.size(), 3);
}

TEST(TraversalAndHeight, Orders) {
    OrderedSet<int> s;
    for (int v : {4, 2, 6, 1, 3, 5, 7}) s.insert(v);
    auto in = s.traversal(OrderedSet<int>::Order::IN);
    EXPECT_EQ(in, std::vector<int>({ 1,2,3,4,5,6,7 }));
    auto pre = s.traversal(OrderedSet<int>::Order::PRE);
    EXPECT_EQ(pre.front(), 4);
    EXPECT_EQ(s.get_height(), 3);
}

TEST(RebalanceAndParent, Checks) {
    OrderedSet<int> s;
    for (int v : {1, 2, 3, 4, 5, 6, 7}) s.insert(v);
    EXPECT_EQ(s.get_height(), 7);
    s.rebalance();
    EXPECT_LE(s.get_height(), 3);
    auto p = s.get_parent(4);
    EXPECT_FALSE(!p);
}

TEST(EraseAndOperators, Checks) {
    OrderedSet<int> a;
    for (int v : {1, 2, 3, 4, 5}) a.insert(v);
    EXPECT_TRUE(a.erase(3));
    EXPECT_FALSE(a.contains(3));
    EXPECT_FALSE(a.erase(10));
    OrderedSet<int> b;
    b.insert(4); b.insert(5); b.insert(6);
    auto uni = a + b;
    EXPECT_TRUE(uni.contains(2)); EXPECT_TRUE(uni.contains(6));
    auto inter = a * b;
    EXPECT_TRUE(inter.contains(4)); EXPECT_FALSE(inter.contains(2));
    auto diff = a - b;
    EXPECT_TRUE(diff.contains(2)); EXPECT_FALSE(diff.contains(4));
}

TEST(IteratorAndString, Checks) {
    OrderedSet<int> s;
    for (int v : {10, 5, 15, 3, 7}) s.insert(v);
    std::vector<int> vals;
    for (auto it = s.begin(); it != s.end(); ++it) vals.push_back(*it);
    EXPECT_EQ(vals, s.traversal(OrderedSet<int>::Order::IN));
    auto str = s.tree_string();
    EXPECT_NE(str.size(), 0);
}