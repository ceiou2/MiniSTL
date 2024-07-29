// MiniDeque.h
#pragma once
#ifndef MINI_DEQUE_H
#define MINI_DEQUE_H

#define buffer_size 128

#include <cstddef>
#include<type_traits>
#include "MiniVector.h"

template<typename T>
class deque
{
private:
    typedef T value_type;
    typedef value_type* pointer;
    typedef T** map_pointer; //指向map元素的二级指针
    typedef T& reference;
    typedef const T& const_reference;//为什么typedef const reference const_reference不行？
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* buffer;

public:
    //==============================迭代器模块=======================
    class iterator
    {
    public:
        T* cur;
        T* first;
        T* last;
        map_pointer node;

        //构造函数
        iterator()
        {
            cur = nullptr;
            first = nullptr;
            last = nullptr;
            node = nullptr;
        }

        iterator(const T* c,const T* f,const T* l, map_pointer n){
            cur = const_cast<T*>(c);//确保安全的情况下移除const限定符
            first = const_cast<T*>(f);
            last = const_cast<T*>(l);
            node = n;
        };

        iterator(const iterator& other){
            cur = other.cur;
            first = other.first;
            last = other.last;
            node = other.node;
        }


        //重载*运算符
        T& operator*() const
        {
            return *cur;
        }

        //辅助函数
        void set_node(map_pointer newNode)
        {
            node = newNode;
            first = *newNode;
            last = first + buffer_size;
        }

        //重载前置递增
        iterator& operator++()
        {
            ++cur;
            if (cur == last) // cur走到了最后一个元素的下一个位置
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        //重载后置递增
        iterator operator++(int)
        {
            iterator temp = *this;
            ++*this;
            return temp;
        }

        //重载前置递减
        iterator& operator--()
        {
            if (cur == first) // cur移动到上一个buffer情况
            {
                set_node(node - 1);
                cur = last - 1;
            }
            --cur;
            return *this;
        }

        //重载后置递减
        iterator operator--(int)
        {
            iterator temp = *this;
            --*this;
            return temp;
        }

        //override operator+=
        iterator& operator+=(long int m){
            if(m>0){
                while(m--){
                    ++*this;
                }
            }
            else if(m<0){
                while(m++){
                    --*this;
                }
            }
            return *this;
        }

        //override operator-=
        iterator& operator-=(long int m){
            *this += -m;
            return *this;
        }

        //重载随机访问+
        iterator operator+(int n)
        {
            iterator res = *this;
            while (n--) {
                ++res;
            }
            return res;
        }

        //重载随机访问-
        iterator operator-(int n)
        {
            iterator res = *this;
            while (n--) {
                --res;
            }
            return res;
        }

        //重载等于运算符
        bool operator==(const iterator& other) const
        {
            return (cur == other.cur && first == other.first &&
                    last == other.last && node == other.node);
        }

        //重载不等运算符
        bool operator!=(const iterator& other) const{
            return !(*this == other);
        }

        //重载赋值运算符
        iterator& operator=(const iterator& other){
            cur = other.cur;
            first = other.first;
            last = other.last;
            node = other.node;
            return *this;
        }

        //移动赋值运算符
        //iterator& operator=(iterator&& other);

    };

    class const_iterator
    {
    public:
        const T* cur;
        const T* first;
        const T* last;
        map_pointer node;

        //构造函数
        const_iterator()
        {
            cur = nullptr;
            first = nullptr;
            last = nullptr;
            node = nullptr;
        }

        const_iterator(T* c, T* f, T* l, map_pointer n)
            : cur(c),
              first(f),
              last(l),
              node(n){};

        const_iterator(iterator i){
            cur = i.cur;
            first = i.first;
            last = i.last;
            node = i.node;
        }
        //重载*运算符
        const_reference operator*() const
        {
            return *cur;
        }

        //辅助函数
        void set_node(map_pointer newNode)
        {
            node = newNode;
            first = *newNode;
            last = first + buffer_size;
        }

        //重载前置递增
        const_iterator& operator++()
        {
            ++cur;
            if (cur == last) // cur走到了最后一个元素的下一个位置
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        //重载后置递增
        const_iterator operator++(int)
        {
            const_iterator temp = *this;
            ++*this;
            return temp;
        }

        //重载前置递减
        const_iterator& operator--()
        {
            if (cur == first) // cur移动到上一个buffer情况
            {
                set_node(node - 1);
                cur = last - 1;
            }
            --cur;
            return *this;
        }

        //重载后置递减
        const_iterator operator--(int)
        {
            const_iterator temp = *this;
            --*this;
            return temp;
        }

        //重载随机访问+
        const_iterator operator+(int n)
        {
            const_iterator res = *this;
            while (n--) {
                ++res;
            }
            return res;
        }

        //重载随机访问-
        const_iterator operator-(int n)
        {
            const_iterator res = *this;
            while (n--) {
                --res;
            }
            return res;
        }

        //重载等于运算符
        bool operator==(const const_iterator& other) const
        {
            return (cur == other.cur && cur == other.cur &&
                    last == other.last && node == other.node);
        }

        //重载不等运算符
        bool operator!=(const const_iterator& other) const
        {
            return !(*this == other);
        }

        //重载赋值运算符
        const_iterator& operator=(const const_iterator& other)
        {
            cur = other.cur;
            first = other.first;
            last = other.last;
            node = other.node;
            return *this;
        }
    };

    class reverse_iterator
    {
    public:
        T* cur;
        T* first;
        T* last;
        map_pointer node;

        //构造函数
        reverse_iterator()
        {
            cur = nullptr;
            first = nullptr;
            last = nullptr;
            node = nullptr;
        }

        reverse_iterator(T* c, T* f, T* l, map_pointer n)
            : cur(c),
              first(f),
              last(l),
              node(n){};

        reverse_iterator(const iterator& it)
        {
            cur = it.cur;
            first = it.first;
            last = it.last;
            node = it.node;
        }

        //重载*运算符
        reference operator*() const
        {
            return *cur;
        }

        //辅助函数
        void set_node(map_pointer newNode)
        {
            node = newNode;
            first = *newNode;
            last = first + buffer_size;
        }

        //重载前置递增
        reverse_iterator& operator++()
        {
            if (cur == first) // cur移动到上一个buffer情况
            {
                set_node(node - 1);
                cur = last - 1;
            }
            --cur;
            return *this;
        }

        //重载后置递增
        reverse_iterator operator++(int)
        {
            reverse_iterator temp = *this;
            --*this;
            return temp;
        }

        //重载前置递减
        reverse_iterator& operator--()
        {
            ++cur;
            if (cur == last) // cur走到了最后一个元素的下一个位置
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        //重载后置递减
        reverse_iterator operator--(int)
        {
            reverse_iterator temp = *this;
            ++*this;
            return temp;
        }

        //重载随机访问+
        reverse_iterator operator+(int n)
        {
            reverse_iterator res = *this;
            while (n--) {
                --res;
            }
            return res;
        }

        //重载随机访问-
        reverse_iterator operator-(int n)
        {
            reverse_iterator res = *this;
            while (n--) {
                ++res;
            }
            return res;
        }

        //重载等于运算符
        bool operator==(const reverse_iterator& other) const
        {
            return (cur == other.cur && cur == other.cur &&
                    last == other.last && node == other.node);
        }

        //重载不等运算符
        bool operator!=(const reverse_iterator& other) const
        {
            return !(*this == other);
        }

        //重载赋值运算符
        reverse_iterator& operator=(const reverse_iterator& other)
        {
            cur = other.cur;
            first = other.first;
            last = other.last;
            node = other.node;
            return *this;
        }
    };

    class const_reverse_iterator
    {
    public:
        const T* cur;
        const T* first;
        const T* last;
        map_pointer node;

        //构造函数
        const_reverse_iterator()
        {
            cur = nullptr;
            first = nullptr;
            last = nullptr;
            node = nullptr;
        }

        const_reverse_iterator(T* c, T* f, T* l, map_pointer n)
            : cur(c),
              first(f),
              last(l),
              node(n){};

        const_reverse_iterator(const iterator it)
        {
            cur = it.cur;
            first = it.first;
            last = it.last;
            node = it.node;
        }
        //重载*运算符
        const_reference operator*() const
        {
            return *cur;
        }

        //辅助函数
        void set_node(map_pointer newNode)
        {
            node = newNode;
            first = *newNode;
            last = first + buffer_size;
        }

        //重载前置递增
        const_reverse_iterator& operator++()
        {
            if (cur == first) // cur移动到上一个buffer情况
            {
                set_node(node - 1);
                cur = last - 1;
            }
            --cur;
            return *this;
        }

        //重载后置递增
        const_reverse_iterator operator++(int)
        {
            const_reverse_iterator temp = *this;
            --*this;
            return temp;
        }

        //重载前置递减
        const_reverse_iterator& operator--()
        {
            ++cur;
            if (cur == last) // cur走到了最后一个元素的下一个位置
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        //重载后置递减
        const_reverse_iterator operator--(int)
        {
            reverse_iterator temp = *this;
            ++*this;
            return temp;
        }

        //重载随机访问+
        const_reverse_iterator operator+(int n)
        {
            const_reverse_iterator res = *this;
            while (n--) {
                --res;
            }
            return res;
        }

        //重载随机访问-
        const_reverse_iterator operator-(int n)
        {
            reverse_iterator res = *this;
            while (n--) {
                ++res;
            }
            return res;
        }

        //重载等于运算符
        bool operator==(const const_reverse_iterator& other) const
        {
            return (cur == other.cur && cur == other.cur &&
                    last == other.last && node == other.node);
        }

        //重载不等运算符
        bool operator!=(const const_reverse_iterator& other) const
        {
            return !(*this == other);
        }

        //重载赋值运算符
        const_reverse_iterator& operator=(const const_reverse_iterator& other)
        {
            cur = other.cur;
            first = other.first;
            last = other.last;
            node = other.node;
            return *this;
        }
    };

    //----------迭代器功能函数-------------
    iterator begin()
    {
        return start;
    }

    const_iterator begin() const
    {
        return start;
    }

    const_iterator cbegin() const
    {
        return start;
    }

    iterator end()
    {
        return finish;
    }

    const_iterator end() const
    {
        return finish;
    }

    const_iterator cend() const
    {
        return finish;
    }

    reverse_iterator rbegin()
    {
        return finish - 1;
    }

    const_reverse_iterator rbegin() const
    {
        return finish - 1;
    }

    const_reverse_iterator crbegin() const
    {
        return finish - 1;
    }

    reverse_iterator rend()
    {
        return start - 1;
    }

    const_reverse_iterator rend() const
    {
        return start - 1;
    }

    const_reverse_iterator crend() const
    {
        return start - 1;
    }


    //=============================成员变量模块=======================

    vector<T*>	map;
    iterator	start; //指向第一个map节点
    iterator	finish; //指向最后一个map节点,finish.cur指向最后一个元素的下一个位置

    private:
    //===============================辅助函数模块=====================
    void add_buffer_back()
    { //尾部添加一个buffer，finish.cur指向新buffer末尾，空但将分配value,cur后移(因为最后元素的下一个位置)
        buffer buff = new T[buffer_size];
        map.push_back(buff);
        // init finish
        finish.cur = buff;   //最后一个元素的下一个位置
        finish.first = buff; // buffer第一个位置
        finish.last = buff + buffer_size; // buffer尾部的下一个位置
        //bug here ++(finish.node);

        finish.node = &map[map.size() - 1];

        //!!!!!!!!!只要存在map的增减，就要重新定义start和finish，防止map改变使得iterator失效
        //init start
        size_type diff = start.cur - start.first;
        start.node = &map[0];
        start.first = map[0];
        start.last = map[0] + buffer_size;
        start.cur = start.first + diff;
    }

    void add_buffer_front()
    { //头部添加一个buffer,start.cur指向新buffer末尾，空但将分配value，cur不移(指向第一个元素)
        buffer buff = new T[buffer_size];
        start.node = map.insert(
                map.begin(),
                buff); // map头部插入添加,返回T**指向map头：等价于start.node=map;
        // init start
        start.first = buff;
        start.last = buff + buffer_size;
        start.cur = (start.last) - 1;

        //init finish :debugged 这里可能会导致map重新分配空间，start和finish的地址都要更新
        size_type diff = finish.last - finish.cur;
        finish.node = &map[map.size() - 1];
        finish.first = map[map.size() - 1];
        finish.last = map[map.size() - 1] + buffer_size;
        finish.cur = finish.last - diff;
    }

    void _push_back(const T& value)
    {
        if (map.size() == 0) { //处理空deque情况
            buffer buff = new T[buffer_size];
            map.push_back(buff);

            // init start
            start.cur = buff; //第一个元素的位置
            start.first = buff;
            start.last = buff + buffer_size; // buffer尾部的下一个位置
            start.node = &map[0];

            // init finish
            finish.cur = buff + 1; //最后一个元素的下一个位置
            finish.first = buff;
            finish.last = buff + buffer_size; // buffer尾部
            finish.node = &map[0];

            //赋值
            *(buff + 0) = value;

            return;
        } else if (
                finish.cur ==
                finish.last) { //尾部满了需要在尾部新添加一个buffer的情况
            add_buffer_back();   //添加尾部一个buffer
            *finish = value; //赋值
            ++(finish.cur);     //++末尾
            return;
        } else {
            *finish = value;
            ++(finish.cur);
            return;
        }
    }

    void _push_front(const T& value)
    {
        if (map.size() == 0) { //处理空deque情况
            buffer buff = new T[buffer_size];
            map.push_back(buff);

            // init start
            start.cur = buff; //第一个元素的位置
            start.first = buff;
            start.last = buff + buffer_size; // buffer尾部的下一个位置
            start.node = &map[0];

            // init finish
            finish.cur = buff + 1; //最后一个元素的下一个位置
            finish.first = buff;
            finish.last = buff + buffer_size; // buffer尾部
            finish.node = &map[0];

            //赋值
            *(buff + 0) = value;

            return;
        } else if (
                start.cur ==
                start.first) { //头部满了需要在头部新添加一个buffer的情况
            add_buffer_front(); //添加头部一个buffer
            *start = value; //赋值
            return;
        } else {
            *start = value;
            return;
        }
    }

    //释放空间，清空deque
    void release()
    {
        for (size_type i = 0; i < map.size(); ++i) { //释放buffer
            delete map[i];
            map[i] = nullptr;
        }
        map.clear();
        start.cur = nullptr;
        finish.cur = nullptr;
    }

    // map移动后start和finish的node要重新初始化
    void resetNode_start_finish()
    {
        if (!map.size()) {
            start = nullptr;
            finish = nullptr;
            return;
        }
        start.node = map;
        finish.node = map[map.size() - 1];
    }

    //swap iterator
    void swap(iterator& lhs,iterator& rhs){
        std::swap(lhs.cur, rhs.cur);
        std::swap(lhs.first, rhs.first);
        std::swap(lhs.last, rhs.last);
        std::swap(lhs.node, rhs.node);
    }


public:
    //***************************************************************
    //==============================成员函数模块=======================

    //构造函数
    //默认构造函数
    deque()
    {
        map.clear();
        start = iterator();
        finish = iterator();
    }

    deque(size_type count, const T& value = T())
    {
        while (count--) {
            _push_back(value);
        }
    }

    //here
    deque(int count, int value)
    {
        if (count <= 0)
            return;
        while (count--) {
            _push_back(value);
        }
    }

    //构造[first,last)内容的容器
    template<typename InputIt>
    deque(InputIt firstIt, InputIt lastIt)
    {
        while (firstIt != lastIt) {
            _push_back(*firstIt);
            ++firstIt;
        }
    }

    //复制构造函数
    deque(const deque& other)
    {
        for (auto it = other.begin(); it != other.end(); ++it) {
            _push_back(*it);
        }
    }

    //移动构造函数
    deque(deque&& other)
    {
        this->map = other.map;
        other.map.clear();
    }

    //列表初始化构造
    deque(std::initializer_list<T> init)
    {
        for (auto it = init.begin(); it != init.end(); ++it) {
            _push_back(*it);
        }
    }

    //析构函数
    ~deque()
    {
        release();
    }

    //赋值函数
    //拷贝赋值运算符
    deque& operator=(const deque& other)
    {
        release(); //释放原空间
        for (auto it = other.begin(); it != other.end(); ++it) {
            _push_back(*it);
        }
        return *this;
    }

    //移动赋值运算符
    deque& operator=(deque&& other)
    {
        release(); //释放原空间
        this->map = other.map;
        other.map.clear();
        return *this;
    }

    //将值赋给容器
    //以count份value的副本替换内容
    void assign(size_type count, const T& value)
    {
        release();
        while (count--) {
            _push_back(value);
        }
    }

//here
    void assign(int count, int value)
    {
        if(count<=0)
        return;
        assign(size_type(count), value);
    }

    //以范围 [first, last) 中元素的副本替换内容。
    template<typename InputIt>
    void assign(InputIt first, InputIt last)
    {
        release();
        while (first != last) {
            _push_back(*first);
            ++first;
        }
    }

    //以来自 initializer_list ilist 的元素替换内容。
    void assign(std::initializer_list<T> init)
    {
        release();
        for (auto it = init.begin(); it != init.end(); ++it) {
            _push_back(*it);
        }
    }

    //返回位于指定位置 pos 的元素的引用，有边界检查。
    //若 pos 不在容器范围内，则抛出 std::out_of_range 类型的异常。
    reference at(size_type pos)
    {
        size_type map_offset =
                pos / buffer_size; // map偏移量（也是buffer组偏移量）
        size_type buffer_offset = pos % buffer_size; // buffer元素偏移量

        size_type last_elem_offset =
                0; //最后一个元素的下一个位置在最后一个buffer的偏移量
        for (pointer p = finish.first; p != finish.cur; ++p) {
            ++last_elem_offset;
        }

        if (map.size() == 0 || map_offset > map.size() ||
            buffer_offset >= last_elem_offset) {
            throw std::out_of_range("Index out of range");
        }
        return map[map_offset][buffer_offset];
    }

    const_reference at(size_type pos) const
    {
        size_type map_offset =
                pos / buffer_size; // map偏移量（也是buffer组偏移量）
        size_type buffer_offset = pos % buffer_size; // buffer元素偏移量

        size_type last_elem_offset =
                0; //最后一个元素的下一个位置在最后一个buffer的偏移量
        for (pointer p = finish.first; p != finish.cur; ++p) {
            ++last_elem_offset;
        }

        if (map.size() == 0 || map_offset > map.size() ||
            buffer_offset >= last_elem_offset) {
            throw std::out_of_range("Index out of range");
        }
        return map[map_offset][buffer_offset];
    }

    //返回位于指定位置 pos 的元素的引用。不进行边界检查。
    reference operator[](size_type pos)
    {
        size_type map_offset =
                pos / buffer_size; // map偏移量（也是buffer组偏移量）
        size_type buffer_offset = pos % buffer_size; // buffer元素偏移量

        return map[map_offset][buffer_offset];
    }

    const_reference operator[](size_type pos) const
    {
        size_type map_offset =
                pos / buffer_size; // map偏移量（也是buffer组偏移量）
        size_type buffer_offset = pos % buffer_size; // buffer元素偏移量

        return map[map_offset][buffer_offset];
    }

    //访问第一个元素
    reference front()
    {
        return *(start.cur);
    }

    const_reference front() const
    {
        return *(start.cur);
    }

    //访问最后一个元素
    reference back()
    {
        //return *((finish.cur) - 1);
        return *(finish - 1);
    }

    const_reference back() const
    {
        return *(finish - 1);
    }

    //检查容器是否无元素
    bool empty() const
    {
        if (! size())
            return true;
        return false;
    }

    //返回容器中的元素数量
    size_type size() const
    {
        if (!map.size())
            return 0;                            //空deque的情况
        size_type sz = map.size() * buffer_size; //总容量

        //计算首尾两buffer的空余数量（注意单buffer的可能性）
        pointer tmp_s = start.cur;
        pointer tmp_f = finish.cur; //最后一个元素的下一个位置

        while (tmp_s != start.first) { //减去第一个buffer的空位置
            --sz;
            --tmp_s;
        }

        if (start == finish)
            return sz;                 //单buffer的情况
        while (tmp_f != finish.last) { //减去最后一个buffer的空位置
            --sz;
            ++tmp_f;
        }
        return sz;
    }

    // max_size

    //清除内容
    void clear()
    {
        release();
    }

    //插入元素
    iterator insert(const_iterator pos, const T& value)
    {
        iterator it(pos.cur, pos.first, pos.last, pos.node);
        iterator res(it);
        T tmp = *it;
        *it = value;
        ++it;
        while (it != end()) {
            std::swap(*it, tmp);
            // T t = *it;
            // *it = tmp;
            // tmp = t;
            ++it;
        }
        _push_back(tmp);
        return res;
    }

    iterator insert(const_iterator pos, T&& value)
    {
        iterator it(pos.cur, pos.first, pos.last, pos.node);
        iterator res(it);
        value_type tmp = *it;
        *it = value;
        ++it;
        while (it != end()) {
            std::swap(*it, tmp);
            ++it;
        }
        _push_back(tmp);
        return res;
    }

    iterator insert(const_iterator pos, size_type count, const T& value)
    {
        iterator it(pos.cur, pos.first, pos.last, pos.node);
        iterator res(it);
        while (count--) {
            it = insert(pos, value);
            ++it;
        }
        return res;
    }

    iterator insert(const_iterator pos, size_type count, T&& value)
    {
        iterator it(pos.cur, pos.first, pos.last, pos.node);
        iterator res(it);
        while (count--) {
            it = insert(pos, value);
            ++it;
        }
        return res;
    }

    iterator insert(const_iterator pos, int count, T&& value)
    {
        if(count<=0)
            return iterator(pos.cur, pos.first, pos.last, pos.node);
        return insert(pos, size_type(count), value);
    }

    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        iterator res(pos.cur, pos.first, pos.last, pos.node);
        iterator it(res);
        while (first != last) {
            it = insert(it, *first);
            ++it;
            ++first;
        }
        return res;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        iterator res(pos.cur, pos.first, pos.last, pos.node);
        iterator i(res);
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            i = insert(i, *it);
            ++i;
        }
        return res;
    }

    //将元素添加到容器末尾
    void push_back(const T& value)
    {
        _push_back(value);
    }

    //移除末元素,
    void pop_back()
    {
        if (finish.cur ==
                    finish.first) //最后一个buffer的第一个元素删除后释放buffer
        {
            pointer del_p = finish.first;
            --finish;
            delete del_p;
            del_p = nullptr;
            map.pop_back();
        } else {
            --finish;
        }
    }

    //前附给定元素 value 到容器起始。
    void push_front(const T& value)
    {
        _push_front(value);
    }

    //移除容器首元素。
    void pop_front()
    {
        if (start.cur ==
                    (start.last) -
                    1) { //首元素是第一个buffer的最后一个元素，删除后释放buffer
            pointer del_p = start.first;
            ++start;
            delete del_p;
            del_p = nullptr;
            map.erase(map.begin()); // erase改变map与buffer的映射关系了，要重新init
                                    // start和finish的node成员
            // resetNode_start_finish();
            if (!map.size()) { //最后一个元素情况
                start.cur=nullptr;
                finish.cur=nullptr;
                return;
            }
            start.node =&map[0]; // reset start.node
            finish.node = &map[map.size() - 1];
        } else {
            ++start;
        }
    }

    //删除元素
    iterator erase(iterator pos)
    {
        if (!pos.cur)
            return pos; //空pos的情况
        for (auto it = pos; it != end(); ++it) {
            if (it + 1 == end()) {
                break;
            }
            *it = *(it + 1);
        }
        pop_back();
        return pos;
    }

    iterator erase(const_iterator pos)
    {
        if (!pos)
            return pos; //空pos的情况
        for (auto it = pos; it != end(); ++it) {
            if (it + 1 == end()) {
                break;
            }
            *it = *(it + 1);
        }
        pop_back();
        return pos;
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last) {
            first = erase(first);
            --last;
        }
        return first;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        while (first != last) {
            first = erase(first);
        }
    }

    //改变存储元素的个数
    void resize(size_type count)
    {
        size_type sz = size();
        if (sz == count) {
            return;
        } else if (sz < count) {
            size_type d_sz = count - sz;
            while (d_sz--) {
                push_back(T());
            }
        } else {
            size_type d_sz = sz - count;
            while (d_sz--) {
                pop_back();
            }
        }
    }

    void resize(size_type count, const value_type& value)
    {
        size_type sz = size();
        if (sz == count) {
            return;
        } else if (sz < count) {
            size_type d_sz = count - sz;
            while (d_sz--) {
                push_back(value);
            }
        } else {
            size_type d_sz = sz - count;
            while (d_sz--) {
                pop_back();
            }
        }
    }

    //将内容与 other 的交换。不在单独的元素上调用任何移动、复制或交换操作。
    void swap(deque& other)
    {
        if (*this == other)
            return;

        map.swap(other.map);
        swap(start, other.start);
        swap(finish, other.finish);
    }
};

//==================================非成员函数模块====================
template<typename T>
bool operator==(const deque<T>& lhs, const deque<T>& rhs)
{
    if (lhs.size() == rhs.size()) {
        if (lhs.size() == 0)
            return true; //俩空deque情况
        auto itr = rhs.begin();
        for (auto it = lhs.begin(); it != lhs.end(); ++it) {
            if (*it != *itr)
                return false;

            ++itr;
        }
        return true;
    } else { // size不相等情况
        return false;
    }
}

template<typename T>
bool operator!=(const deque<T>& lhs, const deque<T>& rhs)
{
    if (lhs == rhs)
        return false;
    return true;
}

template<typename T>
bool operator<(const deque<T>& lhs, const deque<T>& rhs)
{
    auto itr = rhs.begin();
    auto itl = lhs.begin();
    while (itr != rhs.end() && itl != lhs.end()) {
        if (*itr < *itl)
            return false;
        else if (*itr > *itl)
            return true;
        ++itr;
        ++itl;
    }
    if (itr == rhs.end() && itl == lhs.end()) {
        return false;
    } else if (itr == rhs.end()) {
        return false;
    }
    return true;
}

template<typename T>
bool operator<=(const deque<T>& lhs, const deque<T>& rhs)
{
    if (lhs < rhs || lhs == rhs)
        return true;
    return false;
}

template<typename T>
bool operator>(const deque<T>& lhs, const deque<T>& rhs)
{
    if (!(lhs <= rhs))
        return true;
    return false;
}

template<typename T>
bool operator>=(const deque<T>& lhs, const deque<T>& rhs)
{
    if (lhs > rhs || lhs == rhs)
        return true;
    return false;
}

#endif
