//MiniString.h
#pragma once
#ifndef MINI_STRING_H
#define MINI_STRING_H

#include<cstddef>

class string{
private:
    typedef char value_type;
    typedef value_type* pointer;
    typedef const char* const_pointer;
    typedef value_type& reference;
    typedef const char& const_reference;
    typedef size_t size_type;

private:
    pointer start;
    pointer finish;
    pointer end_of_storage;

public:
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
        friend class string;
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
        friend class string;
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
        friend class string;
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
        friend class string;
    };
    // begin():获取第一个元素的迭代器
    iterator begin()
    {
        return iterator(start);
    }

    const_iterator begin() const
    {
        return const_iterator(start);
    }

    const_iterator cbegin() const
    {
        return const_iterator(start);
    }

    // end()::获取string最后一个元素的下一个位置的迭代器
    iterator end()
    {
        return iterator(finish);
    }

    const_iterator end() const
    {
        return const_iterator(finish);
    }

    const_iterator cend() const
    {
        return const_iterator(finish);
    }

    // reverse begin
    reverse_iterator rbegin()
    {
        return reverse_iterator(finish - 1);
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(finish - 1);
    }

    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(finish - 1);
    }

    // rend
    reverse_iterator rend()
    {
        return reverse_iterator(start - 1);
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(start - 1);
    }

    const_reverse_iterator crend() const
    {
        return const_reverse_iterator(start - 1);
    }
    //==============元素访问模块===============
    // at:有边界检查访问
    reference at(size_type n)
    {
        if (n >= size()) {
            throw std::out_of_range("out of range");
        }
        return *(begin() + n);
    }

    const_reference at(size_type n) const
    {
        if (n >= size()) {
            throw std::out_of_range("out of range");
        }
        return *(begin() + n);
    }

    // operator[]:随机访问
    reference operator[](size_type n)
    {
        return *(begin() + n);
    }

    // operator[]:const版本
    const_reference operator[](size_type n) const
    {
        return *(begin() + n);
    }

    reference front()
    {
        return *begin();
    } //第一个元素

    reference back()
    {
        return *(end() - 1);
    } //最后一个元素

    //-------------容量模块-----------
    // size():获取元素数量
    size_type size() const
    {
        return size_type(end() - begin());
    }

    // capacity():获取容器容量
    size_type capacity() const
    {
        return size_type(end_of_storage - (begin()).p);
    }

    // empty():string是否为空
    bool empty() const
    {
        return begin() == end();
    }

    // reserve:分配新空间并转移
    void reserve(size_type new_cap)
    {
        //开辟空间
        pointer tmp_pointer = new value_type[new_cap];

        size_type _size =
                size(); // 因为size()通过finish-start计算，但届时将改变该两指针的指向

        //转移数据
        if (start) {
            for (size_type i = 0; i < _size; ++i) {
                tmp_pointer[i] = start[i];
            }

            // release
            delete[] start;
        }
        start = tmp_pointer;
        finish = start + _size;
        end_of_storage = start + new_cap;
    }

    //-------------功能函数模块-----------

    // fill_initialize(size_type n,const char& value);
    void fill_initialize(size_type n, const char& value)
    {
        reserve(n);
        finish = start + n; // set size
        for (size_type i = 0; i < size(); ++i) {
            start[i] = value;
        }
    }

    // release():释放空间
    void release()
    {
        delete[] start;
        start = nullptr;
        finish = nullptr;
        end_of_storage = nullptr;
    }

    // fore_move():元素向前移动
    void fore_move(iterator position)
    {
        if (position == end())
            return;
        while (position + 1 != end()) {
            *position = *(position + 1);
            ++position;
        }
    }

    // back_move():元素向后移动一位
    void back_move(iterator position)
    {
        if (position == end())
            return;
        for (iterator it = end() - 1; it != position; --it) {
            if (it == begin())
                return;
            *it = *(it - 1);
        }
    }

    //-------------构造函数模块-----------
    //默认构造函数
    string(): start(0), finish(0), end_of_storage(0){};

    // string(size_type n,const char& value);
    string(size_type n, const char& value): start(0), finish(0), end_of_storage(0)
    {
        fill_initialize(n, value);
    }

    // string(int n,const char&
    // value)注：官方文档有这两个函数，但是size_type应该够用，暂时不知道这两个函数的定义有什么作用
    // string(long n,const char& value)

    //列表初始化
    string(std::initializer_list<char> init_list)
        : start(0),
          finish(0),
          end_of_storage(0)
    {
        // reserve(init_list.end()-init_list.begin());
        // std::copy(init_list.begin(),init_list.end(),start);
        // release();
        reserve(init_list.end() - init_list.begin());
        for (size_type i = 0; i < init_list.end() - init_list.begin(); ++i) {
            *(start + i) = *(init_list.begin() + i);
            ++finish;
        }
    }

    //拷贝构造函数:深拷贝版本
    string(const string& ori_string): start(0), finish(0), end_of_storage(0)
    {
        reserve(ori_string.capacity());
        for (size_type i = 0; i < ori_string.size(); ++i) {
            *(start + i) = *(ori_string.begin() + i);
            ++finish;
        }
    }

    //移动构造函数
    string(string&& ori_string)
    {
        start = (ori_string.begin()).p;
        finish = (ori_string.end()).p;
        end_of_storage = start + ori_string.capacity();

        ori_string.start = nullptr; //右值中指针置空防止析构时delete掉内存
        ori_string.finish = nullptr;
        ori_string.end_of_storage = nullptr;
    }

    //拷贝赋值函数
    string& operator=(const string& ori_string)
    {
        release();
        reserve(ori_string.capacity());
        for (size_type i = 0; i < ori_string.size(); ++i) {
            *(start + i) = *(ori_string.begin() + i);
            ++finish;
        }
        return *this; //返回自身的引用以支持链式赋值
    }

    //移动赋值函数
    string& operator=(string&& ori_string)
    {
        release();
        start = ori_string.begin().p;
        finish = ori_string.end().p;
        end_of_storage = start + ori_string.capacity();

        ori_string.start = nullptr; //右值中指针置空防止析构时delete掉内存
        ori_string.finish = nullptr;
        ori_string.end_of_storage = nullptr;

        return *this; //返回自身的引用以支持链式赋值
    }

    // string(size_type n);
    explicit string(size_type n): start(0), finish(0), end_of_storage(0)
    {
        fill_initialize(n, char());
    }

    //~string()
    ~string()
    {
        release();
    }

    void swap(string& other);

    //-------------操作函数模块-----------
    void push_back(const char& x)
    { //将元素插入尾端
        if (finish != end_of_storage) {
            *finish = x;
            ++finish;
        } else {
            reserve((capacity() == 0)
                            ? 1
                            : 2 * capacity()); //空间分配，1或原空间翻倍
            push_back(x);
        }
    }

    void pop_back()
    { //移除尾端元素
        --finish;
    }

    iterator erase(iterator position)
    { //清除某位置上的元素
        if (position + 1 != end()) {
            fore_move(position); //后续元素向前移动
        }
        --finish;
        return position;
    }

    iterator erase(iterator begin, iterator end)
    {
        while (begin != end) {
            erase(begin);
            --end;
        }
        return begin;
    }

    iterator insert(iterator position, const char& x)
    { //在迭代器位置插入值，返回插入位置的迭代器
        if (finish != end_of_storage) {
            ++finish;
            back_move(position);
            *position = x;
        } else {
            size_type tmp_size = size_type(position - start); //处理position失效
            reserve((capacity() == 0)
                            ? 1
                            : 2 * capacity()); //空间分配，1或原空间翻倍
            return insert(start + tmp_size, x);
        }
        return position;
    }

    //写一个move版本的insert规避迭代器失效

    void resize(size_type new_size, const char& x) //改变元素数量
    {
        if (new_size <= size()) {
            finish = start + new_size;
        } else {
            reserve(new_size);
            while (finish != start + new_size) {
                *finish = x;
                ++finish;
            }
        }
    }

    void resize(size_type new_size)
    {
        resize(new_size, char());
    } //重载

    void clear()
    {
        finish = start;
    }

    // assign
    void assign(size_type count, const char& value) //以count份 value的副本替换内容
    {
        *this = string(count, value);
    }

    void
    assign(const_iterator first,
           const_iterator
                   last) //将区间[fast,last)的元素赋值到当前string容器中，原内容释放，其中有任何一个实参是指向*this中的迭代器时行为未定义
    {
        release();
        reserve(last - first);
        for (size_type i = 0; i < last - first; ++i) {
            *(start + i) = *(first + i);
            ++finish;
        }
    }

    //上面的所以成员函数与vector<char>特化相同，以下是string特有功能函数的补充
    //=================string 特有功能函数===================
    //------------------元素访问模块-------------------
    //返回指向用作字符存储的底层数组的指针。
    const char* data()const{
        return start;
    }

    //返回指向拥有数据等价于存储于字符串中的空终止字符数组的指针。
    const char* c_str()const{
        const size_type s = size();
//start here++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }
};

void swap(string& lhs, string& rhs);

bool operator==(const string& lhs, const string& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (auto i = 0; i <= lhs.size(); ++i) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

bool operator!=(const string& lhs, const string& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const string& lhs, const string& rhs)
{
    auto lit = lhs.begin();
    auto rit = rhs.begin();
    while (lit != lhs.end() || rit != rhs.end()) {
        if (lit == lhs.end()) {
            return true;
        } else if (rit == rhs.end()) {
            return false;
        }
        if (*lit < *rit) {
            return true;
        } else if (*lit > *rit) {
            return false;
        }
        ++lit;
        ++rit;
    }
    return false;
}

bool operator<=(const string& lhs, const string& rhs)
{
    return (lhs == rhs || lhs < rhs);
}

bool operator>(const string& lhs, const string& rhs)
{
    return !(lhs == rhs || lhs < rhs);
}

bool operator>=(const string& lhs, const string& rhs)
{
    return (lhs == rhs || lhs > rhs);
}

void swap(string& lhs, string& rhs)
{
    if (lhs == rhs)
        return;
    lhs.swap(rhs);
}

void string::swap(string& other)
{
    if (*this == other)
        return;

    std::swap(this->start, other.start);
    std::swap(this->finish, other.finish);
    std::swap(this->end_of_storage, other.end_of_storage);
}

#endif
