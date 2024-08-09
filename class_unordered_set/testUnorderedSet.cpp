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
TEST(testModifier,clear){
    unordered_set<int> us{1, 2, 3, 4, 5};
    EXPECT_FALSE(us.empty());
    us.clear();
    EXPECT_TRUE(us.empty());
}

TEST(testModifier,insert){

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
