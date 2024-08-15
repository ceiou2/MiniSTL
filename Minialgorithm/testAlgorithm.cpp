#include <gtest/gtest.h>
#include "MiniAlgorithm.h"
#include "MiniVector.h"

TEST(testBatchOperations, for_each)
{
    vector<int> v{1, 2, 3, 4, 5};
    for_each(v.begin(), v.end(), [](int& param) {
        ++param;
    });
    int i = 2;
    for (auto it = v.begin(); it != v.end(); ++it) {
        EXPECT_EQ(*it, i);
        ++i;
    }
}

TEST(testMinimum_MaximumOperations, min_element)
{
    vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(min_element(v.begin(), v.end()), v.begin());
    // 下面给一个相反的comp函数，这样min_element找到的就是最大值
    EXPECT_EQ(
            min_element(
                    v.begin(), v.end(),
                    [](const int& a, const int& b) -> bool {
                        return a > b;
                    }),
            v.begin() + 4);
}

TEST(testMinimum_MaximumOperations, max_element)
{
    vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(max_element(v.begin(), v.end()), v.begin() + 4);
    // 下面给一个相反的comp函数，这样max_element找到的就是最小值
    EXPECT_EQ(
            max_element(
                    v.begin(), v.end(),
                    [](const int& a, const int& b) -> bool {
                        return a > b;
                    }),
            v.begin());
}

TEST(testMinimum_MaximumOperations, min)
{
    EXPECT_EQ(min(1, 5), 1);
    // 下面给一个相反的comp函数，这样min找到的就是最大值
    EXPECT_EQ(
            min(1, 5,
                [](const int& a, const int& b) -> bool {
                    return a > b;
                }),
            5);
}

TEST(testMinimum_MaximumOperations, max)
{
    EXPECT_EQ(max(1, 5), 5);
    // 下面给一个相反的comp函数，这样max找到的就是最小值
    EXPECT_EQ(
            max(1, 5,
                [](const int& a, const int& b) -> bool {
                    return a > b;
                }),
            1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
