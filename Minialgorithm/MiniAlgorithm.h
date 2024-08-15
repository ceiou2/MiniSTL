//MiniAlgorithm.h
#pragma once
#ifndef MINI_ALGORITHM_H
#define MINI_ALGORITHM_H

#include<cstddef>

/*
**************************************************************
========================以下为函数声明模块=======================
**************************************************************
*/
///////////////////不改变序列的操作///////////
//=============批量操作================
// for_each
//对范围 [first, last) 中每个迭代器的解引用结果应用给定的函数对象
// f。忽略 f返回的结果。
template<class InputIt, class UnaryFunc>
UnaryFunc for_each(InputIt first, InputIt last, UnaryFunc f);
///////////////////修改序列的操作////////////


///////////////////排序和相关操作////////////
//=============最大最小操作=============
// min_element
//寻找范围 [first, last) 中的最小元素。
template<class ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last);

template<class ForwardIt, class Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp);

// min
//返回给定值中的较小者。
template<typename T>
const T& min(const T& a, const T& b);

template<typename T, typename Compare>
const T& min(const T& a, const T& b, Compare comp);

template<typename T>
T min(std::initializer_list<T> ilist);

template<typename T, typename Compare>
T min(std::initializer_list<T> ilist, Compare comp);

// max_element
//寻找范围 [first, last) 中的最大元素。
template<class ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last);

template<class ForwardIt, class Compare>
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp);

// max
//返回给定值中的较大者。
template<class T>
const T& max(const T& a, const T& b);

template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp);

template<class T>
T max(std::initializer_list<T> ilist);

template<class T, class Compare>
T max(std::initializer_list<T> ilist, Compare comp);

/*
**************************************************************
========================以下为函数定义模块=======================
**************************************************************
*/
///////////////////不改变序列的操作///////////
//=============批量操作================
// for_each
//对范围 [first, last) 中每个迭代器的解引用结果应用给定的函数对象
// f。忽略 f返回的结果。
template<class InputIt, class UnaryFunc>
UnaryFunc for_each(InputIt first, InputIt last, UnaryFunc f){
    for (; first != last; ++first)
        f(*first);

    return f;
}

//================搜索操作=============
//++++++++++++++++++++++++++++++++++start here
// all_of, any_of, none_of
//检查一元谓词 p 是否对范围 [first, last) 中所有元素返回 true
template<class InputIt, class UnaryPred>
bool all_of(InputIt first, InputIt last, UnaryPred p);

//检查一元谓词 p 是否对范围 [first, last) 中至少一个元素返回 true。
template<class InputIt, class UnaryPred>
bool any_of(InputIt first, InputIt last, UnaryPred p);

//检查一元谓词 p 是否不对范围 [first, last) 中任何元素返回 true。
template<class InputIt, class UnaryPred>
bool none_of(InputIt first, InputIt last, UnaryPred p);


// find, find_if, find_if_not
// find 搜索等于（用 operator== 比较）value 的元素。
template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value);

// find_if 搜索谓词 p 对其返回 true 的元素。
template<class InputIt, class UnaryPred>
InputIt find_if(InputIt first, InputIt last, UnaryPred p);

// find_if_not 搜索谓词 q 对其返回 false 的元素。
template<class InputIt, class UnaryPred>
InputIt find_if_not(InputIt first, InputIt last, UnaryPred q);

// find_end
//在范围 [first, last) 中搜索序列 [s_first, s_last) 最后一次出现的位置。
//用 operator== 比较元素。
template<class ForwardIt1, class ForwardIt2>
ForwardIt1 find_end(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last);

//用给定的二元谓词 p 比较元素。
template<class ForwardIt1, class ForwardIt2, class BinaryPred>
ForwardIt1 find_end(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last,
        BinaryPred p);

//find_first_of
//在范围 [first, last) 中搜索范围 [s_first, s_last) 中的任何元素。
//用 operator== 比较元素。
template<class InputIt, class ForwardIt>
InputIt
find_first_of(InputIt first, InputIt last, ForwardIt s_first, ForwardIt s_last);

//用给定的二元谓词 p 比较元素。
template<class InputIt, class ForwardIt, class BinaryPred>
InputIt find_first_of(
        InputIt first,
        InputIt last,
        ForwardIt s_first,
        ForwardIt s_last,
        BinaryPred p);

// count, count_if
//返回范围 [first, last) 中满足特定判别标准的元素数。
//计数等于 value 的元素（使用 operator==）。
template<class InputIt, class T>
typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value);

//计数谓词 p 对其返回 true 的元素。
template<class InputIt, class UnaryPred>
typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPred p);

//++++++++++++++++++++++++++++++++++++++++++++++++++start here
///////////////////修改序列的操作////////////

///////////////////排序和相关操作////////////
//=============最大最小操作=============
// min_element
//寻找范围 [first, last) 中的最小元素。

template<class ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last)
{
    ForwardIt res = first;
    while (first != last) {
        if (*first < *res)
            res = first;
        ++first;
    }
    return res;
}

template<class ForwardIt, class Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
{
    ForwardIt res = first;
    while (first != last) {
        if (comp(*first, *res))
            res = first;
        ++first;
    }
    return res;
}

// min
//返回给定值中的较小者。
template<typename T>
const T& min(const T& a, const T& b)
{
    return (b < a) ? b : a;
}

template<typename T, typename Compare>
const T& min(const T& a, const T& b, Compare comp)
{
    return (comp(b,a)) ? b : a;
}

template<typename T>
T min(std::initializer_list<T> ilist){
    return *min_element(ilist.begin(), ilist.end());
}

template<typename T, class Compare>
T min(std::initializer_list<T> ilist, Compare comp){
    return *min_element(ilist.begin(), ilist.end(), comp);
}


// max_element
//寻找范围 [first, last) 中的最大元素。
template<class ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last){
    ForwardIt res = first;
    while (first != last) {
        if (*first > *res)
            res = first;
        ++first;
    }
    return res;
}

template<class ForwardIt, class Compare>
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp){
    ForwardIt res = first;
    while (first != last) {
        if (comp(*res, *first))
            res = first;
        ++first;
    }
    return res;
}

// max
//返回给定值中的较大者。
template<class T>
const T& max(const T& a, const T& b){
    return (a < b) ? b : a;
}

template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp){
    return (comp(a, b)) ? b : a;
}

template<class T>
T max(std::initializer_list<T> ilist){
    return *max_element(ilist.begin(), ilist.end());
}

template<class T, class Compare>
T max(std::initializer_list<T> ilist, Compare comp){
    return *max_element(ilist.begin(), ilist.end(), comp);
}

#endif
