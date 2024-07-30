// MiniArray.h
#pragma once
#ifndef _MiniArray_H
#define _MiniArray_H

#include <cstddef> //ptrdiff_t头文件

// array类声明
template<typename T, size_t Num>
class array
{
private:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef const reference const_reference;
    typedef const pointer const_pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference;
    typedef value_type* iterator;
    typedef const T* const_iterator;
    typedef value_type* reverse_iterator;
    typedef const T* const_reverse_iterator;

    value_type array_container[Num ? Num : 1]; //可以处理0空间情况

public:
    //默认构造函数
    array()
    {
        for (size_type i = 0; i < Num; ++i) {
            array_container[i] = T(); //初始化
        }
    }

    //拷贝构造函数
    array(const array<T, Num>& inputArray)
    {
        *this = inputArray;
    }

    //移动构造函数
    array(array<T, Num>&& inputArray)
    {
        array_container = inputArray.array_container;
        inputArray.array_container = nullptr;
    }

    //析构函数
    ~array() {}

    //{}列表初始化构造函数
    array(std::initializer_list<T> init)
    {
        if (init.size() > Num) {
            throw std::length_error("too many elements in initializer list");
        }
        std::copy(init.begin(), init.end(), data());
    }

    //获取首部迭代器
    iterator begin()
    {
        return &array_container[0];
    }

    //获取尾部迭代器
    iterator end()
    {
        return &array_container[Num];
    }

    //--------元素访问模块----------
    // at:带越界检查访问指定的元素
    reference at(const size_type& ind)
    {
        if (ind >= Num) // check range
        {
            throw std::out_of_range("out_of_range");
        }
        return data()[ind];
    }

    // operator[]:访问指定元素
    reference operator[](const size_type& ind)
    {
        return data()[ind];
    }
    // const version
    const_reference operator[](const size_type& ind) const
    {
        return data()[ind];
    }

    // front:访问第一个元素
    reference front()
    {
        return at(0);
    }
    const_reference front() const
    {
        return at(0);
    }

    // back:访问最后一个元素
    reference back()
    {
        return at(Num - 1);
    }
    const_reference back() const
    {
        return at(Num - 1);
    }

    // data:直接访问底层首地址
    pointer data()
    {
        return array_container;
    }
    // const_pointer data() const{return array_container;}

    //---------容量模块----------
    // empty()
    [[nodiscard]] constexpr bool empty() const
    {
        if (Num == 0) {
            return true;
        }
        return false;
    }

    // size
    constexpr size_type size() const
    {
        return Num;
    }

    // max_size
    constexpr size_type max_size() const
    {
        return Num;
    }

    //---------操作模块----------
    // fill():以指定值填充容器
    void fill(const value_type& value)
    {
        for (size_type i = 0; i < Num; ++i) {
            array_container[i] = value;
        }
    }

    // swap:将容器内容与other的内容交换。不会导致迭代器和引用关联到别的容器
    void swap(array& other)
    {
        if (other.size() != Num) //检查大小,防止越界
        {
            return;
        }
        for (size_type i = 0; i < Num; ++i) {
            swap(array_container[i], other[i]);
        }
    }



    //--------辅助模块----------
    //略
};

//---------非成员函数模块----------
template<typename T,size_t N>
bool operator==(const array<T,N>&lhs,const array<T,N>&rhs){
    if(lhs.size()!=rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size;++i){
        if(lhs[i]!=rhs[i])
            return false;
    }
    return true;
}

template<typename T, size_t N>
bool operator!=(const array<T, N>& lhs, const array<T, N>& rhs)
{
    if(lhs==rhs)
        return false;
    return true;
}

template<typename T, size_t N>
bool operator<(const array<T, N>& lhs, const array<T, N>& rhs)
{
    size_type i = 0;
    while(i<lhs.size() && i<rhs.size()){
        if(lhs[i]<rhs[i]){
            return true;
        }
        else if(lhs[i]>rhs[i]){
            return false;
        }
        ++i;
    }
    if(lhs.size()<rhs.size()){
        return true;
    }
    return false;
}

template<typename T, size_t N>
bool operator<=(const array<T, N>& lhs, const array<T, N>& rhs)
{
    if(lhs<rhs || lhs==rhs)
        return true;
    return false;
}

template<typename T, size_t N>
bool operator>(const array<T, N>& lhs, const array<T, N>& rhs)
{
    if (lhs < rhs || lhs == rhs)
        return false;
    return true;
}

template<typename T, size_t N>
bool operator>=(const array<T, N>& lhs, const array<T, N>& rhs)
{
    if (!(lhs < rhs))
    return true;
    return false;
}


#endif
