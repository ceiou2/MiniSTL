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

TEST(testSearchOperations, all_ofANDany_ofANDnone_of){
    vector<int> v{1, 2, 3, 4, 5};
    bool res=all_of(v.begin(), v.end(), [](const int& a) -> bool {
        return a > 0;
    });
    EXPECT_TRUE(res);
    res = any_of(v.begin(), v.end(), [](const int& a) -> bool {
        return a == 5;
    });
    EXPECT_TRUE(res);
    res = none_of(v.begin(), v.end(), [](const int& a) -> bool {
        return a == 9;
    });
    EXPECT_TRUE(res);
}

TEST(testSearchOperations, find)
{
    vector<int> v{1, 2, 3, 4, 5};
    auto res = find(v.begin(), v.end(),1);
    EXPECT_EQ(res,v.begin());
    res = find_if(v.begin(), v.end(), [](const int& a) -> bool {
        return a == 1;
    });
    EXPECT_EQ(res, v.begin());
    res = find_if_not(v.begin(), v.end(), [](const int& a) -> bool {
        return a == 9;
    });
    EXPECT_EQ(res, v.begin());
}

TEST(testSearchOperations, findAfind_ifAfind_if_not)
{
    vector<int> v{1, 2, 3, 4, 5};
    auto res = find(v.begin(), v.end(), 1);
    EXPECT_EQ(res, v.begin());
    res = find_if(v.begin(), v.end(), [](const int& a) -> bool {
        return a == 1;
    });
    EXPECT_EQ(res, v.begin());
    res = find_if_not(v.begin(), v.end(), [](const int& a) -> bool {
        return a == 9;
    });
    EXPECT_EQ(res, v.begin());
}

TEST(testSearchOperations, find_end)
{
    vector<int> v{1, 2, 3, 4, 5, 1, 2, 3};
    vector<int> v2{1, 2, 3};
    auto ans = v.begin() + 5;
    auto res = find_end(v.begin(), v.end(), v2.begin(), v2.end());
    EXPECT_EQ(res, ans);
    res = find_end(
            v.begin(), v.end(), v2.begin(),
            v2.end(),[](const int& a,const int& b)->bool { return a == b; });
    EXPECT_EQ(res, ans);
}

TEST(testSearchOperations, find_first_of)
{
    vector<int> v{1, 2, 3, 4, 5, 1, 2, 3};
    vector<int> v2{1, 2, 3};
    auto ans = v.begin();
    auto res = find_first_of(v.begin(), v.end(), v2.begin(), v2.end());
    EXPECT_EQ(res, ans);
    res = find_first_of(
            v.begin(), v.end(), v2.begin(), v2.end(),
            [](const int& a, const int& b) -> bool {
                return a == b;
            });
    EXPECT_EQ(res, ans);
}

TEST(testSearchOperations, countANDcount_if)
{
    vector<int> v{1, 2, 3, 4, 5, 1, 2, 3};
    auto ans = 2;
    auto res = count(v.begin(), v.end(), 1);
    EXPECT_EQ(res, ans);
    res = count_if(
            v.begin(), v.end(),
            [](const int& a) -> bool {
                return a == 1;
            });
    EXPECT_EQ(res, ans);
}

TEST(testSearchOperations, equal)
{
    vector<int> v{1, 2, 3, 4, 5, 1, 2, 3};
    vector<int> v2{1, 2, 3};
    auto res = equal(v.begin(), v.begin()+3, v2.begin());
    EXPECT_TRUE(res);
    res = equal(v.begin(), v.begin() + 3, v2.begin(), [](const int& a,const int& b) -> bool {
        return a == b;
    });
    EXPECT_TRUE(res);
}

TEST(testSearchOperations, search)
{
    vector<int> v{1, 2, 3, 4, 5, 1, 2, 3};
    vector<int> v2{1, 2, 3};
    auto ans = v.begin();
    auto res = search(v.begin(), v.end(), v2.begin(),v2.end());
    EXPECT_EQ(res,ans);
    res =
            search(v.begin(), v.end(), v2.begin(), v2.end(),
                  [](const int& a, const int& b) -> bool {
                      return a == b;
                  });
    EXPECT_EQ(res, ans);
}

TEST(testCopyOperations,copyANDcopy_if){
    vector<int> v{9, 9, 9, 9, 9, 9, 9, 9};
    vector<int> v2{1, 2, 3};
    copy(v2.begin(), v2.end(), v.begin());
    auto ans = v.begin();
    auto res = search(v.begin(), v.end(), v2.begin(), v2.end());
    EXPECT_EQ(res, ans);
    copy_if(v2.begin(), v2.end(), v.begin() + 3, [](const int& a) -> bool {
        return a == 3;
    });
    EXPECT_EQ(*(v.begin() + 3), 3);
}

TEST(testSwapOperations,swap){
    vector<int> v{1, 2, 3};
    vector<int> v2{5};
    swap(v, v2);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v2.size(), 3);
}

TEST(testTransformation_Oprations,transform){
    vector<int> v(5,1);
    vector<int> v2(5,9);
    transform(v.begin(), v.end(), v2.begin(), [](const int& a) -> int {
        return a + 1;
    });
    EXPECT_EQ(v2, vector<int>(5, 2));
    vector<int> v3(5);
    transform(
            v.begin(), v.end(), v2.begin(), v3.begin(),
            [](const int& a, const int& b) -> int {
                return a + b;
            });
    EXPECT_EQ(*(v3.begin() + 1), 3);
}

TEST(testTransformation_Oprations, replaceANDreplace_if)
{
    vector<int> v(5, 1);
    replace(v.begin(), v.end(), 1, 2);
    EXPECT_EQ(v, vector<int>(5, 2));
    replace_if(
            v.begin(), v.end(),
            [](const int& a) -> bool {
                return a == 2;
            },3);
    EXPECT_EQ(*(v.begin() + 1), 3);
}

TEST(testGeneration_Oprations, fill)
{
    vector<int> v(5, 1);
    fill(v.begin(), v.end(), 2);
    EXPECT_EQ(v, vector<int>(5,2));
}

TEST(testGeneration_Operations, generate)
{
    vector<int> v(5, 1);
    generate(v.begin(), v.end(), []() -> int {
        return 2;
    });
    EXPECT_EQ(v, vector<int>(5, 2));
}

TEST(testRemoving_Operations,Remove__Remove_if){
    vector<int> v{1, 2, 3, 4, 5};
    auto new_end_i=remove(v.begin(), v.end(), 3);
    EXPECT_EQ(*(v.begin() + 2), 4);
    //计算剩余元素的数量
    auto ret = 0;
    for (auto i = v.begin(); i != new_end_i;++i,++ret){}
    EXPECT_EQ(ret, 4);
    new_end_i = remove_if(v.begin(), new_end_i, [](const int& a) -> bool {
        return a == 2;
    });
    EXPECT_EQ(*(v.begin() + 1), 4);
    ret = 0;
    for (auto i = v.begin(); i != new_end_i; ++i, ++ret) {}
    EXPECT_EQ(ret, 3);
}

TEST(testRemoving_Operations, unique) {
    vector<int> v{1, 1, 2, 2, 3, 3};
    auto new_end_i = unique(v.begin(), v.end());
    auto ret = 0;
    for (auto i = v.begin(); i != new_end_i; ++i, ++ret) {}
    EXPECT_EQ(ret, 3);
    vector<int> v2{1, 1, 2, 2, 3, 3};
    new_end_i =
            unique(v2.begin(), v2.end(), [](const int& a, const int& b) -> bool {
                return a == b;
            });
    ret = 0;
    for (auto i = v2.begin(); i != new_end_i; ++i, ++ret) {}
    EXPECT_EQ(ret, 3);
}

TEST(testOrder_Changing_operations,reverse){
    vector<int> v{1, 2, 3};
    reverse(v.begin(), v.begin() + 2);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(testOrder_Changing_operations,reverse_copy){
    vector<int> v1{1, 2, 3};
    vector<int> v2(9, 2);
    reverse_copy(v1.begin(), v1.end(),v2.begin());
    EXPECT_EQ(v2.front(), 1);
}

TEST(testOrder_Changing_operations, rotate)
{

}

TEST(testOrder_Changing_operations,random_shuffle){
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    vector<int> vec1(vec);
    random_shuffle(vec.begin(), vec.end());
    EXPECT_TRUE(vec != vec1);//这里有小概率失败，但是不代表程序错误
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

TEST(testPartitioningOperations,is_partitioned){
    vector<int> vec_true{1, 2, 3, 4, 5};
    vector<int> vec_false{1, 6, 2, 3, 4};
    EXPECT_TRUE(
            is_partitioned(vec_true.begin(), vec_true.end(),
            [](const int& a) -> bool {
                return a <= 3;
            }));
    EXPECT_FALSE(is_partitioned(
            vec_false.begin(), vec_false.end(), [](const int& a) -> bool {
                return a <= 3;
            }));
}

TEST(testPartitioningOperations,partition)
{
    vector<int> vec_false{1, 5, 2, 3, 4};
    EXPECT_FALSE(is_partitioned(
            vec_false.begin(), vec_false.end(), [](const int& a) -> bool {
                return a <= 3;
            }));
    partition(
            vec_false.begin(), vec_false.end(), [](const int& a) -> bool {
                return a <= 3;
            });
    EXPECT_TRUE(is_partitioned(
            vec_false.begin(), vec_false.end(), [](const int& a) -> bool {
                return a <= 3;
            }));
}

TEST(testPartitioningOperations, partition_copy)
{
    vector<int> vec{1, 5, 2, 3, 4};
    vector<int> vec1{9, 9};
    vector<int> vec2{9, 9, 9};
    partition_copy(
            vec.begin(), vec.end(), vec1.begin(), vec2.begin(),
            [](const int& a) -> bool {
                return a < 3;
            });
    EXPECT_EQ(find(vec1.begin(), vec1.end(), 9), vec1.end());
    EXPECT_NE(find(vec1.begin(), vec1.end(), 2), vec1.end());
    EXPECT_EQ(find(vec1.begin(), vec1.end(), 9), vec1.end());
    EXPECT_NE(find(vec1.begin(), vec1.end(), 5), vec1.end());
}
//++++++++++++++=starthere

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
