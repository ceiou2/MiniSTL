#include<gtest/gtest.h>
#include"MiniDeque.h"
#include"MiniVector.h"

TEST(TestConstructor,TestInt)
{
	//默认构造函数
	deque<int>NoArg;
	EXPECT_TRUE(NoArg.map.empty());

    int count=10;
	int value=2;
	deque<int>arg1(10);
	deque<int>arg2(10,2);
	EXPECT_EQ(arg1.size(),10);
	EXPECT_EQ(arg2.size(),10);
	for(int i=0;i<arg1.size();++i){
		EXPECT_EQ(arg1.at(i),0);
		EXPECT_EQ(arg2.at(i),2);
	}

	//构造iterator范围初始化容器
	deque<int>itarg(arg2.begin(),arg2.end());
	EXPECT_EQ(itarg,arg2);

	//复制构造函数
	deque<int>cpcs(arg2);
	EXPECT_EQ(cpcs,arg2);


	//移动构造函数
	deque<int>mvcs(std::move(arg2));
	EXPECT_EQ(cpcs.size(),10);
    EXPECT_EQ(arg2.size(), 0);
    EXPECT_TRUE(arg2.empty());

    //列表初始化构造
	deque<int>listcs{1,2,3,4,5};
	EXPECT_EQ(listcs.size(),5);
	EXPECT_EQ(listcs[0],1);


}

TEST(TestIterator,Iterator){
    deque<int> d1{1, 2, 3, 4, 5};
	//begin(),operator*
    EXPECT_EQ(*(d1.begin()), 1);
	//iterator++,end()
    int temp_i=1;
    for (auto i = d1.begin(); i != d1.end(); ++i) {
        EXPECT_EQ(*i,temp_i );
        ++temp_i;
    }

    temp_i = 5;
    // iterator--,operator +
    for (auto i = d1.begin() + 4; i != d1.begin(); --i) {
        EXPECT_EQ(*i, temp_i);
        --temp_i;
    }

    // operator -
    auto i = d1.begin() + 4;
    i = i - 4;
    EXPECT_EQ(*i, 1);

	//operator +=
    i = d1.begin();
    i += 2;
    EXPECT_EQ(*i, 3);

    //operator -=
    i = d1.begin() + 4;
    i -= 2;
    EXPECT_EQ(*i, 3);
}

TEST(TestOperator,Operator){
    deque<int> d1{1, 2, 3};
    deque<int> d2{5,6};
    deque<int> d3{1, 2, 3};
    // operator !=
    EXPECT_TRUE(d1 != d2);
    EXPECT_FALSE(d1 != d3);

	//operator ==
    EXPECT_TRUE(d1 == d3);
    EXPECT_FALSE(d1 == d2);

	//operator >
    EXPECT_FALSE(d1 > d2);
    EXPECT_TRUE(d2 > d1);

	//operator <
    EXPECT_FALSE(d2 < d1);
    EXPECT_TRUE(d1 < d2);

	//operator =
    d3 = d2;
    EXPECT_TRUE(d3 == d2);
    EXPECT_EQ(d3.size(), 2);
    EXPECT_TRUE(d3 != d1);

    //operator >=
    deque<int> d4{1, 2};
    EXPECT_TRUE(d1 >= d4);
    EXPECT_TRUE(d2 >= d3);
    EXPECT_TRUE(d2 >= d1);

	//operator <=
    EXPECT_TRUE(d4 <= d1);
    EXPECT_TRUE(d3 <= d2);
    EXPECT_TRUE(d1 <= d2);
}

TEST(TestFunction,assign){
    deque<int> dq1{6, 7, 8, 9, 10};
    // assign
    dq1.assign(3, 9);
    for (auto i = dq1.begin(); i != dq1.end(); ++i) {
        EXPECT_EQ(*i, 9);
    }

    deque<int> dq2 = {6, 7, 8, 9, 10};
    dq1.assign(dq2.begin(), dq2.end()); // inputIt == dequeIt
    EXPECT_EQ(dq1, dq2);
    vector<int> v{1, 2, 3, 4, 5};
    int k = 1;
    dq1.assign(v.begin(), v.end());
    for (auto i = dq1.begin(); i != dq1.end(); i++) { // operator++(int)
        EXPECT_EQ(*i, k);
        ++k;
    }
}

TEST(TestFunction, oper) {
    // at
    deque<int> d3{1, 2, 3, 4, 5};
    EXPECT_EQ(d3.at(2), 3);
    EXPECT_EQ(d3.at(0), 1);
    EXPECT_EQ(d3.at(4), 5);
    EXPECT_THROW(d3.at(5), std::out_of_range);
    EXPECT_THROW(d3.at(-1), std::out_of_range);

    // operator[]
    EXPECT_EQ(d3[2], 3);
    EXPECT_EQ(d3[0], 1);
    EXPECT_EQ(d3[4], 5);

    // front()
    EXPECT_EQ(d3.front(), 1);

    // back()
    EXPECT_EQ(d3.back(), 5);

    // empty(),clear()
    EXPECT_FALSE(d3.empty());
    d3.clear();
    EXPECT_TRUE(d3.empty());
}

TEST(TestFunction, size) {
    // size
    deque<int> d4{1, 2, 3, 4, 5};
    EXPECT_EQ(d4.size(), 5);
}

TEST(TestFunction, pop_push) {
    // push_back()
    deque<int> d10{1, 2, 3, 4, 5};
    d10.push_back(6);
    EXPECT_EQ(d10.back(), 6);
    EXPECT_EQ(d10.size(), 6);

    // pop_back()
    d10.pop_back();
    EXPECT_EQ(d10.back(), 5);
    EXPECT_EQ(d10.size(), 5);

    // push_front()
    d10.push_front(10);
    EXPECT_EQ(d10.front(), 10);
    EXPECT_EQ(d10.size(), 6);

    // pop_front()
    d10.pop_front();
    EXPECT_EQ(d10.front(), 1);
    EXPECT_EQ(d10.size(), 5);

    // erase
    d10.erase(d10.begin());
    EXPECT_EQ(d10.front(), 2);

    d10.erase(d10.begin() + 1);
    EXPECT_EQ(d10[1], 4);

    d10.erase(d10.begin() + 1, d10.end());
    EXPECT_EQ(d10.size(), 1);

    // resize
    d10.resize(10);
    EXPECT_EQ(d10.size(), 10);

    d10.resize(15, 3);
    EXPECT_EQ(d10.back(), 3);
    EXPECT_EQ(d10.size(), 15);

    d10.resize(10);
    EXPECT_EQ(d10.size(), 10);

    d10.resize(10);
    EXPECT_EQ(d10.size(), 10);

    // swap
    deque<int> dOther{1, 2, 3};
    d10.swap(dOther);
    EXPECT_EQ(d10.size(), 3);
    EXPECT_EQ(dOther.size(), 10);
}

TEST(TestFunction, insert)
{
    // insert
    deque<int> d5{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    d5.insert(d5.begin(), -2);
    EXPECT_EQ(d5.front(), -2);
    d5.insert(d5.begin() + 10, -1);
    EXPECT_EQ(d5[10], -1);
    d5.insert(d5.end(), 99); //?
    EXPECT_EQ(d5.back(), 99);
    deque<int> d6{1, 2, 3, 4, 5};
    d6.insert(d6.begin() + 1, 5, 7);
    for (int i = 1; i <= 5; ++i) {
        EXPECT_EQ(d6[i], 7);
    }
    deque<int> d7;
    d7.insert(d7.begin(), d6.begin(), d6.end());
    EXPECT_EQ(d6, d7);

    // EXPECT_TRUE(d6==d7);
    // initializer_list
}

TEST(TestReverseIterator,ReverseIterator)
{
    deque<int> d1{1, 2, 3, 4, 5};
    // begin(),operator*
    EXPECT_EQ(*(d1.rbegin()), 5);
    // iterator++,end()
    int temp_i = 1;
    for (auto i = d1.begin(); i != d1.end(); ++i) {
        EXPECT_EQ(*i, temp_i);
        ++temp_i;
    }

    temp_i = 5;
    // iterator--,operator +
    for (auto i = d1.begin() + 4; i != d1.begin(); --i) {
        EXPECT_EQ(*i, temp_i);
        --temp_i;
    }

    // operator -
    auto i = d1.begin() + 4;
    i = i - 4;
    EXPECT_EQ(*i, 1);

    // operator +=
    i = d1.begin();
    i += 2;
    EXPECT_EQ(*i, 3);

    // operator -=
    i = d1.begin() + 4;
    i -= 2;
    EXPECT_EQ(*i, 3);
}

int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
