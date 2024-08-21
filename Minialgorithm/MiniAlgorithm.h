//MiniAlgorithm.h
//部分未实现：sort中的堆排序，stable_sort堆排序实现
#pragma once
#ifndef MINI_ALGORITHM_H
#define MINI_ALGORITHM_H

#include<cstddef>
#include<random>

#define Insert_Sort_Maxsize 32
#define Sort_MaxDepth   16

//********************辅助函数******************************* */
// iter_swap
//交换两个迭代器内容
template<typename InputIt>
void iter_swap(InputIt lhs, InputIt rhs)
{
    std::swap(*lhs, *rhs);
}

// next
//得到当前迭代器的下一个位置的迭代器
template<typename InputIt>
InputIt next(InputIt cur_iter,size_t step=1)
{
    while (step--) {
        ++cur_iter;
    }
    return cur_iter;
}

//distance
//得到两个迭代器之间的距离，要求第一参数在第二参数前面,不然会访问到last
template<typename InputIt>
size_t distance(InputIt first, InputIt second){
    size_t ret = 0;
    while (first != second) {
        ++ret;
        ++first;
    }
    return ret;
}

//insert_sort
//插入排序
template<class RandomIt, class Compare>
void insert_sort(RandomIt first, RandomIt last, Compare comp)
{
    size_t diff = distance(first, last);//获取元素数量
    for (auto i = 1; i < diff; ++i){//待排序的数组的遍历
        for (auto j = i; j > 0;--j){//待排序的元素向前方不断swap直至正确位置
            if(comp(*(first+j-1),*(first+j))){
                break;
            }
            iter_swap(first + j, first + j - 1);
        }
    }
}

//_sort
//sort的子函数，用于递归调用
template<class RandomIt, class Compare>
void _sort(RandomIt first, RandomIt last, int depth, Compare comp)
{
    //获取元素总数
    size_t diff = distance(first, last);
    //若元素很少则通过插入排序进行排序操作
    if (diff <= Insert_Sort_Maxsize) {
        return insert_sort(first, last, comp);
    }

    // if(depth<=0){//转换采用堆排序

    //     return;
    // }

    --depth;

    //一般情况下快排
    if (first ==
        last) // 只有一个元素，算排序完成（这里是预防性代码，当<=32时应该是插入排序才对，也就是说快排不会出现这种情况
        return;
    auto key = *first;
    //这里采用前后指针法进行快排
    auto pre = first;
    auto cur = pre + 1;
    while(cur!=last){//使pre+1左边都小于key
        if(!comp(key,*cur)){
            iter_swap(cur, ++pre);
        }
        ++cur;
    }
    iter_swap(first, pre);//最后将哨位放到pre的位置(pre一直是属于key左侧的)
    // 递归调用左右两侧[first,pre) [pre+1,last);pre位置上是key不用动了
    _sort(first, pre,depth,comp);
    _sort(pre + 1, last,depth,comp);
}

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

//================搜索操作=============
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

// find_first_of
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
size_t
count(InputIt first, InputIt last, const T& value);

//计数谓词 p 对其返回 true 的元素。
template<class InputIt, class UnaryPred>
size_t
count_if(InputIt first, InputIt last, UnaryPred p);

// equal
//检查 [first1, last1) 与从 first2 开始的另一个范围是否相等：
//用 operator== 比较元素。
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);

//用给定的二元谓词 p 比较元素。
template<class InputIt1, class InputIt2, class BinaryPred>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPred p);

// search
//搜索范围 [first, last) 中首次出现元素序列 [s_first, s_last) 的位置。
//元素用 operator== 比较
template<class ForwardIt1, class ForwardIt2>
ForwardIt1 search(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last);

//元素用给定的二元谓词 p 比较
template<class ForwardIt1, class ForwardIt2, class BinaryPred>
ForwardIt1 search(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last,
        BinaryPred p);

///////////////////修改序列的操作////////////
//================复制操作==================
// copy,copy_if
//复制范围 [first, last) 中的元素到从 d_first
//开始的另一范围（复制目标范围）。如果 d_first 在 [first, last)
//中，那么行为未定义。此时可以用 copy_backward 代替。
template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first);

//仅复制谓词 pred 对其返回 true
//的元素。此复制算法是稳定的：保持被复制元素的相对顺序。如果 [first, last)
//与复制目标范围重叠，那么行为未定义。
template<class InputIt, class OutputIt, class UnaryPred>
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPred pred);

//=================交换操作=================
// swap
//交换给定值
// template<class T>
// void swap(T& a, T& b);
//这一部分由容器实现swap特化

//================变换操作==================
// transform
// transform 应用给定的函数到某个/些输入范围中的元素，并将结果存储到从 d_first
// 开始的输出范围。
//应用一元函数 unary_op 到 [first1, last1) 中的元素。
template<class InputIt, class OutputIt, class UnaryOp>
OutputIt
transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op);

//应用二元函数 binary_op 到来自两个范围的元素对：一个范围是 [first1,
// last1)，而另一个范围包含 distance(first1, last1) 个元素并从 first2
// 开始。
template<class InputIt1, class InputIt2, class OutputIt, class BinaryOp>
OutputIt transform(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2,
        OutputIt d_first,
        BinaryOp binary_op);

// replace,replace_if
//以 new_value 替换范围 [first, last) 中所有满足特定判别标准的元素
//替换所有等于（用 operator== 比较）old_value 的元素。
template<class ForwardIt, class T>
void replace(
        ForwardIt first,
        ForwardIt last,
        const T& old_value,
        const T& new_value);

//替换所有谓词 p 对其返回 true 的元素。
template<class ForwardIt, class UnaryPred, class T>
void replace_if(
        ForwardIt first,
        ForwardIt last,
        UnaryPred p,
        const T& new_value);

//================生成操作==================
// fill
//将给定的 value 赋给 [first, last) 中的所有元素。
template<class ForwardIt, class T>
void fill(ForwardIt first, ForwardIt last, const T& value);

// generate
// 以给定函数对象 g 所生成的值对范围 [first, last) 中的每个元素赋值。
template<class ForwardIt, class Generator>
void generate(ForwardIt first, ForwardIt last, Generator g);

//================移除操作==================
// remove,remove_it
//从范围 [first, last)
//移除所有满足特定判别标准的元素，并返回范围新结尾的尾后迭代器。
// 移除所有等于（用 operator== 比较）value 的元素。
template<class ForwardIt, class T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value);

//移除所有 p 对于它返回 true 的元素。
template<class ForwardIt, class UnaryPred>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPred p);

// unique
//从范围 [first, last)
//移除相继等价元素组中首元素以外的所有元素，并返回范围新结尾的尾后迭代器。
//用 operator== 比较元素。
template<class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last);

//用给定的二元谓词 p 比较元素。
template<class ForwardIt, class BinaryPred>
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPred p);

//==============顺序变更操作================
// reverse
//反转 [first, last) 范围中的元素顺序。
template<class BidirIt>
void reverse(BidirIt first, BidirIt last);

// reverse_copy
//给定 N 为 std::distance(first, last)。将范围 [first,
//last)（源范围）中的元素复制到从 d_first 开始的包含 N
//个元素的新范围（目标范围），使得目标范围中元素以逆序排列。
template<class BidirIt, class OutputIt>
OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first);

// rotate
//+++++++++++++++++++++here

// rotate_copy

// random_shuffle
//重排序给定范围 [first, last)
//中的元素，使得这些元素的每个排列拥有相等的出现概率。
template<class RandomIt>
void random_shuffle(RandomIt first, RandomIt last);

///////////////////排序和相关操作////////////
//=============划分操作==================
// is_partitioned
//检查范围 [first, last) 是否已按谓词 p 划分：所有满足 p
//的元素都会在所有不满足的元素之前出现。
template<class InputIt, class UnaryPred>
bool is_partitioned(InputIt first, InputIt last, UnaryPred p);

// partition
//排序范围 [first, last) 中的元素，使得谓词 p 对其返回 true 的所有元素位于谓词 p
//对其返回 false 的所有元素之前。不保持相对顺序。
template<class ForwardIt, class UnaryPred>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPred p);

// partition_copy
//根据谓词 p 的返回值，将范围 [first, last) 中的元素复制到两个不同范围。
template<
        class InputIt,
        class OutputIt1,

        class OutputIt2,
        class UnaryPred>
std::pair<OutputIt1, OutputIt2> partition_copy(
        InputIt first,
        InputIt last,
        OutputIt1 d_first_true,
        OutputIt2 d_first_false,
        UnaryPred p);

// stable_partition
//重排序范围 [first, last) 中的元素，使得所有谓词 p 对其返回 true
//的元素均先于谓词 p 对其返回 false 的元素。保持元素的相对顺序。
template<class BidirIt, class UnaryPred>
BidirIt stable_partition(BidirIt first, BidirIt last, UnaryPred p);

// partition_point
//检验（如同用 std::partition）已划分范围 [first,
//last)，并定位第一分段的结尾，即首个不满足 p 的元素，或者在所有元素满足 p 时是
//last。
template<class ForwardIt, class UnaryPred>
ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPred p);

//============排序操作==================
// sort
//以非降序排序范围 [first, last) 中的元素。不保证维持相等元素的顺序。
template<class RandomIt>
void sort(RandomIt first, RandomIt last);

template<class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);

// stable_sort
//以非降序排序范围 [first, last) 中的元素。保证保持等价元素间的顺序
template<class RandomIt>
void stable_sort(RandomIt first, RandomIt last);

template<class RandomIt, class Compare>
void stable_sort(RandomIt first, RandomIt last, Compare comp);

// partial_sort
//重排元素，使得范围 [first, middle) 含有范围 [first, last) 中已排序的 middle -
//first 个最小元素。不保证保持相等元素间的顺序。
template<class RandomIt>
void partial_sort(RandomIt first, RandomIt middle, RandomIt last);

template<class RandomIt, class Compare>
void partial_sort(RandomIt first, RandomIt middle, RandomIt last, Compare comp);

// partial_sort_copy
//以升序排序范围 [first, last) 中的某些元素，存储结果于范围 [d_first, d_last)。
template<class InputIt, class RandomIt>
RandomIt partial_sort_copy(
        InputIt first,
        InputIt last,
        RandomIt d_first,
        RandomIt d_last);

template<class InputIt, class RandomIt, class Compare>
RandomIt partial_sort_copy(
        InputIt first,
        InputIt last,
        RandomIt d_first,
        RandomIt d_last,
        Compare comp);

// is_sorted

//======二分搜索操作（在以划分范围上）=====
// lower_bound

// upper_bound

// equal_range

// binary_search

//========集合操作（在一排序范围上）======
// includes

// set_union

// set_intersection

// set_difference

//=======归并操作（在以排序范围上）======
// merge

// inplace_merge

//================堆操作==============
// push_heap

// pop_heap

// make_heap

// sort_heap

// is_heap

// is_heap_until

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

//minmax

//minmax_element

//================字典序比较操作==============
//lexicographical_compare


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
// all_of, any_of, none_of
//检查一元谓词 p 是否对范围 [first, last) 中所有元素返回 true
template<class InputIt, class UnaryPred>
bool all_of(InputIt first, InputIt last, UnaryPred p){
    return find_if_not(first, last, p) == last;
}

//检查一元谓词 p 是否对范围 [first, last) 中至少一个元素返回 true。
template<class InputIt, class UnaryPred>
bool any_of(InputIt first, InputIt last, UnaryPred p){
    return find_if(first, last, p) != last;
}

//检查一元谓词 p 是否不对范围 [first, last) 中任何元素返回 true。
template<class InputIt, class UnaryPred>
bool none_of(InputIt first, InputIt last, UnaryPred p){
    return find_if(first, last, p) == last;
}


// find, find_if, find_if_not
// find 搜索等于（用 operator== 比较）value 的元素。
template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value){
    for (; first != last; ++first)
        if (*first == value)
            return first;

    return last;
}

// find_if 搜索谓词 p 对其返回 true 的元素。
template<class InputIt, class UnaryPred>
InputIt find_if(InputIt first, InputIt last, UnaryPred p){
    for (; first != last; ++first)
        if (p(*first))
            return first;

    return last;
}

// find_if_not 搜索谓词 q 对其返回 false 的元素。
template<class InputIt, class UnaryPred>
InputIt find_if_not(InputIt first, InputIt last, UnaryPred q){
    for (; first != last; ++first)
        if (!q(*first))
            return first;

    return last;
}

// find_end
//在范围 [first, last) 中搜索序列 [s_first, s_last) 最后一次出现的位置。
//用 operator== 比较元素。
template<class ForwardIt1, class ForwardIt2>
ForwardIt1 find_end(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last)
{
    if (s_first == s_last)
        return last;

    ForwardIt1 result = last;
    while (true) {
        ForwardIt1 new_result = search(first, last, s_first, s_last);
        if (new_result == last)
            break;
        else {
            result = new_result;
            first = result;
            ++first;
        }
    }
    return result;
}

//用给定的二元谓词 p 比较元素。
template<class ForwardIt1, class ForwardIt2, class BinaryPred>
ForwardIt1 find_end(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last,
        BinaryPred p)
{
    if (s_first == s_last)
        return last;

    ForwardIt1 result = last;
    while (true) {
        ForwardIt1 new_result = search(first, last, s_first, s_last, p);
        if (new_result == last)
            break;
        else {
            result = new_result;
            first = result;
            ++first;
        }
    }
    return result;
}

//find_first_of
//在范围 [first, last) 中搜索范围 [s_first, s_last) 中的任何元素。
//用 operator== 比较元素。
template<class InputIt, class ForwardIt>
InputIt
find_first_of(InputIt first, InputIt last, ForwardIt s_first, ForwardIt s_last)
{
    for (; first != last; ++first)
        for (ForwardIt it = s_first; it != s_last; ++it)
            if (*first == *it)
                return first;
    return last;
}

//用给定的二元谓词 p 比较元素。
template<class InputIt, class ForwardIt, class BinaryPred>
InputIt find_first_of(
        InputIt first,
        InputIt last,
        ForwardIt s_first,
        ForwardIt s_last,
        BinaryPred p)
        {
            for (; first != last; ++first)
                for (ForwardIt it = s_first; it != s_last; ++it)
                    if (p(*first, *it))
                        return first;
            return last;
        }

// count, count_if
//返回范围 [first, last) 中满足特定判别标准的元素数。
//计数等于 value 的元素（使用 operator==）。
template<class InputIt, class T>
size_t
count(InputIt first, InputIt last, const T& value)
{
    size_t ret = 0;
    for (; first != last; ++first)
        if (*first == value)
            ++ret;
    return ret;
}

//计数谓词 p 对其返回 true 的元素。
template<class InputIt, class UnaryPred>
size_t
count_if(InputIt first, InputIt last, UnaryPred p)
{
    size_t ret = 0;
    for (; first != last; ++first)
        if (p(*first))
            ++ret;
    return ret;
}

// equal
//检查 [first1, last1) 与从 first2 开始的另一个范围是否相等：
//用 operator== 比较元素。
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
        if (!(*first1 == *first2))
            return false;

    return true;
}

//用给定的二元谓词 p 比较元素。
template<class InputIt1, class InputIt2, class BinaryPred>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPred p)
{
    for (; first1 != last1; ++first1, ++first2)
        if (!p(*first1, *first2))
            return false;

    return true;
}

// search
//搜索范围 [first, last) 中首次出现元素序列 [s_first, s_last) 的位置。
//元素用 operator== 比较
template<class ForwardIt1, class ForwardIt2>
ForwardIt1 search(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last)
{
    while (true) {
        ForwardIt1 it = first;
        for (ForwardIt2 s_it = s_first;; ++it, ++s_it) {
            if (s_it == s_last)
                return first;
            if (it == last)
                return last;
            if (!(*it == *s_it))
                break;
        }
        ++first;
    }
}

//元素用给定的二元谓词 p 比较
template<class ForwardIt1, class ForwardIt2, class BinaryPred>
ForwardIt1 search(
        ForwardIt1 first,
        ForwardIt1 last,
        ForwardIt2 s_first,
        ForwardIt2 s_last,
        BinaryPred p)
        {
            while (true) {
                ForwardIt1 it = first;
                for (ForwardIt2 s_it = s_first;; ++it, ++s_it) {
                    if (s_it == s_last)
                        return first;
                    if (it == last)
                        return last;
                    if (!p(*it, *s_it))
                        break;
                }
                ++first;
            }
        }

///////////////////修改序列的操作////////////
//================复制操作==================
// copy,copy_if
//复制范围 [first, last) 中的元素到从 d_first
//开始的另一范围（复制目标范围）。如果 d_first 在 [first, last)
//中，那么行为未定义。此时可以用 copy_backward 代替。
template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    for (; first != last; (void)++first, (void)++d_first)
        *d_first = *first;

    return d_first;
}

//仅复制谓词 pred 对其返回 true
//的元素。此复制算法是稳定的：保持被复制元素的相对顺序。如果 [first, last)
//与复制目标范围重叠，那么行为未定义。
template<class InputIt, class OutputIt, class UnaryPred>
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPred pred)
{
    for (; first != last; ++first)
        if (pred(*first)) {
            *d_first = *first;
            ++d_first;
        }

    return d_first;
}

//=================交换操作=================
// swap
//交换给定值
// template<class T>
// void swap(T& a, T& b);
//这一部分由容器实现swap特化

//================变换操作==================
// transform
// transform 应用给定的函数到某个/些输入范围中的元素，并将结果存储到从 d_first
// 开始的输出范围。
//应用一元函数 unary_op 到 [first1, last1) 中的元素。
template<class InputIt, class OutputIt, class UnaryOp>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op)
{
    for (; first1 != last1; ++d_first, ++first1)
        *d_first = unary_op(*first1);

    return d_first;
}

//应用二元函数 binary_op 到来自两个范围的元素对：一个范围是 [first1,
//last1)，而另一个范围包含 distance(first1, last1) 个元素并从 first2 开始。
template<
        class InputIt1,
        class InputIt2,
        class OutputIt,
        class BinaryOp>
OutputIt transform(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2,
        OutputIt d_first,
        BinaryOp binary_op)
{
    for (; first1 != last1; ++d_first, ++first1, ++first2)
        *d_first = binary_op(*first1, *first2);

    return d_first;
}

// replace,replace_if
//以 new_value 替换范围 [first, last) 中所有满足特定判别标准的元素
//替换所有等于（用 operator== 比较）old_value 的元素。
template<class ForwardIt, class T>
void replace(
        ForwardIt first,
        ForwardIt last,
        const T& old_value,
        const T& new_value)
{
    for (; first != last; ++first)
        if (*first == old_value)
            *first = new_value;
}

//替换所有谓词 p 对其返回 true 的元素。
template<class ForwardIt, class UnaryPred, class T>
void replace_if(
        ForwardIt first,
        ForwardIt last,
        UnaryPred p,
        const T& new_value)
{
    for (; first != last; ++first)
        if (p(*first))
            *first = new_value;
}

//================生成操作==================
// fill
//将给定的 value 赋给 [first, last) 中的所有元素。
template<class ForwardIt, class T>
void fill(ForwardIt first, ForwardIt last, const T& value){
    for (; first != last; ++first)
        *first = value;
}

// generate
// 以给定函数对象 g 所生成的值对范围 [first, last) 中的每个元素赋值。
template<class ForwardIt, class Generator>
void generate(ForwardIt first, ForwardIt last, Generator g)
{
    for (; first != last; ++first)
        *first = g();
}

//================移除操作==================
// remove,remove_it
//从范围 [first, last)
//移除所有满足特定判别标准的元素，并返回范围新结尾的尾后迭代器。
// 移除所有等于（用 operator== 比较）value 的元素。
template<class ForwardIt, class T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
    first = find(first, last, value);
    if (first != last)
        for (ForwardIt i = first; ++i != last;)
            if (!(*i == value))
                *first++ = std::move(*i);
    return first;
}

//移除所有 p 对于它返回 true 的元素。
template<class ForwardIt, class UnaryPred>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPred p)
{
    first = find_if(first, last, p);
    if (first != last)
        for (ForwardIt i = first; ++i != last;)
            if (!p(*i))
                *first++ = std::move(*i);
    return first;
}

// unique
//从范围 [first, last)
//移除相继等价元素组中首元素以外的所有元素，并返回范围新结尾的尾后迭代器。
//用 operator== 比较元素。
template<class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last)
{
    if (first == last)
        return last;

    ForwardIt result = first;
    while (++first != last)
        if (!(*result == *first) && ++result != first)
            *result = std::move(*first);

    return ++result;
}

//用给定的二元谓词 p 比较元素。
template<class ForwardIt, class BinaryPred>
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPred p)
{
    if (first == last)
        return last;

    ForwardIt result = first;
    while (++first != last)
        if (!p(*result, *first) && ++result != first)
            *result = std::move(*first);

    return ++result;
}

//==============顺序变更操作================
// reverse
//反转 [first, last) 范围中的元素顺序。
template<class BidirIt>
void reverse(BidirIt first, BidirIt last)
{
    while (first!=last && first != --last) {
        iter_swap(first++, last);
    }
}

// reverse_copy
//给定 N 为 std::distance(first, last)。将范围 [first,
//last)（源范围）中的元素复制到从 d_first 开始的包含 N
//个元素的新范围（目标范围），使得目标范围中元素以逆序排列。
template<class BidirIt, class OutputIt>
OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first){
    for (; first != last; ++d_first)
        *d_first = *(--last);
    return d_first;
}

//rotate

//rotate_copy

// random_shuffle
//重排序给定范围 [first, last)
//中的元素，使得这些元素的每个排列拥有相等的出现概率。
template<class RandomIt>
void random_shuffle(RandomIt first, RandomIt last){
    for (int i = last - first - 1; i > 0; --i) {
        iter_swap(first+i, first+(std::rand() % (i + 1)));
    }
}

///////////////////排序和相关操作////////////
//=============划分操作==================
// is_partitioned
//检查范围 [first, last) 是否已按谓词 p 划分：所有满足 p
//的元素都会在所有不满足的元素之前出现。
template<class InputIt, class UnaryPred>
bool is_partitioned(InputIt first, InputIt last, UnaryPred p){
    for (; first != last; ++first)
        if (!p(*first))
            break;
    for (; first != last; ++first)
        if (p(*first))
            return false;
    return true;
}

// partition
//排序范围 [first, last) 中的元素，使得谓词 p 对其返回 true 的所有元素位于谓词 p
//对其返回 false 的所有元素之前。不保持相对顺序。
template<class ForwardIt, class UnaryPred>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPred p){
    first = find_if_not(first, last, p);
    if (first == last)
        return first;

    for (auto i = next(first); i != last; ++i) {
        if (p(*i)) {
            iter_swap(i, first);
            ++first;
        }
    }

    return first;
}

// partition_copy
//根据谓词 p 的返回值，将范围 [first, last) 中的元素复制到两个不同范围。
template<
        class InputIt,
        class OutputIt1,

        class OutputIt2,
        class UnaryPred>
std::pair<OutputIt1, OutputIt2> partition_copy(
        InputIt first,
        InputIt last,
        OutputIt1 d_first_true,
        OutputIt2 d_first_false,
        UnaryPred p)
{
    for (; first != last; ++first) {
        if (p(*first)) {
            *d_first_true = *first;
            ++d_first_true;
        } else {
            *d_first_false = *first;
            ++d_first_false;
        }
    }

    return std::pair<OutputIt1, OutputIt2>(d_first_true, d_first_false);
}

// stable_partition
//重排序范围 [first, last) 中的元素，使得所有谓词 p 对其返回 true
//的元素均先于谓词 p 对其返回 false 的元素。保持元素的相对顺序。
template<class BidirIt, class UnaryPred>
BidirIt stable_partition(BidirIt first, BidirIt last, UnaryPred p);
//+++++++++++++++++++++start here
// partition_point
//检验（如同用 std::partition）已划分范围 [first,
// last)，并定位第一分段的结尾，即首个不满足 p 的元素，或者在所有元素满足 p 时是
// last。
template<class ForwardIt, class UnaryPred>
ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPred p){
    for (auto length = distance(first, last); 0 < length;) {
        auto half = length / 2;
        auto middle = next(first, half);
        if (p(*middle)) {
            first = next(middle);
            length -= (half + 1);
        } else
            length = half;
    }

    return first;
}

//============排序操作==================
//sort
//以非降序排序范围 [first, last) 中的元素。不保证维持相等元素的顺序。
template<class RandomIt>
void sort(RandomIt first, RandomIt last){
    sort(first, last, [](const auto& lhs, const auto& rhs) -> bool {
        return lhs < rhs;
    });
}

template<class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp){
    _sort(first, last, Sort_MaxDepth, comp);
}

// stable_sort
//以非降序排序范围 [first, last) 中的元素。保证保持等价元素间的顺序
template<class RandomIt>
void stable_sort(RandomIt first, RandomIt last){
    stable_sort(first, last, [](const auto& lhs, const auto& rhs) -> bool {
        return lhs < rhs;
    });
}

template<class RandomIt, class Compare>
void stable_sort(RandomIt first, RandomIt last, Compare comp){
    //堆排序稳定版
}

// partial_sort
//重排元素，使得范围 [first, middle) 含有范围 [first, last) 中已排序的 middle -
// first 个最小元素。不保证保持相等元素间的顺序。
template<class RandomIt>
void partial_sort(RandomIt first, RandomIt middle, RandomIt last){
    //这里cppreference有实现
}

template<class RandomIt, class Compare>
void partial_sort(RandomIt first, RandomIt middle, RandomIt last, Compare comp);

// partial_sort_copy
//以升序排序范围 [first, last) 中的某些元素，存储结果于范围 [d_first, d_last)。
template<class InputIt, class RandomIt>
RandomIt partial_sort_copy(
        InputIt first,
        InputIt last,
        RandomIt d_first,
        RandomIt d_last);

template<class InputIt, class RandomIt, class Compare>
RandomIt partial_sort_copy(
        InputIt first,
        InputIt last,
        RandomIt d_first,
        RandomIt d_last,
        Compare comp);

//is_sorted

//======二分搜索操作（在以划分范围上）=====
//lower_bound

//upper_bound

//equal_range

//binary_search

//========集合操作（在一排序范围上）======
//includes

//set_union

//set_intersection

//set_difference

//=======归并操作（在以排序范围上）======
//merge

//inplace_merge

//================堆操作==============
//push_heap

//pop_heap

//make_heap

//sort_heap

//is_heap

//is_heap_until


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
