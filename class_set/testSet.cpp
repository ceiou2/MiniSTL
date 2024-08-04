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
TEST(testIterator,iteratorConstructor){
    set<int> s{1, 2, 3, 4, 5};
    set<int>::iterator it1;
    set<int>::iterator it2 = s.begin();
    set<int>::iterator it3(it2);
    EXPECT_EQ(it2, it3);
    EXPECT_EQ(*it2, 1);
}

TEST(testIterator,iteratorOperator){
    set<int> s{2, 4, 6, 8, 10};
    set<int>::iterator it1 = s.begin();
    //*
    EXPECT_EQ(*it1, 2);
    //=
    set<int>::iterator it2;
    it2 = it1;
    EXPECT_EQ(*it2, 2);
    //++
    EXPECT_EQ(*(++it2), 4);
    EXPECT_EQ(*it2, 4);
    //++(int)
    EXPECT_EQ(*(it2++), 4);
    EXPECT_EQ(*it2, 6);
    //--
    EXPECT_EQ(*(--it2), 4);
    EXPECT_EQ(*it2,4);
    //--(int)
    EXPECT_EQ(*(it2--), 4);
    EXPECT_EQ(*it2, 2);
    //==
    EXPECT_TRUE(it2==it1);
    ++it2;
    EXPECT_FALSE(it2 == it1);
    //!=
    EXPECT_TRUE(it2 != it1);
    --it2;
    EXPECT_FALSE(it2 != it1);
}

//const_iterator部分
TEST(testConstIterator,ConstiteratorConstructor){
    set<int> s{1, 2, 3, 4, 5};
    set<int>::const_iterator it1;
    set<int>::const_iterator it2 = s.begin();
    set<int>::const_iterator it3(it2);
    set<int>::iterator it4=s.begin();
    it1 = it4;
    EXPECT_EQ(it2, it3);
    EXPECT_EQ(*it2, 1);
    EXPECT_EQ(*it1, 1);
    EXPECT_EQ(it1, it2);
    //oper== between const_iterator & iterator
    EXPECT_TRUE(it1 == it4);
    EXPECT_TRUE(it4 == it1);
    EXPECT_FALSE(it1 != it4);
    EXPECT_FALSE(it4 != it1);
}

TEST(testConstIterator,ConstiteratorOperator){
    set<int> s{2, 4, 6, 8, 10};
    set<int>::const_iterator it1 = s.begin();
    //*
    EXPECT_EQ(*it1, 2);
    //=
    set<int>::const_iterator it2;
    it2 = it1;
    EXPECT_EQ(*it2, 2);
    //++
    EXPECT_EQ(*(++it2), 4);
    EXPECT_EQ(*it2, 4);
    //++(int)
    EXPECT_EQ(*(it2++), 4);
    EXPECT_EQ(*it2, 6);
    //--
    EXPECT_EQ(*(--it2), 4);
    EXPECT_EQ(*it2,4);
    //--(int)
    EXPECT_EQ(*(it2--), 4);
    EXPECT_EQ(*it2, 2);
    //==
    EXPECT_TRUE(it2==it1);
    ++it2;
    EXPECT_FALSE(it2 == it1);
    //!=
    EXPECT_TRUE(it2 != it1);
    --it2;
    EXPECT_FALSE(it2 != it1);
    //const修改
    EXPECT_THROW(*it2 = 5, std::exception);
}

//reverse_iterator部分
TEST(testReverseIterator,ReverseiteratorConstructor){
    set<int> s{1, 2, 3, 4, 5};
    set<int>::reverse_iterator it1;
    set<int>::reverse_iterator it2 = s.rbegin();
    set<int>::reverse_iterator it3(it2);
    EXPECT_EQ(it2, it3);
    EXPECT_EQ(*it2, 5);
}

TEST(testReverseIterator,ReverseiteratorOperator){
    set<int> s{2, 4, 6, 8, 10};
    set<int>::reverse_iterator it1 = s.rbegin();
    //*
    EXPECT_EQ(*it1, 10);
    //=
    set<int>::reverse_iterator it2;
    it2 = it1;
    EXPECT_EQ(*it2, 10);
    //++
    EXPECT_EQ(*(++it2), 8);
    EXPECT_EQ(*it2, 8);
    //++(int)
    EXPECT_EQ(*(it2++), 8);
    EXPECT_EQ(*it2, 6);
    //--
    EXPECT_EQ(*(--it2), 8);
    EXPECT_EQ(*it2,8);
    //--(int)
    EXPECT_EQ(*(it2--), 8);
    EXPECT_EQ(*it2, 10);
    //==
    EXPECT_TRUE(it2==it1);
    ++it2;
    EXPECT_FALSE(it2 == it1);
    //!=
    EXPECT_TRUE(it2 != it1);
    --it2;
    EXPECT_FALSE(it2 != it1);
}

//const_reverse_iterator部分
TEST(testConstReverseIterator,ConstReverseiteratorConstructor){
    set<int> s{1, 2, 3, 4, 5};
    set<int>::const_reverse_iterator it1;
    set<int>::const_reverse_iterator it2 = s.rbegin();
    set<int>::const_reverse_iterator it3(it2);
    set<int>::reverse_iterator it4=s.rbegin();
    it1 = it4;
    EXPECT_EQ(it2, it3);
    EXPECT_EQ(*it2, 5);
    EXPECT_EQ(*it1, 5);
    EXPECT_EQ(it1, it2);
    //oper== between const_reverse_iterator & reverse_iterator
    EXPECT_TRUE(it1 == it4);
    EXPECT_TRUE(it4 == it1);
    EXPECT_FALSE(it1 != it4);
    EXPECT_FALSE(it4 != it1);
}

TEST(testConstReverseIterator,ConstReverseiteratorOperator){
    set<int> s{2, 4, 6, 8, 10};
    set<int>::const_reverse_iterator it1 = s.rbegin();
    //*
    EXPECT_EQ(*it1, 10);
    //=
    set<int>::const_reverse_iterator it2;
    it2 = it1;
    EXPECT_EQ(*it2, 10);
    //++
    EXPECT_EQ(*(++it2), 8);
    EXPECT_EQ(*it2, 8);
    //++(int)
    EXPECT_EQ(*(it2++), 8);
    EXPECT_EQ(*it2, 6);
    //--
    EXPECT_EQ(*(--it2), 8);
    EXPECT_EQ(*it2,8);
    //--(int)
    EXPECT_EQ(*(it2--), 8);
    EXPECT_EQ(*it2, 10);
    //==
    EXPECT_TRUE(it2==it1);
    ++it2;
    EXPECT_FALSE(it2 == it1);
    //!=
    EXPECT_TRUE(it2 != it1);
    --it2;
    EXPECT_FALSE(it2 != it1);
    //const修改
    EXPECT_THROW(*it2 = 5, std::exception);
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
