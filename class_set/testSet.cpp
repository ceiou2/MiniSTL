#include<gtest/gtest.h>
#include"MiniSet.h"
#include<vector>

//构造函数测试
TEST(TestConstructor,_default){
    set<int> s;
    EXPECT_TRUE(s.empty());
}

TEST(TestConstructor, _INITIALIZER)
{
    set<int> s{1,2,3,4,5};
    EXPECT_EQ(s.size(),5);
}

TEST(TestConstructor, Iterator_constructor)
{
    std::vector<int> v{1, 2, 3};
    set<int> s(v.begin(), v.end());
    EXPECT_EQ(s.size(),3);
}

TEST(TestConstructor, _copy)
{
    set<int> s_other{1, 2, 3, 4, 5};
    set<int> s(s_other);
    EXPECT_EQ(s.size(),5);
}

TEST(TestConstructor, _move)
{
    set<int> s_other{1, 2, 3, 4, 5};
    set<int> s(std::move(s_other));
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(s_other.size(), 0);
}

//成员函数测试
//赋值运算符模块
TEST(Testoperatorassign,copy_assign){
    set<int> s{1, 2, 3, 5, 6};
    set<int> s2 = s;
    EXPECT_EQ(s2.size(), s.size());
}

TEST(Testoperatorassign, move_assign)
{
    set<int> s{1, 2, 3, 5, 6};
    set<int> s2 = std::move(s);
    EXPECT_EQ(s2.size(), 5);
    EXPECT_EQ(s.size(), 0);
}

TEST(Testoperatorassign, initializer_assign)
{
    set<int> s={1, 2, 3, 5, 6};
    EXPECT_EQ(s.size(), 5);
}

//容量模块
TEST(TestCapacity,size){
    set<int> s;
    EXPECT_EQ(s.size(), 0);
    set<int> s3{1,2,3,4,5};
    EXPECT_EQ(s3.size(), 5);
}

TEST(TestCapacity,empty){
    set<int> s;
    EXPECT_TRUE(s.empty());
    set<int> s1{1};
    EXPECT_FALSE(s1.empty());
}

//迭代器模块
//iterator部分



int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
