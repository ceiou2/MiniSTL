//MiniFunctional.h
#pragma once
#ifndef MINI_FUNCTIONAL_H
#define MINI_FUNCTIONAL_H

#include<cstddef>
#include<typeindex>
#include<typeinfo>
#include<memory>
#include<utility>


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

//++++++++++here function + bind，function还没有完全实现

//类模板声明
// template<typename>
// class function;

// template<typename R, typename... Args>
// class function<R(Args...)>//函数签名
// {
//     private:
//         using result_type = R;
//         using FuncPtr = R (*)(Args...);

//         FuncPtr functionPtr;

//     public:
//         // 默认构造函数
//         function() = default;

//         //构造函数接受一个函数指针
//         function(FuncPtr ptr):functionPtr(ptr){}

//         //重载调用操作符
//         result_type operator()(Args... args){
//             return (*functionPtr)(std::forward<Args>(args)...);
//         }
// };

//=================function===============
//function类：用户API，通过接口类(type_earse)的指针添加、删除、调用容器类(Container)中储存的可调用对象
//主模板+++++++++++++++++++++++++here暂时没清楚其原理，不加这个会报错说主模板错误，按部就班抄csdn上的解决办法
template<typename>
class function;

template<typename R, typename... Args>
class function<R(Args...)>
{
private:
    //接口类：其指针储存在function类中，利用虚基类的动态联编特性为function提供类型擦除模块
    class type_erase
    {
    public:
        virtual ~type_erase() {}
        virtual R call(Args...) = 0;//用于调用容器类中的可调用对象，由容器类实现
    };

    //容器类：继承接口类，将实际的对象储存，为function提供真正的调用内容
    template<typename functor>
    class Container: public type_erase
    {
    private:
        functor RealPtr;//函数指针或者函数对象!!!!!!

    public:
        //构造函数，用于储存指向可调用对象的指针
        Container(functor funcptr)
        {
            RealPtr = funcptr;
        }

        R call(Args... args){
            //return (*RealPtr)(std::forward(args)...);
            return RealPtr(args...);
        }

        //析构函数
        ~Container(){}
    };

    type_erase* funcPtr;

public:
    template<typename functor>
    function(functor f){
        funcPtr = (new Container<functor>(f));
    }

    // ~function(){
    //     if(funcPtr)
    //         delete funcPtr;//调用容器析构函数，而非原可调用对象析构函数
    //     funcPtr = nullptr;
    // }

    R operator()(Args... args){
        //return funcPtr->call(std::forward<Args>(args)...);
        return funcPtr->call(args...);
    }
};

#endif
