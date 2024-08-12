// testUnorderedSet.cpp
#include <gtest/gtest.h>
#include "MiniUnorderedSet.h"
#include <vector>

//测试构造函数
TEST(testConstructor, defaultConstructor)
{
    //默认构造函数
    unordered_set<int> us;
    EXPECT_TRUE(us.empty());
}

TEST(testConstructor, inputItConstructor)
{
    vector<int> v{1, 2, 3};
    unordered_set<int> us(v.begin(), v.end());
    EXPECT_EQ(us.size(), 3);
}

TEST(testConstructor, CopyConstructor)
{
    vector<int> v{1, 2, 3};
    unordered_set<int> us(v.begin(), v.end());
    unordered_set<int> us2(us);
    EXPECT_EQ(us2.size(), 3);
}

TEST(testConstructor, moveConstructor)
{
    vector<int> v{1, 2, 3};
    unordered_set<int> us(v.begin(), v.end());
    unordered_set<int> us2(std::move(us));
    EXPECT_EQ(us2.size(), 3);
    EXPECT_EQ(us.size(), 0);
}

TEST(testConstructor, InitConstructor)
{
    unordered_set<int> us{1, 2, 3};
    EXPECT_EQ(us.size(), 3);
}

//测试operator=重载
TEST(testOper, oper)
{
    unordered_set<int> us{1, 2, 3};
    unordered_set<int> us2 = us;
    EXPECT_EQ(us2.size(), us.size());
}

//=========迭代器模块==========
TEST(testIterator, Iterator)
{
    unordered_set<int> us{1, 2, 3, 4, 5};
    unordered_set<int>::iterator it1 = us.begin();
    // operator*
    EXPECT_EQ(*it1, 1);
    // operator++
    EXPECT_EQ(*(++it1), 2);
    // operator++(int)
    EXPECT_EQ(*(it1++), 2);
    EXPECT_EQ(*it1, 3);
    // iterator operator =
    auto it2 = it1;
    EXPECT_TRUE(it1 == it2);
    unordered_set<int>::const_iterator cit(it1);
    EXPECT_TRUE(cit == it1);
}

TEST(testIterator, constIterator)
{
    unordered_set<int> us{1, 2, 3, 4, 5};
    unordered_set<int>::const_iterator it1 = us.begin();
    // operator*
    EXPECT_EQ(*it1, 1);
    // operator++
    EXPECT_EQ(*(++it1), 2);
    // operator++(int)
    EXPECT_EQ(*(it1++), 2);
    EXPECT_EQ(*it1, 3);
    // iterator operator =
    auto it2 = it1;
    EXPECT_TRUE(it1 == it2);
}

TEST(testIterator, localIterator) {}

TEST(testIterator, constlocalIterator) {}

//修改器模块
TEST(testModifier, clear)
{
    unordered_set<int> us{1, 2, 3, 4, 5};
    EXPECT_FALSE(us.empty());
    us.clear();
    EXPECT_TRUE(us.empty());
}

TEST(testModifier, insert)
{
    unordered_set<int> us{1, 2, 3, 4, 5};
    us.insert(6);
    EXPECT_TRUE(us.find(6) != us.end());
    EXPECT_EQ(us.size(), 6);
    vector<int> v{7, 8, 9};
    us.insert(v.begin(), v.end());
    EXPECT_EQ(us.size(), 9);
    us.insert({10, 11, 12});
    EXPECT_EQ(us.size(), 12);
}

TEST(testModifier, erase)
{
    unordered_set<int> us{1, 2, 3, 4, 5};
    us.erase(us.begin());
    EXPECT_EQ(us.size(), 4);
    us.erase(4);
    EXPECT_EQ(us.size(), 3);
    us.erase(us.begin(), us.end());
    EXPECT_TRUE(us.empty());
    us.insert(3);
    EXPECT_EQ(us.size(), 1);
    unordered_set<int>::const_iterator cit = us.begin();
    us.erase(cit);
    EXPECT_TRUE(us.empty());
}

TEST(testModifier, swap)
{
    unordered_set<int> us1{1, 2, 3};
    unordered_set<int> us2{6, 7, 8, 9, 10};
    us1.swap(us2);
    EXPECT_EQ(us1.size(), 5);
    EXPECT_EQ(us2.size(), 3);
}

TEST(testLookup, count)
{
    unordered_set<int> us{1, 2, 3, 4, 5};
    EXPECT_EQ(us.count(1), 1);
    EXPECT_EQ(us.count(9), 0);
}

TEST(testLookup, find)
{
    unordered_set<int> us1{1, 2, 3, 4, 5};
    auto it1 = us1.find(1);
    EXPECT_EQ(*it1, 1);
    const unordered_set<int> us2{2, 3, 4, 5, 6};
    auto it2 = us2.find(5);
    EXPECT_EQ(*it2, 5);
}

TEST(testNomenberFunc, equal_Nequal)
{
    unordered_set<int> us1{1, 2, 3, 4, 5};
    unordered_set<int> us2{1, 2, 3, 4, 5};
    unordered_set<int> us3{1, 2, 3};
    unordered_set<int> us4{1, 2, 3, 4, 6};
    unordered_set<int> us5{1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(us1 == us2);
    EXPECT_FALSE(us1 != us2);
    EXPECT_TRUE(us3 != us1);
    EXPECT_FALSE(us1 == us3);
    EXPECT_TRUE(us1 != us4);
    EXPECT_FALSE(us1 == us5);
}

TEST(testNomenberFunc, swap)
{
    unordered_set<int> us1{1, 2, 3};
    unordered_set<int> us2{6, 7, 8, 9, 10};
    swap(us1, us2);
    EXPECT_EQ(us1.size(), 5);
    EXPECT_EQ(us2.size(), 3);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
