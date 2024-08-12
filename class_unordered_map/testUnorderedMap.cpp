// testUnorderMap.cpp
#include <gtest/gtest.h>
#include "MiniUnorderedMap.h"
#include "MiniMap.h"

//测试构造函数
TEST(testConstructor, defaultConstructor)
{
    //默认构造函数
    unordered_map<char, int> us;
    EXPECT_TRUE(us.empty());
}

TEST(testConstructor, inputItConstructor)
{
    map<char, int> v{{'a', 1}, {'b', 2}, {'c', 3}};
    unordered_map<char, int> us(v.begin(), v.end());
    EXPECT_EQ(us.size(), 3);
}

TEST(testConstructor, CopyConstructor)
{
    map<char, int> v{{'a', 1}, {'b', 2}, {'c', 3}};
    unordered_map<char, int> us(v.begin(), v.end());
    unordered_map<char, int> us2(us);
    EXPECT_EQ(us2.size(), 3);
}

TEST(testConstructor, moveConstructor)
{
    map<char, int> v{{'a', 1}, {'b', 2}, {'c', 3}};
    unordered_map<char, int> us(v.begin(), v.end());
    unordered_map<char, int> us2(std::move(us));
    EXPECT_EQ(us2.size(), 3);
    EXPECT_EQ(us.size(), 0);
}

TEST(testConstructor, InitConstructor)
{
    unordered_map<char, int> us{{'a', 1}, {'b', 2}, {'c', 3}};
    EXPECT_EQ(us.size(), 3);
}

//测试operator=重载
TEST(testOper, oper)
{
    unordered_map<char, int> us{{'a', 1}, {'b', 2}, {'c', 3}};
    unordered_map<char, int> us2 = us;
    EXPECT_EQ(us2.size(), us.size());
}

//=========迭代器模块==========
TEST(testIterator, Iterator)
{
    unordered_map<char, int> us{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    unordered_map<char, int>::iterator it1 = us.begin();
    // operator*
    EXPECT_EQ(it1->second, 4);
    // operator++
    EXPECT_EQ((++it1)->second, 5);
    // operator++(int)
    EXPECT_EQ((it1++)->second, 5);
    EXPECT_EQ(it1->second, 1);
    // iterator operator =
    auto it2 = it1;
    EXPECT_TRUE(it1 == it2);
    unordered_map<char, int>::const_iterator cit(it1);
    EXPECT_TRUE(cit == it1);
}

TEST(testIterator, constIterator)
{
    unordered_map<char, int> us{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    unordered_map<char, int>::const_iterator it1 = us.begin();
    // operator*
    EXPECT_EQ(it1->second, 4);
    // operator++
    EXPECT_EQ((++it1)->second, 5);
    // operator++(int)
    EXPECT_EQ((it1++)->second, 5);
    EXPECT_EQ(it1->second, 1);
    // iterator operator =
    auto it2 = it1;
    EXPECT_TRUE(it1 == it2);
}

TEST(testIterator, localIterator) {}

TEST(testIterator, constlocalIterator) {}

//修改器模块
TEST(testModifier, clear)
{
    unordered_map<char, int> us{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    EXPECT_FALSE(us.empty());
    us.clear();
    EXPECT_TRUE(us.empty());
}

TEST(testModifier, insert)
{
    unordered_map<char, int> us{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    us.insert(std::make_pair('f', 6));
    EXPECT_TRUE(us.find('f') != us.end());
    EXPECT_EQ(us.size(), 6);
    map<char, int> v{{'g', 7}, {'h', 8}, {'i', 9}};
    us.insert(v.begin(), v.end());
    EXPECT_EQ(us.size(), 9);
    us.insert({{'j', 10}, {'k', 11}, {'l', 12}});
    EXPECT_EQ(us.size(), 12);
}

TEST(testModifier, erase)
{
    unordered_map<char, int> us{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    us.erase(us.begin());
    EXPECT_EQ(us.size(), 4);
    us.erase('a');
    EXPECT_EQ(us.size(), 3);
    us.erase(us.begin(), us.end());
    EXPECT_TRUE(us.empty());
    us.insert({'c', 3});
    EXPECT_EQ(us.size(), 1);
    unordered_map<char, int>::const_iterator cit = us.begin();
    us.erase(cit);
    EXPECT_TRUE(us.empty());
}

TEST(testModifier, swap)
{
    unordered_map<char, int> us1{{'a', 1}, {'b', 2}, {'c', 3}};
    unordered_map<char, int> us2{
            {'f', 6}, {'g', 7}, {'h', 8}, {'i', 9}, {'j', 10}};
    us1.swap(us2);
    EXPECT_EQ(us1.size(), 5);
    EXPECT_EQ(us2.size(), 3);
}

TEST(testLookup, count)
{
    unordered_map<char, int> us{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    EXPECT_EQ(us.count('a'), 1);
    EXPECT_EQ(us.count('z'), 0);
}

TEST(testLookup, find)
{
    unordered_map<char, int> us1{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    auto it1 = us1.find('a');
    EXPECT_EQ(it1->second, 1);
    const unordered_map<char, int> us2{
            {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}};
    auto it2 = us2.find('e');
    EXPECT_EQ(it2->second, 5);
}

TEST(testNomenberFunc, equal_Nequal)
{
    unordered_map<char, int> us1{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    unordered_map<char, int> us2{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    unordered_map<char, int> us3{{'a', 1}, {'b', 2}, {'c', 3}};
    unordered_map<char, int> us4{
            {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'f', 6}};
    unordered_map<char, int> us5{{'a', 1}, {'b', 2}, {'c', 3},
                                 {'d', 4}, {'e', 5}, {'f', 6}};
    EXPECT_TRUE(us1 == us2);
    EXPECT_FALSE(us1 != us2);
    EXPECT_TRUE(us3 != us1);
    EXPECT_FALSE(us1 == us3);
    EXPECT_TRUE(us1 != us4);
    EXPECT_FALSE(us1 == us5);
}

TEST(testNomenberFunc, swap)
{
    unordered_map<char, int> us1{{'a', 1}, {'b', 2}, {'c', 3}};
    unordered_map<char, int> us2{
            {'f', 6}, {'g', 7}, {'h', 8}, {'i', 9}, {'j', 10}};
    swap(us1, us2);
    EXPECT_EQ(us1.size(), 5);
    EXPECT_EQ(us2.size(), 3);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
