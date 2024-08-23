//MiniFunctional.h
#pragma once
#ifndef MINI_FUNCTIONAL_H
#define MINI_FUNCTIONAL_H

#include<cstddef>


//===================算术运算模块================
//plus
//进行加法的函数对象。相当于在两个 T 类型的实例上调用 operator+
template<typename T>
struct plus
{
    T operator()(const T& lhs, const T& rhs)const{
        return lhs + rhs;
    }
};

// minus
//进行减法的函数对象。等效于在两个 T 类型实例上调用 operator-
template<typename T>
struct minus
{
    T operator()(const T& lhs, const T& rhs)const{
        return lhs - rhs;
    }
};

// multiplies
//进行乘法的函数对象。相当于在两个 T 类型实例上调用 operator*
template<typename T>
struct multiplies
{
    T operator()(const T& lhs, const T& rhs) const
    {
        return lhs * rhs;
    }
};

// divides
//进行除法的函数对象。相当于在两个 T 类型实例上调用 operator/
template<typename T>
struct divides
{
    T operator()(const T& lhs, const T& rhs) const
    {
        return lhs / rhs;
    }
};

// modulus
//进行取余的函数对象。相当于在两个 T 类型实例上调用 operator%
template<typename T>
struct modulus
{
    T operator()(const T& lhs, const T& rhs) const
    {
        return lhs % rhs;
    }
};

// negate
//进行取反的函数对象。相当于在一个 T 类型实例上调用 operator-
template<typename T>
struct negate
{
    // typedef T result_type;
    // typedef T argument_type;
    T operator()(const T& arg) const
    {
        return -arg;
    }
};

//=====================比较模块=================
// equal_to
//进行比较的函数对象。除非被特化，调用类型 T 上的 operator==
template<typename T>
struct equal_to
{
    bool operator()(const T&lhs, const T& rhs)const{
        return lhs == rhs;
    }
};

// not_equal_to
//进行比较的函数对象。除非被特化，调用类型 T 上的 operator!=
template<typename T>
struct not_equal_to
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs != rhs;
    }
};

// greater
//进行比较的函数对象。主模板会调用类型 T 上的 operator>
template<typename T>
struct greater
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs > rhs;
    }
};

// less
//进行比较的函数对象。主模板会调用类型 T 上的 operator<
template<typename T>
struct less
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }
};

// greater_equal
//进行比较的函数对象。主模板会调用类型 T 上的 operator<
template<typename T>
struct greater_equal
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs >= rhs;
    }
};

// less_equal
//进行比较的函数对象。主模板会调用类型 T 上的 operator<
template<typename T>
struct less_equal
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs <= rhs;
    }
};

//===================逻辑运算模块================
//logical_and
template<typename T>
struct logical_and
{
    bool operator()(const T& lhs, const T& rhs)const{
        return lhs && rhs;
    }
};

// logical_or
template<typename T>
struct logical_or
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs || rhs;
    }
};

// logical_not
template<typename T>
struct logical_not
{
    bool operator()(const T& arg) const
    {
        return !arg;
    }
};

//=====================位运算================
// bit_and
//进行逐位与的函数对象。相当于调用类型 T 上的 operator&
template<typename T>
struct bit_and
{
    T operator()(const T& lhs, const T& rhs) const
    {
        return lhs & rhs;
    }
};

// bit_or
//进行逐位或的函数对象。相当于在类型 T 上调用 operator|
template<typename T>
struct bit_or
{
    T operator()(const T& lhs, const T& rhs) const
    {
        return lhs | rhs;
    }
};

// bit_xor
//进行逐位异或的函数对象。相当于调用类型 T 上的 operator^
template<typename T>
struct bit_xor
{
    T operator()(const T& lhs, const T& rhs) const
    {
        return lhs ^ rhs;
    }
};

//C++ 14才有
// // bit_not
// //提供进行逐位非的函数对象。相当于调用类型 T 上的 operator~
// template<typename T>
// struct bit_not
// {
//     T operator()(const T& arg) const
//     {
//         return ~arg;
//     }
// };

//++++++++++here function + bind

template<typename>
class function;

template<typename R, typename... Args>
class function<R(Args...)>
{
    private:
        typedef R result_type;

    public:

};






#endif
