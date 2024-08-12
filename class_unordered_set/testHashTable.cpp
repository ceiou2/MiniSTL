#include <iostream>
#include "HashTable.h"
#include <gtest/gtest.h>
using namespace std;

class KeyOfT
{
public:
    int operator()(const int& key) const
    {
        return key;
    }
};

TEST(testHashTable, insert)
{
    HashTable<int, int, KeyOfT> ht;
    EXPECT_EQ(ht.get_size(), 0);
    ht.insert(3);
    EXPECT_EQ(ht.get_size(), 1);
    EXPECT_EQ(ht.find(3)->data, 3);
}

TEST(testHashTable, erase)
{
    HashTable<int, int, KeyOfT> ht;
    for (auto i = 0; i <= 10; ++i) {
        ht.insert(i);
    }
    EXPECT_EQ(ht.get_size(), 11);
    ht.erase(3);
    EXPECT_EQ(ht.get_size(), 10);
    EXPECT_EQ(ht.find(3), nullptr);
    ht.clear();
    EXPECT_EQ(ht.get_size(), 0);
    EXPECT_EQ(ht.find(2), nullptr);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
