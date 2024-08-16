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
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef const T* const_pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference;

public:
    value_type array_container[Num ? Num : 1]; //可以处理0空间情况

    //前向声明
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;
    //======================迭代器模块===============
    class iterator
    {
    private:
        pointer p;

    public:
        //构造函数
        iterator(): p(nullptr) {}

        iterator(pointer in_p): p(in_p) {}

        iterator(const iterator& other): p(other.p) {}

        //重载*
        reference operator*()
        {
            return *p;
        }

        //重载=
        iterator& operator=(const iterator& other)
        {
            p = other.p;
            return *this;
        }

        //重载++
        iterator& operator++()
        {
            ++p;
            return *this;
        }

        //重载++(int)
        iterator operator++(int)
        {
            iterator res(p);
            ++p;
            return res;
        }

        //重载--
        iterator& operator--()
        {
            --p;
            return *this;
        }

        //重载--(int)
        iterator operator--(int)
        {
            iterator res(p);
            --p;
            return res;
        }

        //重载+
        iterator operator+(long int offset)
        {
            return iterator(p + offset);
        }

        //重载+=
        iterator& operator+=(long int offset)
        {
            p += offset;
            return *this;
        }

        //重载-
        iterator operator-(long int offset)
        {
            return iterator(p - offset);
        }

        //重载-=
        iterator& operator-=(long int offset)
        {
            p -= offset;
            return *this;
        }

        //重载==
        bool operator==(const iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const iterator& other) const
        {
            return p != other.p;
        }

        //重载==
        bool operator==(const const_iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const const_iterator& other) const
        {
            return p != other.p;
        }

        //计算迭代器之间的距离
        long int operator-(const iterator& other)
        {
            return (int)(p - other.p);
        }

        //友元声明
        friend class const_iterator;
        friend class vector;
    };
    class const_iterator
    {
    private:
        const_pointer p;

    public:
        //构造函数
        const_iterator(): p(nullptr) {}

        const_iterator(const_pointer in_p): p(in_p) {}

        const_iterator(const const_iterator& other): p(other.p) {}

        //重载*
        const_reference operator*()
        {
            return *p;
        }

        //重载=
        const_iterator& operator=(const const_iterator& other)
        {
            p = other.p;
            return *this;
        }

        //重载++
        const_iterator& operator++()
        {
            ++p;
            return *this;
        }

        //重载++(int)
        const_iterator operator++(int)
        {
            const_iterator res(p);
            ++p;
            return res;
        }

        //重载--
        const_iterator& operator--()
        {
            --p;
            return *this;
        }

        //重载--(int)
        const_iterator operator--(int)
        {
            const_iterator res(p);
            --p;
            return res;
        }

        //重载+
        const_iterator operator+(long int offset)
        {
            return const_iterator(p + offset);
        }

        //重载+=
        const_iterator& operator+=(long int offset)
        {
            p += offset;
            return *this;
        }

        //重载-
        const_iterator operator-(long int offset)
        {
            return const_iterator(p - offset);
        }

        //重载-=
        const_iterator& operator-=(long int offset)
        {
            p -= offset;
            return *this;
        }

        //重载==
        bool operator==(const iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const iterator& other) const
        {
            return p != other.p;
        }

        //重载==
        bool operator==(const const_iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const const_iterator& other) const
        {
            return p != other.p;
        }

        //计算迭代器之间的距离
        long int operator-(const const_iterator& other)
        {
            return (int)(p - other.p);
        }

        //友元声明
        friend class iterator;
        friend class vector;
    };
    class reverse_iterator
    {
    private:
        pointer p;

    public:
        //构造函数
        reverse_iterator(): p(nullptr) {}

        reverse_iterator(pointer in_p): p(in_p) {}

        reverse_iterator(const reverse_iterator& other): p(other.p) {}

        //重载*
        reference operator*()
        {
            return *p;
        }

        //重载=
        reverse_iterator& operator=(const reverse_iterator& other)
        {
            p = other.p;
            return *this;
        }

        //重载++
        reverse_iterator& operator++()
        {
            --p;
            return *this;
        }

        //重载++(int)
        reverse_iterator operator++(int)
        {
            reverse_iterator res(p);
            --p;
            return res;
        }

        //重载--
        reverse_iterator& operator--()
        {
            ++p;
            return *this;
        }

        //重载--(int)
        reverse_iterator operator--(int)
        {
            reverse_iterator res(p);
            ++p;
            return res;
        }

        //重载+
        reverse_iterator operator+(long int offset)
        {
            return reverse_iterator(p - offset);
        }

        //重载+=
        reverse_iterator& operator+=(long int offset)
        {
            p -= offset;
            return *this;
        }

        //重载-
        reverse_iterator operator-(long int offset)
        {
            return reverse_iterator(p + offset);
        }

        //重载-=
        reverse_iterator& operator-=(long int offset)
        {
            p += offset;
            return *this;
        }

        //重载==
        bool operator==(const reverse_iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const reverse_iterator& other) const
        {
            return p != other.p;
        }

        //重载==
        bool operator==(const const_reverse_iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const const_reverse_iterator& other) const
        {
            return p != other.p;
        }

        //计算迭代器之间的距离
        long int operator-(const reverse_iterator& other)
        {
            return (int)(other.p - p);
        }

        //友元声明
        friend class const_reverse_iterator;
        friend class vector;
    };

    class const_reverse_iterator
    {
    private:
        const_pointer p;

    public:
        //构造函数
        const_reverse_iterator(): p(nullptr) {}

        const_reverse_iterator(const_pointer in_p): p(in_p) {}

        const_reverse_iterator(const const_reverse_iterator& other): p(other.p)
        {
        }

        //重载*
        const_reference operator*()
        {
            return *p;
        }

        //重载=
        const_reverse_iterator& operator=(const const_reverse_iterator& other)
        {
            p = other.p;
            return *this;
        }

        //重载++
        const_reverse_iterator& operator++()
        {
            --p;
            return *this;
        }

        //重载++(int)
        const_reverse_iterator operator++(int)
        {
            const_reverse_iterator res(p);
            --p;
            return res;
        }

        //重载--
        const_reverse_iterator& operator--()
        {
            ++p;
            return *this;
        }

        //重载--(int)
        const_reverse_iterator operator--(int)
        {
            const_reverse_iterator res(p);
            ++p;
            return res;
        }

        //重载+
        const_reverse_iterator operator+(long int offset)
        {
            return const_reverse_iterator(p - offset);
        }

        //重载+=
        const_reverse_iterator& operator+=(long int offset)
        {
            p -= offset;
            return *this;
        }

        //重载-
        const_reverse_iterator operator-(long int offset)
        {
            return const_reverse_iterator(p + offset);
        }

        //重载-=
        const_reverse_iterator& operator-=(long int offset)
        {
            p += offset;
            return *this;
        }

        //重载==
        bool operator==(const reverse_iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const reverse_iterator& other) const
        {
            return p != other.p;
        }

        //重载==
        bool operator==(const const_reverse_iterator& other) const
        {
            return p == other.p;
        }

        //重载!-
        bool operator!=(const const_reverse_iterator& other) const
        {
            return p != other.p;
        }

        //计算迭代器之间的距离
        long int operator-(const const_reverse_iterator& other)
        {
            return (int)(other.p - p);
        }

        //友元声明
        friend class reverse_iterator;
        friend class vector;
    };
    //====================迭代器模块====================
    //获取首部迭代器
    iterator begin()
    {
        return &array_container[0];
    }

    const_iterator begin() const
    {
        return array_container;
    }

    const_iterator cbegin()
    {
        return array_container;
    }

    //获取尾部迭代器
    iterator end()
    {
        return &array_container[Num];
    }

    const_iterator end() const
    {
        return array_container;
    }

    const_iterator cend()
    {
        return array_container;
    }

    //获取反向首部迭代器
    reverse_iterator rbegin()
    {
        return &array_container[Num - 1];
    }

    const_reverse_iterator rbegin() const
    {
        return &array_container[Num - 1];
    }

    const_reverse_iterator crbegin()
    {
        return &array_container[Num - 1];
    }

    reverse_iterator rend()
    {
        return &array_container[0] - 1;
    }

    const_reverse_iterator rend() const
    {
        return &array_container[0] - 1;
    }

    const_reverse_iterator crend()
    {
        return &array_container[0] - 1;
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

    const_pointer data() const
    {
        return array_container;
    }

    //---------容量模块----------
    // empty()
    [[nodiscard]] constexpr bool empty() const
    {
        return Num == 0;
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
            std::swap(array_container[i], other[i]);
        }
    }
};

//---------非成员函数模块----------
template<typename T, size_t N>
bool operator==(const array<T, N>& lhs, const array<T, N>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template<typename T, size_t N>
bool operator!=(const array<T, N>& lhs, const array<T, N>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, size_t N>
bool operator<(const array<T, N>& lhs, const array<T, N>& rhs)
{
    size_t i = 0;
    while (i < lhs.size() && i < rhs.size()) {
        if (lhs[i] < rhs[i]) {
            return true;
        } else if (lhs[i] > rhs[i]) {
            return false;
        }
        ++i;
    }
    return (lhs.size() < rhs.size());
}

template<typename T, size_t N>
bool operator<=(const array<T, N>& lhs, const array<T, N>& rhs)
{
    return (lhs < rhs || lhs == rhs);
}

template<typename T, size_t N>
bool operator>(const array<T, N>& lhs, const array<T, N>& rhs)
{
    return !(lhs < rhs || lhs == rhs);
}

template<typename T, size_t N>
bool operator>=(const array<T, N>& lhs, const array<T, N>& rhs)
{
    return !(lhs < rhs);
}

//特化swap算法
template<typename T, size_t N>
void swap(array<T, N>& lhs, array<T, N>& rhs)
{
    lhs.swap(rhs);
}

#endif
