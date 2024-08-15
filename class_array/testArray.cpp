#include <gtest/gtest.h>
#include "MiniArray.h"

TEST(testConstructer, constructer)
{
    array<int, 5> arr{1, 2, 3, 4, 5};
    EXPECT_EQ(arr.size(), 5);

    array<int, 5> arr2(arr);
    EXPECT_TRUE(arr == arr2);

    array<int, 5> arr3 = arr;
    EXPECT_TRUE(arr == arr3);
}

TEST(TestAccess, at)
{
    array<int, 3> arr{1, 2, 3};
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(2), 3);
}

TEST(TestAccess, opera)
{
    array<int, 3> arr{1, 2, 3};
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);
}

TEST(TestAccess, front_back)
{
    array<int, 5> arr{1, 2, 3, 4, 5};
    EXPECT_EQ(arr.front(), 1);
    EXPECT_EQ(arr.back(), 5);
}

TEST(TestAccess, data)
{
    array<int, 5> arr{1, 2, 3, 4, 5};
    EXPECT_EQ(arr.data()[0], 1);
    EXPECT_EQ(arr.data()[4], 5);
}

TEST(TestIterator, iteratorANDconst_iterator)
{
    array<int, 5> arr{1, 2, 3, 4, 5};
    auto it = arr.begin();
    EXPECT_EQ(*it, 1);
    const array<int, 5> arr2{1, 2, 3, 4, 5};
    auto it2 = arr2.begin();
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*(++it), 2);
    EXPECT_EQ(*(++it2), 2);
    EXPECT_EQ(*(it++), 2);
    EXPECT_EQ(*(it2++), 2);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*it2, 3);
    EXPECT_EQ(*(it + 2), 5);
    EXPECT_EQ(*(it2 + 2), 5);
    it += 2;
    it2 += 2;
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(*it2, 5);
    EXPECT_EQ(*(--it), 4);
    EXPECT_EQ(*(--it2), 4);
    EXPECT_EQ(*(it--), 4);
    EXPECT_EQ(*(it2--), 4);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*it2, 3);
    EXPECT_EQ(*(it - 2), 1);
    EXPECT_EQ(*(it2 - 2), 1);
    it -= 2;
    it2 -= 2;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*it2, 1);
}

TEST(TestIterator_iterator, reverse_iteratorANDconst_reverse_iterator)
{
    array<int, 5> arr{1, 2, 3, 4, 5};
    auto it = arr.rbegin();
    EXPECT_EQ(*it, 5);
    const array<int, 5> arr2{1, 2, 3, 4, 5};
    auto it2 = arr2.rbegin();
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(*(++it), 4);
    EXPECT_EQ(*(++it2), 4);
    EXPECT_EQ(*(it++), 4);
    EXPECT_EQ(*(it2++), 4);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*it2, 3);
    EXPECT_EQ(*(it + 2), 1);
    EXPECT_EQ(*(it2 + 2), 1);
    it += 2;
    it2 += 2;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*it2, 1);
    EXPECT_EQ(*(--it), 2);
    EXPECT_EQ(*(--it2), 2);
    EXPECT_EQ(*(it--), 2);
    EXPECT_EQ(*(it2--), 2);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*it2, 3);
    EXPECT_EQ(*(it - 2), 5);
    EXPECT_EQ(*(it2 - 2), 5);
    it -= 2;
    it2 -= 2;
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(*it2, 5);
}

TEST(TestCapacity, empty)
{
    array<int, 5> arr{1, 2, 3};
    EXPECT_FALSE(arr.empty());
    array<int, 0> arr2;
    EXPECT_TRUE(arr2.empty());
}

TEST(TestCapacity, size)
{
    array<int, 5> arr{1, 2, 3};
    EXPECT_EQ(arr.size(), 5);
}

TEST(TestCapacity, max_size)
{
    array<int, 5> arr{1, 2, 3, 4};
    EXPECT_EQ(arr.max_size(), 5);
}

TEST(TestOperations, fill)
{
    array<int, 5> arr{1, 2};
    arr.fill(10);
    EXPECT_EQ(arr.at(0), 10);
}

TEST(TestOperations, swap)
{
    array<int, 3> arr1{1, 2, 3};
    array<int, 3> arr2{3, 2, 1};
    arr1.swap(arr2);
    EXPECT_EQ(arr1.front(), 3);
    EXPECT_EQ(arr2.front(), 1);
}

TEST(TestNon_MemberFunctions, oper)
{
    array<int, 5> arr1{1, 2, 3, 4, 5};
    array<int, 5> arr2(arr1);
    array<int, 5> arr3{1, 2, 3, 4, 6};
    array<int, 5> arr4{1, 2, 3, 4, 4};
    array<int, 5> arr5{1, 2, 3, 4};
    EXPECT_TRUE(arr1 == arr2);
    EXPECT_TRUE(arr1 != arr3);
    EXPECT_TRUE(arr1 < arr3);
    EXPECT_FALSE(arr3 < arr4);
    EXPECT_TRUE(arr1 > arr4);
    EXPECT_TRUE(arr4 >= arr5);
    EXPECT_TRUE(arr1 <= arr2);
}

TEST(TestNon_MemberFunctions, swap)
{
    array<int, 3> arr1{1, 2, 3};
    array<int, 3> arr2{3, 2, 1};
    swap(arr1, arr2);
    EXPECT_EQ(arr1.front(), 3);
    EXPECT_EQ(arr2.front(), 1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
