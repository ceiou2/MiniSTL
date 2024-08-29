// MiniFunctional.h
#pragma once
#ifndef MINI_FUNCTIONAL_H
#define MINI_FUNCTIONAL_H

#include <cstddef>
#include <memory>
#include <utility>

//===================算术运算模块================
// plus
//进行加法的函数对象。相当于在两个 T 类型的实例上调用 operator+
template<typename T>
struct plus
{
    T operator()(const T& lhs, const T& rhs) const
    {
        return lhs + rhs;
    }
};

// minus
//进行减法的函数对象。等效于在两个 T 类型实例上调用 operator-
template<typename T>
struct minus
{
    T operator()(const T& lhs, const T& rhs) const
    {
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
    bool operator()(const T& lhs, const T& rhs) const
    {
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
// logical_and
template<typename T>
struct logical_and
{
    bool operator()(const T& lhs, const T& rhs) const
    {
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

// C++ 14才有
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

//++++++++++here function + bind还没有完全实现

//=================function===============
// function类：用户API，通过接口类(type_earse)的指针添加、删除、调用容器类(Container)中储存的可调用对象
//主模板
//这里是function的声明，也就是泛化版本，下面的是模板特化，要现有泛化版本，才能特化，当然了。
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
        virtual R call(
                Args...) = 0; //用于调用容器类中的可调用对象，由容器类实现
    };

    //容器类：继承接口类，将实际的对象储存，为function提供真正的调用内容
    template<typename functor>
    class Container: public type_erase
    {
    private:
        functor f; //函数指针或者函数对象!!!!!!

    public:
        //构造函数，用于储存指向可调用对象的指针
        Container(functor fu): f(fu) {}

        R call(Args... args)
        {
            return f(args...);
        }

        //析构函数
        ~Container() {}
    };

    type_erase* funcPtr;

    //========================辅助函数模块==================
    // release
    //释放占有的资源
    void release()
    {
        if (funcPtr)
            delete funcPtr; //调用容器析构函数，而非原可调用对象析构函数
        funcPtr = nullptr;
    }

public:
    //构造函数
    function()
    {
        funcPtr = nullptr;
    }

    function(std::nullptr_t)
    {
        funcPtr = nullptr;
    }

    template<typename functor>
    function(functor&& f)
    {
        funcPtr = new Container<functor>(f);
    }

    template<typename functor>
    function(functor f)
    {
        funcPtr = new Container<functor>(f);
    }

    //复制构造函数：+++++++++++++++here目前是浅拷贝
    // function(function other)
    // {
    //     funcPtr = other.ptr;
    // }

    //移动构造函数
    function(function&& other)
    {
        funcPtr = other.funcPtr;
        other.funcPtr = nullptr; //置空防止析构时释放空间
    }

    //析构函数
    ~function()
    {
        if (funcPtr)
            delete funcPtr; //调用容器析构函数，而非原可调用对象析构函数
        funcPtr = nullptr;
    }

    //重载operator()运算符
    R operator()(Args... args) const
    {
        // return funcPtr->call(std::forward<Args>(args)...);
        return funcPtr->call(args...);
    }

    //重载operator=运算符+++++++++++++here目前是浅拷贝
    // function& operator=(function other)
    // {
    //     release();
    //     funcPtr = other.funcPtr;
    //     return *this;
    // }

    function& operator=(function&& other)
    {
        release();
        funcPtr = other.funcPtr;
        other.funcPtr = nullptr; //置空防止析构时释放空间
        return *this;
    }

    function& operator=(std::nullptr_t)
    {
        release(); //释放占有的资源
        funcPtr = nullptr;
        return *this;
    }

    template<typename functor>
    function& operator=(const functor& other_f)
    {
        release();
        funcPtr = new Container<functor>(other_f);
        return *this;
    }

    template<typename functor>
    function& operator=(functor&& other_f)
    {
        release();
        funcPtr = new Container<functor>(std::move(other_f));
        return *this;
    }

    // swap
    //交换*this 与 other 存储的可调用对象。
    void swap(function& other)
    {
        std::swap(funcPtr, other.funcPtr);
    }

    // operator bool
    operator bool() const
    {
        if (funcPtr) {
            return true;
        }
        return false;
    }
};

//========非成员函数模块==========
template<typename R, typename... Args>
void swap(function<R(Args...)> lhs, function<R(Args...)> rhs)
{
    lhs.swap(rhs);
}

template<typename R, typename... Args>
bool operator==(const function<R(Args...)>& f, nullptr_t)
{
    return f;
}

template<typename R, typename... Args>
bool operator==(nullptr_t, const function<R(Args...)>& f)
{
    return f;
}

template<typename R, typename... Args>
bool operator!=(const function<R(Args...)>& f, nullptr_t)
{
    return !f;
}

template<typename R, typename... Args>
bool operator!=(nullptr_t, const function<R(Args...)>& f)
{
    return !f;
}

#endif
