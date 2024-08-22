#include<gtest/gtest.h>
#include"MiniString.h"

TEST(testStringConstructor,constructor){
    string s;
    EXPECT_EQ(s.size(), 0);
    string s1(3, 'a');
    EXPECT_EQ(s.size(),3);
    string s2{'a','b','c'};
    EXPECT_EQ(s2.size(), 3);
    string s3(s2);
    EXPECT_EQ(s2.size(), 3);
    string smove(std::move(s3));
    EXPECT_EQ(smove.size(), 3);
    EXPECT_EQ(s3.size(),0);
    string ss(5);
    EXPECT_EQ(ss.size(), 5);
}

TEST(testIterator,iterator){

}

TEST(testString,data){

}

TEST(testString, c_str) {

}

TEST(testString, length) {

}

TEST(testString,append){

}

int main(int argc,char** argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
