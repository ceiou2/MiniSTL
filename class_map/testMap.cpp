#include<gtest/gtest.h>
#include"MiniMap.h"
#include<vector>

//构造函数测试
TEST(TestConstructor,_default){
    map<char,int> s;
    EXPECT_TRUE(s.empty());
}

TEST(TestConstructor, _INITIALIZER)
{
    map<char, int> s{{'a',1},{'b',2},{'c',3},{'d',4},{'e',5}};
    EXPECT_EQ(s.size(),5);
}

TEST(TestConstructor, Iterator_constructor)
{
    std::vector<std::pair<char, int> > v{
            {'a', 1}, {'b', 2}, {'c', 3}};
    map<char, int> s(v.begin(), v.end());
    EXPECT_EQ(s.size(),3);
}

TEST(TestConstructor, _copy)
{
    map<char, int> s_other{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int> s(s_other);
    EXPECT_EQ(s.size(),5);
    EXPECT_EQ(s_other.size(), 5);
}

TEST(TestConstructor, _move)
{
    map<char, int> s_other{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int> s(std::move(s_other));
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(s_other.size(), 0);
}

//成员函数测试
//赋值运算符模块
TEST(Testoperatorassign,copy_assign){
    map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int> s2 = s;
    EXPECT_EQ(s2.size(), s.size());
}

TEST(Testoperatorassign, move_assign)
{
    map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int> s2 = std::move(s);
    EXPECT_EQ(s2.size(), 5);
    EXPECT_EQ(s.size(), 0);
}

TEST(Testoperatorassign, initializer_assign)
{
    map<char, int> s = {{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    EXPECT_EQ(s.size(), 5);
}

//容量模块
TEST(TestCapacity,size){
    map<char, int> s;
    EXPECT_EQ(s.size(), 0);
    map<char, int> s3{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    EXPECT_EQ(s3.size(), 5);
}

TEST(TestCapacity,empty){
    map<char, int> s;
    EXPECT_TRUE(s.empty());
    map<char, int> s1{{'a', 1}};
    EXPECT_FALSE(s1.empty());
}

//迭代器模块
//iterator部分
TEST(testIterator,iteratorConstructor){
    map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int>::iterator it1;
    map<char, int>::iterator it2 = s.begin();
    map<char, int>::iterator it3(it2);
    EXPECT_EQ(it2, it3);
    EXPECT_EQ((*it2).first, 'a');
    EXPECT_EQ(it2->second, 1);
}

TEST(testIterator,iteratorOperator){
    map<char, int> s{{'a', 2}, {'b', 4}, {'c', 6}, {'d', 8}, {'e', 10}};
    map<char, int>::iterator it1 = s.begin();
    //*
    EXPECT_EQ(it1->second, 2);
    //=
    map<char, int>::iterator it2;
    it2 = it1;
    EXPECT_EQ(it2->second, 2);
    //++
    EXPECT_EQ((++it2)->second, 4);
    EXPECT_EQ(it2->second, 4);
    //++(int)
    EXPECT_EQ((it2++)->second, 4);
    EXPECT_EQ(it2->second, 6);
    //--
    EXPECT_EQ((--it2)->second, 4);
    EXPECT_EQ(it2->second,4);
    //--(int)
    EXPECT_EQ((it2--)->second, 4);
    EXPECT_EQ(it2->second, 2);
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
    map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int>::const_iterator it1;
    map<char, int>::const_iterator it2 = s.begin();
    map<char, int>::const_iterator it3(it2);
    map<char, int>::iterator it4 = s.begin();
    it1 = it4;
    EXPECT_EQ(it2, it3);
    EXPECT_EQ(it2->second, 1);
    EXPECT_EQ(it1->second, 1);
    EXPECT_EQ(it1, it2);
    //oper== between const_iterator & iterator
    EXPECT_TRUE(it1 == it4);
    EXPECT_TRUE(it4 == it1);
    EXPECT_FALSE(it1 != it4);
    EXPECT_FALSE(it4 != it1);
}

TEST(testConstIterator,ConstiteratorOperator){
    map<char, int> s{{'a', 2}, {'b', 4}, {'c', 6}, {'d', 8}, {'e', 10}};
    map<char, int>::const_iterator it1 = s.begin();
    //*
    EXPECT_EQ(it1->second, 2);
    //=
    map<char, int>::const_iterator it2;
    it2 = it1;
    EXPECT_EQ(it2->second, 2);
    //++
    EXPECT_EQ((++it2)->second, 4);
    EXPECT_EQ(it2->second, 4);
    //++(int)
    EXPECT_EQ((it2++)->second, 4);
    EXPECT_EQ(it2->second, 6);
    //--
    EXPECT_EQ((--it2)->second, 4);
    EXPECT_EQ(it2->second,4);
    //--(int)
    EXPECT_EQ((it2--)->second, 4);
    EXPECT_EQ(it2->second, 2);
    //==
    EXPECT_TRUE(it2==it1);
    ++it2;
    EXPECT_FALSE(it2 == it1);
    //!=
    EXPECT_TRUE(it2 != it1);
    --it2;
    EXPECT_FALSE(it2 != it1);
    //const修改
    //EXPECT_THROW(*it2 = 5, std::exception);
}

//reverse_iterator部分
TEST(testReverseIterator,ReverseiteratorConstructor){
    map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int>::reverse_iterator it1;
    map<char, int>::reverse_iterator it2 = s.rbegin();
    map<char, int>::reverse_iterator it3(it2);
    EXPECT_EQ(it2, it3);
    EXPECT_EQ(it2->second, 5);
}

TEST(testReverseIterator,ReverseiteratorOperator){
    map<char, int> s{{'a', 2}, {'b', 4}, {'c', 6}, {'d', 8}, {'e', 10}};
    map<char, int>::reverse_iterator it1 = s.rbegin();
    //*
    EXPECT_EQ(it1->second, 10);
    //=
    map<char, int>::reverse_iterator it2;
    it2 = it1;
    EXPECT_EQ(it2->second, 10);
    //++
    EXPECT_EQ((++it2)->second, 8);
    EXPECT_EQ(it2->second, 8);
    //++(int)
    EXPECT_EQ((it2++)->second, 8);
    EXPECT_EQ(it2->second, 6);
    //--
    EXPECT_EQ((--it2)->second, 8);
    EXPECT_EQ(it2->second,8);
    //--(int)
    EXPECT_EQ((it2--)->second, 8);
    EXPECT_EQ(it2->second, 10);
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
    map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    map<char, int>::const_reverse_iterator it1;
    map<char, int>::const_reverse_iterator it2 = s.rbegin();
    map<char, int>::const_reverse_iterator it3(it2);
    map<char, int>::reverse_iterator it4=s.rbegin();
    it1 = it4;
    EXPECT_EQ(it2, it3);
    EXPECT_EQ(it2->second, 5);
    EXPECT_EQ(it1->second, 5);
    EXPECT_EQ(it1, it2);
    //oper== between const_reverse_iterator & reverse_iterator
    EXPECT_TRUE(it1 == it4);
    EXPECT_TRUE(it4 == it1);
    EXPECT_FALSE(it1 != it4);
    EXPECT_FALSE(it4 != it1);
}

TEST(testConstReverseIterator,ConstReverseiteratorOperator){
    map<char, int> s{{'a', 2}, {'b', 4}, {'c', 6}, {'d', 8}, {'e', 10}};
    map<char, int>::const_reverse_iterator it1 = s.rbegin();
    //*
    EXPECT_EQ(it1->second, 10);
    //=
    map<char, int>::const_reverse_iterator it2;
    it2 = it1;
    EXPECT_EQ(it2->second, 10);
    //++
    EXPECT_EQ((++it2)->second, 8);
    EXPECT_EQ(it2->second, 8);
    //++(int)
    EXPECT_EQ((it2++)->second, 8);
    EXPECT_EQ(it2->second, 6);
    //--
    EXPECT_EQ((--it2)->second, 8);
    EXPECT_EQ(it2->second, 8);
    //--(int)
    EXPECT_EQ((it2--)->second, 8);
    EXPECT_EQ(it2->second, 10);
    //==
    EXPECT_TRUE(it2 == it1);
    ++it2;
    EXPECT_FALSE(it2 == it1);
    //!=
    EXPECT_TRUE(it2 != it1);
    --it2;
    EXPECT_FALSE(it2 != it1);
}

// //查找模块测试
// TEST(testLookup,count){
//     map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
//     EXPECT_EQ(s.count(1), 1);
//     EXPECT_EQ(s.count(6), 0);
// }

// TEST(testLookup,find){
//     map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5} ,{'f',6}};
//     map<char, int>::iterator i = s.find(6);
//     auto i2 = s.find(7);
//     EXPECT_EQ(*i, 6);
//     EXPECT_EQ(i2, s.end());
// }

// //修改器模块
// TEST(testModifiers,clear){
//     map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
//     EXPECT_EQ(s.size(), 5);
//     s.clear();
//     EXPECT_EQ(s.size(), 0);
//     s.insert(1);
//     EXPECT_EQ(s.size(), 1);
// }

// TEST(testModifiers,insert){
//     map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}};
//     s.insert(4);
//     EXPECT_EQ(s.count(4), 1);
//     int k = 5;
//     s.insert(std::move(5));
//     EXPECT_EQ(s.count(5), 1);
//     map<char, int> s2{7, 8, 9};
//     s.insert(s2.begin(), s2.end());
//     EXPECT_EQ(s.size(), 8);
//     s.insert({11, 12, 13, 14, 15});
//     EXPECT_EQ(s.size(), 13);
//     s.insert(1);
//     EXPECT_EQ(s.size(), 13);
// }

// TEST(testModifiers,erase){
//     map<char, int> s{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
//     auto it = s.erase(s.begin());
//     EXPECT_EQ(s.size(), 4);
//     EXPECT_EQ(*it, 2);
//     s.erase(s.begin(), s.end());
//     EXPECT_TRUE(s.empty());
//     s.insert(1);
//     EXPECT_EQ(s.erase(2), 0);
//     EXPECT_EQ(s.erase(1), 1);
// }

// TEST(testModifiers,swap){
//     map<char, int> s1{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
//     map<char, int> s2{6, 7, 8};
//     s1.swap(s2);
//     EXPECT_EQ(s1.size(), 3);
//     EXPECT_EQ(s2.size(), 5);
//     EXPECT_EQ(*s1.begin(), 6);
// }

// TEST(testNon_memberFunc,operator){
//     map<char, int> s1{1, 2, 3};
//     map<char, int> s2{1, 2, 3};
//     map<char, int> s3{1, 3};
//     map<char, int> s4{2};
//     EXPECT_TRUE(s1 == s2);
//     EXPECT_FALSE(s1 == s3);

//     EXPECT_TRUE(s1 < s3);
//     EXPECT_FALSE(s3 < s2);
//     EXPECT_FALSE(s1 < s2);

//     EXPECT_TRUE(s1 <= s2);
//     EXPECT_TRUE(s1 <= s3);
//     EXPECT_FALSE(s4 <= s1);

//     EXPECT_TRUE(s4 > s1);
//     EXPECT_FALSE(s1 > s2);
//     EXPECT_FALSE(s3 > s4);

//     EXPECT_TRUE(s4 >= s1);
//     EXPECT_TRUE(s2 >= s1);
//     EXPECT_FALSE(s3 >= s4);
// }

// TEST(testNon_memberFunc,swap){
//     map<char, int> s1{{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
//     map<char, int> s2{6, 7, 8};
//     swap(s1,s2);
//     EXPECT_EQ(s1.size(), 3);
//     EXPECT_EQ(s2.size(), 5);
//     EXPECT_EQ(*s1.begin(), 6);
// }

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
