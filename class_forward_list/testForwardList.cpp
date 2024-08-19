#include<gtest/gtest.h>
#include"MiniForwardList.h"

TEST(testConstructor,constructor)
{
    forward_list<int>fl;
    EXPECT_EQ(fl.size(),0);
    forward_list<int>fl2(5,1);
    EXPECT_EQ(fl2.size(),5);
    EXPECT_EQ(fl2.front(),1);
    forward_list<int>fl3{1,2,3,4,5};
    EXPECT_EQ(fl3.size(),5);
    EXPECT_EQ(fl3.front(),1);
    forward_list<int>fl4(fl3);
    EXPECT_EQ(fl3.size(),5);
    EXPECT_EQ(fl3.front(),1);
    EXPECT_EQ(fl4.size(),5);
    EXPECT_EQ(fl4.front(),1);
    EXPECT_EQ(fl3,fl4);
    forward_list<int>fl5(std::move(fl4));
    EXPECT_TRUE(fl4.empty());
    EXPECT_EQ(fl5.size(),5);
}

TEST(testoperassign,operassign){
    forward_list<int> fl1{1,2,3,4,5};
    forward_list<int> fl2;
    fl2=fl1;//这里需要先定义fl2再赋值，不然会直接调用拷贝构造函数
    EXPECT_EQ(fl1,fl2);

    forward_list<int> fl3;
    fl3=std::move(fl2);
    EXPECT_EQ(fl3,fl1);
    EXPECT_TRUE(fl2.empty());
    forward_list<int> fl5(5);
    EXPECT_EQ(fl5.size(),5);
    EXPECT_EQ(fl5.front(),0);
}

TEST(testIterator,iterator)
{
    forward_list<int> fl{1,2,3,4,5};
    auto i=fl.begin();
    EXPECT_EQ(*i,1);
    EXPECT_EQ(*(++i),2);
    EXPECT_EQ(*(i++),2);
    EXPECT_EQ(*i,3);
    auto i1=fl.begin();
    auto i2=fl.begin();
    EXPECT_TRUE(i1==i2);
    EXPECT_TRUE(i1!=i);
}

TEST(testIterator,constIterator){
    forward_list<int>fl{1,2,3,4,5};
    const forward_list<int>cfl{1,2,3,4,5};
    auto fli=fl.cbegin();
    auto cfli=cfl.begin();
    EXPECT_EQ(*fli,1);
    EXPECT_EQ(*(++fli),2);
    EXPECT_EQ(*(fli++),2);
    EXPECT_EQ(*fli,3);
    EXPECT_EQ(*cfli,1);
    EXPECT_EQ(*(++cfli),2);
    EXPECT_EQ(*(cfli++),2);
    EXPECT_EQ(*cfli,3);
    auto fli1=fl.begin();
    auto fli2=fl.begin();
    EXPECT_TRUE(fli1==fli2);
    EXPECT_TRUE(fli1!=fli);
    auto cfli1=cfl.begin();
    auto cfli2=cfl.begin();
    EXPECT_TRUE(cfli1==cfli2);
    EXPECT_TRUE(cfli1!=cfli);
}

TEST(testCapacity,empty){
    forward_list<int>fl;
    forward_list<int>fl2{1};
    EXPECT_TRUE(fl.empty());
    EXPECT_FALSE(fl2.empty());
}

TEST(testCapacity,size){
    forward_list<int>fl(10);
    EXPECT_EQ(fl.size(),10);
}

TEST(testAccess,front){
    forward_list<int>fl{1,2,3};
    EXPECT_EQ(fl.front(),1);
}

TEST(testModifier,swap){
    forward_list<int>fl1{1,2,3,4,5};
    forward_list<int>fl2{1,2,3};
    fl1.swap(fl2);
    EXPECT_EQ(fl1.size(),3);
    EXPECT_EQ(fl2.size(),5);
}

TEST(testModifier,clear){
    forward_list<int>fl{1,2};
    fl1.clear();
    EXPECT_TRUE(fl1.empty());
    fl1.push_front(3);
    EXPECT_EQ(fl1.front(),3);
}

TEST(testModifier,push_front){
    forward_list<int>fl{1,2,3};
    fl.push_front(9);
    EXPECT_EQ(fl.front(),9);
}

TEST(testModifier,pop_front){
    forward_list<int>fl{1,2,3};
    fl.pop_front();
    EXPECT_EQ(fl.size(),2);
    EXPECT_EQ(fl.front(),2);
}

TEST(testModifier,insert_after){
    forward_list<int>fl{1,2,3};
    fl.insert_after(fl.begin(),9);
    auto i=fl.begin();
    ++i;
    EXPECT_EQ(*i,9);
    EXPECT_EQ(fl.size(),4);
    fl.insert_after(fl.begin(),3,7);
    i=fl.begin();
    ++i;
    EXPECT_EQ(*i,7);
    EXPECT_EQ(fl.size(),7);
    forward_list<int>fl2{1,2};
    fl2.insert_after(fl2.begin(),fl1.begin(),fl1.end());
    EXPECT_EQ(fl2.size(),9);
}

//+++++++++++++++++++++starthere erase

int main(int argc, char** argv){
    testing::GoogleTestInit();
	return RUN_ALL_TESTS();
}
