// testVector.cpp
#include <gtest/gtest.h>
#include "MiniVector.h"

//构造函数模块
TEST(testConstructor, Constructor)
{
    vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
    vector<int> v2(5, 2);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2[0], 2);
    vector<int> v3{1, 2, 3, 4, 5};
    EXPECT_EQ(v3.size(), 5);
    EXPECT_EQ(v3[1], 2);
    vector<int> v4(v3);
    EXPECT_EQ(v4.size(), 5);
    EXPECT_EQ(v4[1], 2);
    vector<int> v5(std::move(v4));
    EXPECT_EQ(v5.size(), 5);
    EXPECT_TRUE(v4.empty());
}

//迭代器模块
TEST(testIterator, Iterator)
{
    vector<int> v{1, 2, 3, 4, 5};
    auto it = v.begin();
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*(++it), 2);
    EXPECT_EQ(*(it++), 2);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*(it + 2), 5);
    EXPECT_EQ(*(--it), 2);
    EXPECT_EQ(*(it--), 2);
    EXPECT_EQ(*it, 1);
    it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1);
    it += 2;
    EXPECT_EQ(*it, 5);
    it -= 2;
    EXPECT_EQ(*it, 3);
    auto it2(it);
    EXPECT_TRUE(it == it2);
    it2 += 2;
    EXPECT_EQ(it2 - it, 2);
    EXPECT_FALSE(it == it2);
}

TEST(testIterator, constIterator)
{
    const vector<int> v{1, 2, 3, 4, 5};
    vector<int>::const_iterator it = v.begin();
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*(++it), 2);
    EXPECT_EQ(*(it++), 2);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*(it + 2), 5);
    EXPECT_EQ(*(--it), 2);
    EXPECT_EQ(*(it--), 2);
    EXPECT_EQ(*it, 1);
    it += 2;
    EXPECT_EQ(*(it - 2), 1);
    it += 2;
    EXPECT_EQ(*it, 5);
    it -= 2;
    EXPECT_EQ(*it, 3);
    auto it2(it);
    EXPECT_TRUE(it == it2);
    it2 += 2;
    EXPECT_EQ(it2 - it, 2);
    EXPECT_FALSE(it == it2);
}

TEST(testIterator, reverseIterator)
{
    vector<int> v{1, 2, 3, 4, 5};
    vector<int>::reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(*(++it), 4);
    EXPECT_EQ(*(it++), 4);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*(it + 2), 1);
    EXPECT_EQ(*(--it), 4);
    EXPECT_EQ(*(it--), 4);
    EXPECT_EQ(*it, 5);
    it += 2;
    EXPECT_EQ(*(it - 2), 5);
    it += 2;
    EXPECT_EQ(*it, 1);
    it -= 2;
    EXPECT_EQ(*it, 3);
    auto it2(it);
    EXPECT_TRUE(it == it2);
    it2 += 2;
    EXPECT_EQ(it2 - it, 2);
    EXPECT_FALSE(it == it2);
}

TEST(testIterator, constreverseIterator)
{
    const vector<int> v{1, 2, 3, 4, 5};
    vector<int>::const_reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(*(++it), 4);
    EXPECT_EQ(*(it++), 4);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*(it + 2), 1);
    EXPECT_EQ(*(--it), 4);
    EXPECT_EQ(*(it--), 4);
    EXPECT_EQ(*it, 5);
    it += 2;
    EXPECT_EQ(*(it - 2), 5);
    it += 2;
    EXPECT_EQ(*it, 1);
    it -= 2;
    EXPECT_EQ(*it, 3);
    auto it2(it);
    EXPECT_TRUE(it == it2);
    it2 += 2;
    EXPECT_EQ(it2 - it, 2);
    EXPECT_FALSE(it == it2);
}

//容量模块
TEST(testCapacity, size)
{
    vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(v.size(), 5);
    v.clear();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
}

TEST(testCapacity, capacity)
{
    vector<int> v{1, 2, 3, 4, 5};
    v.reserve(20);
    EXPECT_EQ(v.capacity(), 20);
}

//赋值函数
TEST(testOperator, oper)
{
    vector<int> v{1, 2, 3, 4, 5};
    vector<int> v2 = v;
    EXPECT_EQ(v2.size(), 5);
    EXPECT_TRUE(v == v2);
    vector<int> v3 = std::move(v2);
    EXPECT_EQ(v3.size(), 5);
    EXPECT_TRUE(v2.empty());
}
//元素访问
TEST(testLookUp, at)
{
    vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(4), 5);
    EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(testLookUp, oper)
{
    vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[4], 5);
}

TEST(testLookUp, frontAndback)
{
    vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(v.front(), 1);
    EXPECT_EQ(v.back(), 5);
}

//修改器模块
TEST(testModifier, clear)
{
    vector<int> v{1, 2, 43, 4, 5};
    v.clear();
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

TEST(testModifier, insert)
{
    vector<int> v{1, 2, 3, 4, 5};
    v.insert(v.begin(), 9);
    EXPECT_EQ(*(v.begin()), 9);
    v.insert(v.begin() + 3, 20);
    EXPECT_EQ(*(v.begin() + 3), 20);
}

TEST(testModifier, push_back)
{
    vector<int> v;
    v.push_back(2);
    EXPECT_EQ(v.size(), 1);
}

TEST(testModifier, erase)
{
    vector<int> v{1, 2, 3, 4, 5};
    v.erase(v.begin());
    EXPECT_EQ(v.front(), 2);
    v.erase(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(testModifier, pop_back)
{
    vector<int> v{1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
}

TEST(testModifier, resize)
{
    vector<int> v{2, 3, 4};
    v.resize(10);
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v[9], 0);
}

TEST(testModifier, swap)
{
    vector<int> v1{1, 2, 3};
    vector<int> v2{1};
    v1.swap(v2);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v2.size(), 3);
}

//非成员函数测试
TEST(testNonMemberFunc, swap)
{
    vector<int> v1{1, 2, 3};
    vector<int> v2{1};
    swap(v1, v2);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v2.size(), 3);
}

TEST(testNonMemberFunc, oper)
{
    vector<int> v1{1, 2, 3};
    vector<int> v2(v1);
    vector<int> v3{1, 2};
    vector<int> v4{1, 2, 3, 4};
    vector<int> v5{1, 2, 5};
    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 < v4);
    EXPECT_TRUE(v1 <= v4);
    EXPECT_TRUE(v1 < v5);
    EXPECT_TRUE(v5 > v1);
    EXPECT_TRUE(v5 >= v1);
    EXPECT_TRUE(v1 >= v2);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
