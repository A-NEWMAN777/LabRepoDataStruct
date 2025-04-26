#include "gtest/gtest.h"
#include "linked_list.h"
#include <initializer_list>

using List = LinkedList<int>;

TEST(LinkedListTest, AppendPrependAndSize) {
    List l;
    EXPECT_EQ(l.size(), 0u);
    l.append(1);
    l.append(2);
    l.prepend(0);
    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l[0], 0);
    EXPECT_EQ(l[1], 1);
    EXPECT_EQ(l[2], 2);
}

TEST(LinkedListTest, InsertAndAt) {
    List l = { 1,2,4,5 };
    l.insert(2, 3);
    EXPECT_EQ(l.size(), 5u);
    for (int i = 0; i < 5; ++i) EXPECT_EQ(l.at(i), i + 1);
}

TEST(LinkedListTest, FindAndRemove) {
    List l = { 1,2,3,2,4 };
    EXPECT_EQ(l.find(2), 1u);
    EXPECT_TRUE(l.remove(2));
    EXPECT_EQ(l.size(), 4u);
    EXPECT_EQ(l.find(2), 2u);
    l.remove_all(2);
    EXPECT_EQ(l.find(2), l.size());
}

TEST(LinkedListTest, CopyAndAssignment) {
    List a = { 1,2,3 };
    List b = a;
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b[1], 2);
    List c;
    c = a;
    EXPECT_EQ(c.size(), 3u);
}

TEST(LinkedListTest, MoveConstructorAndMoveAssignment) {
    List a = { 5,6,7 };
    List b = std::move(a);
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(a.size(), 0u);
    List c;
    c = std::move(b);
    EXPECT_EQ(c.size(), 3u);
    EXPECT_EQ(b.size(), 0u);
}

TEST(LinkedListTest, IteratorTraversal) {
    List l = { 10,20,30 };
    int sum = 0;
    for (auto it = l.begin(); it != l.end(); ++it) sum += *it;
    EXPECT_EQ(sum, 60);
    auto it = l.end();
    --it;
    EXPECT_EQ(*it, 30);
    --it;
    EXPECT_EQ(*it, 20);
}

TEST(LinkedListTest, InitializerList) {
    List l{ 3,1,4,1,5 };
    EXPECT_EQ(l.size(), 5u);
    EXPECT_EQ(l[2], 4);
}

TEST(LinkedListTest, ClearAndDestructor) {
    List* lp = new List{ 1,2,3 };
    EXPECT_EQ(lp->size(), 3u);
    delete lp; 
}
