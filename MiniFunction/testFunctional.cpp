//testFunctional.cpp
#include<gtest/gtest.h>
#include"MiniFunctional.h"

//算术运算模块
TEST(testPlus,plus){
    plus<int> add;
    EXPECT_EQ(5, add(2, 3));
}

TEST(testMinux,minus){
    minus<int> m;
    EXPECT_EQ(2, m(5, 3));
}

TEST(testMultiplies,multiplies){
    multiplies<int> mul;
    EXPECT_EQ(6, mul(2, 3));
}

TEST(testDivides,divides){
    divides<int> div;
    EXPECT_EQ(3, div(6, 2));
}

TEST(testModulus,modulus){
    modulus<int> mod;
    EXPECT_EQ(2, mod(10, 4));
}

TEST(testNegate,negate){
    negate<int> neg;
    EXPECT_EQ(-1, neg(1));
}

//比较模块
TEST(testEqual_to, equal_to)
{
    equal_to<int> eq_t;
    EXPECT_TRUE(eq_t(5, 5));
    EXPECT_FALSE(eq_t(2, 3));
}

TEST(testNot_Equal_to, not_equal_to)
{
    not_equal_to<int> neq_t;
    EXPECT_TRUE(neq_t(2, 3));
    EXPECT_FALSE(neq_t(5, 5));
}

TEST(testGreater, greater)
{
    greater<int> gt;
    EXPECT_TRUE(gt(5, 3));
    EXPECT_FALSE(gt(5, 5));
    EXPECT_FALSE(gt(3, 5));
}

TEST(testLess, less)
{
    less<int> lt;
    EXPECT_TRUE(lt(3, 5));
    EXPECT_FALSE(lt(5, 5));
    EXPECT_FALSE(lt(6, 5));
}

TEST(testGreater_equal, greater_equal)
{
    greater_equal<int> ge;
    EXPECT_TRUE(ge(5, 3));
    EXPECT_TRUE(ge(5, 5));
    EXPECT_FALSE(ge(3, 5));
}

TEST(testLess_equal, less_equal)
{
    less_equal<int> le;
    EXPECT_TRUE(le(3, 5));
    EXPECT_TRUE(le(5, 5));
    EXPECT_FALSE(le(6, 5));
}

//逻辑运算模块
TEST(testLogical_and,logical_and){
    logical_and<bool> log_a;
    EXPECT_TRUE(log_a(1, 1));
    EXPECT_FALSE(log_a(1, 0));
}

TEST(testLogical_or, logical_or)
{
    logical_or<bool> log_o;
    EXPECT_TRUE(log_o(1, 1));
    EXPECT_FALSE(log_o(0, 0));
}

TEST(testLogical_not, logical_not)
{
    logical_not<bool> log_n;
    EXPECT_TRUE(log_n(0));
    EXPECT_FALSE(log_n(1));
}

//位运算
TEST(testBit_and, bit_and)
{
    bit_and<int> bita;
    EXPECT_EQ(bita(1,3),1);
    EXPECT_EQ(bita(1,0),0);
}

TEST(testBit_or, bit_or)
{
    bit_or<int> bito;
    EXPECT_EQ(bito(1, 3), 3);
    EXPECT_EQ(bito(1, 0), 1);
}

TEST(testBit_xor, bit_xor)
{
    bit_xor<int> bitx;
    EXPECT_EQ(bitx(1, 3), 2);
    EXPECT_EQ(bitx(1, 0), 1);
}


int main(int argc,char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
