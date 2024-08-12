// MiniUnorderedMap.h
#pragma once
#ifndef MINI_UNORDERED_MAP_H
#define MINI_UNORDERED_MAP_H

#include "HashTable.h"
#include <cstddef>
#include <utility>

template<typename Key, typename T>
class unordered_map
{
private:
    typedef Key key_type;
    typedef T mapped_type;
    typedef std::pair<const Key, T> value_type;
    typedef size_t size_type;
    typedef value_type& reference;
    typedef const T& const_reference;
    typedef HashNode<value_type> Node;

    class KeyOfT
    {
    public:
        const Key operator()(const value_type& data) const
        {
            return data.first;
        }
    };
    typedef HashTable<Key, value_type, KeyOfT> hashtable;

    hashtable ht;
    KeyOfT kot;

    //===================辅助函数模块=============
    //清空内存，size为0,但是数据结构可继续使用，对象还在，没析构
    void release()
    {
        ht.clear();
    }

public:
    //前向声明
    class iterator;
    class const_iterator;
    class local_iterator;
    class const_local_iterator;
    //=======迭代器模块========
    class iterator
    {
    private:
        Node* cur;
        hashtable* hp;

    public:
        //构造函数
        iterator() {}

        iterator(Node* c, hashtable* h): cur(c), hp(hp) {}

        //重载operator*
        value_type& operator*()
        {
            return cur->data;
        }

        //重载operator->
        value_type* operator->()
        {
            return &(cur->data);
        }

        //重载operator=
        iterator& operator=(const iterator* other)
        {
            cur = other.cur;
            hp = other.hp;
            return *this;
        }

        //重载operator++
        iterator& operator++()
        {
            cur = hp->get_next(cur);
            return *this;
        }

        // override operator++(int)
        iterator operator++(int)
        {
            iterator res = *this;
            ++*this;
            return res;
        }

        // override operator==
        bool operator==(const iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        // override operator==
        bool operator==(const const_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const const_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        //声明友元类
        friend class const_iterator;
        friend class unordered_map;
    };
    class const_iterator
    {
    private:
        const Node* cur;
        const hashtable* hp;

    public:
        //构造函数
        const_iterator() {}

        const_iterator(const Node* c, const hashtable* h): cur(c), hp(h) {}

        // iterator -> const_iterator
        const_iterator(const iterator& other): cur(other.cur), hp(other.hp) {}

        //重载operator*
        const value_type& operator*()
        {
            return cur->data;
        }

        //重载operator->
        const value_type* operator->()
        {
            return &(cur->data);
        }

        //重载operator=
        const_iterator& operator=(const const_iterator& other)
        {
            cur = other.cur;
            hp = other.hp;
            return *this;
        }

        //重载operator++
        const_iterator& operator++()
        {
            cur = hp->get_next(cur);
            return *this;
        }

        // override operator++(int)
        const_iterator operator++(int)
        {
            const_iterator res = *this;
            ++*this;
            return res;
        }

        // override operator==
        bool operator==(const const_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const const_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        // override operator==
        bool operator==(const iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        //声明友元类
        friend class iterator;
        friend class unordered_map;
    };

    // local_iterator
    //=======迭代器模块========
    class local_iterator
    {
    private:
        Node* cur;
        hashtable* hp;

    public:
        //构造函数
        local_iterator() {}

        local_iterator(Node* c, hashtable* h): cur(c), hp(hp) {}

        //重载operator*
        const value_type& operator*()
        {
            return cur->data;
        }

        //重载operator=
        local_iterator& operator=(const local_iterator* other)
        {
            cur = other.cur;
            hp = other.hp;
            return *this;
        }

        //重载operator++
        local_iterator& operator++()
        {
            cur = hp->get_next_in_bucket(cur);
            return *this;
        }

        // override operator++(int)
        local_iterator operator++(int)
        {
            local_iterator res = cur;
            ++cur;
            return res;
        }

        // override operator==
        bool operator==(const local_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const local_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        // override operator==
        bool operator==(const const_local_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const const_local_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        //声明友元类
        friend class const_local_iterator;
        friend class unordered_map;
    };

    // const_local_iterator
    class const_local_iterator
    {
    private:
        const Node* cur;
        const hashtable* hp;

    public:
        //构造函数
        const_local_iterator() {}

        const_local_iterator(Node* c, hashtable* h): cur(c), hp(h) {}

        const_local_iterator(const local_iterator& other)
            : cur(other.cur),
              hp(other.hp)
        {
        }

        //重载operator*
        const value_type& operator*()
        {
            return cur->data;
        }

        //重载operator=
        const_local_iterator& operator=(const const_local_iterator& other)
        {
            cur = other.cur;
            hp = other.hp;
            return *this;
        }

        //重载operator++
        const_local_iterator& operator++()
        {
            cur = hp->get_next_in_bucket(cur);
            return *this;
        }

        // override operator++(int)
        const_local_iterator operator++(int)
        {
            const_local_iterator res = cur;
            ++cur;
            return res;
        }

        // override operator==
        bool operator==(const const_local_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const const_local_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        // override operator==
        bool operator==(const local_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const local_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        //声明友元类
        friend class local_iterator;
        friend class unordered_map;
    };

    //桶接口部分
    //+++++++++++++++++++++++++++++++++++here

    //迭代器操作
    iterator begin()
    {
        return iterator(ht.begin(), &ht);
    }

    const_iterator begin() const
    {
        return const_iterator(ht.begin(), &ht);
    }

    const_iterator cbegin() const
    {
        return const_iterator(ht.begin(), &ht);
    }

    iterator end()
    {
        return iterator(nullptr, nullptr);
    }

    const_iterator end() const
    {
        return iterator(nullptr, nullptr);
    }

    const_iterator cend() const
    {
        return iterator(nullptr, nullptr);
    }

    //***********成员函数模块**********
    //============构造函数=============
    //默认构造函数
    unordered_map() {}

    //构造具有范围 [first, last) 的内容的容器。
    template<typename InputIt>
    unordered_map(InputIt first, InputIt last)
    {
        while (first != last) {
            ht.insert(*first);
            ++first;
        }
    }

    //复制构造函数
    unordered_map(const unordered_map& other)
    {
        other.ht._cp(ht);
    }

    //移动构造函数
    unordered_map(unordered_map&& other)
    {
        other.ht.move_to(ht);
    }

    //初始化列表构造函数
    unordered_map(std::initializer_list<value_type> ilist)
    {
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            ht.insert(*it);
        }
    }

    //=========析构函数模块=========
    //析构函数
    ~unordered_map() {} // hashtable会自行析构销毁

    // operator=
    //复制赋值运算符。以 other 内容的副本替换内容。
    unordered_map& operator=(const unordered_map& other)
    {
        ht = other.ht._cp();
        return *this;
    }

    //移动赋值运算符。用移动语义以 other 的内容替换内容（即从 other 移动 other
    //中的数据到此容器中）。之后 other 处于合法但未指定的状态。
    unordered_map& operator=(unordered_map&& other)
    {
        //不用release，成员hashmap对象会自动调用析构函数
        other.ht.move_to(ht);
        return *this;
    }

    //以 initializer_list ilist 所标识者替换内容。
    unordered_map& operator=(std::initializer_list<value_type> ilist)
    {
        ht.clear();
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            ht.insert(*it);
        }
        return *this;
    }

    //======================容量模块=================
    //获取unordered_map是否为空
    bool empty() const
    {
        return !(ht.get_size());
    }

    size_type size() const
    {
        return ht.get_size();
    }

    // max_size

    //=======================修改器模块===============
    //从容器擦除所有元素。此调用后 size() 返回零。
    void clear()
    {
        release();
    }

    //若容器尚未含有等价的键的元素，则插入元素到容器中。
    std::pair<iterator, bool> insert(const value_type& value)
    {
        Node* tmp = ht.insert(value); //插入，失败返回nullptr
        if (tmp) {
            return std::make_pair(iterator(tmp, &ht), true);
        }
        return std::make_pair(iterator(), false);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        Node* tmp = ht.insert(value); //插入，失败返回nullptr
        if (tmp) {
            return std::make_pair(iterator(tmp, &ht), true);
        }
        return std::make_pair(iterator(), false);
    }

    template<typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        while (first != last) {
            ht.insert(*first);
            ++first;
        }
    }

    void insert(std::initializer_list<value_type> ilist)
    {
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            ht.insert(*it);
        }
    }

    //从容器移除指定的元素。保留未被移除的元素的顺序（这使得可能在迭代通过容器时移除单独的元素）。
    iterator erase(iterator pos)
    {
        // erase掉pos++中返回的原位置的节点
        ht.erase(kot(*(pos++)));
        return pos;
    }

    const_iterator erase(const_iterator pos)
    {
        ht.erase(kot(*(pos++)));
        return pos;
    }

    /*
    here 官方文档返回iterator，不知道为什么，不是会丢失const修饰吗
    */
    const_iterator erase(const_iterator first, const_iterator last)
    {
        while (first != last) {
            first = erase(first);
        }
        return first;
    }

    size_type erase(const Key& key)
    {
        return ht.erase(key);
    }

    //将内容与 other 的交换。不在单独的元素上调用任何移动、复制或交换操作。
    void swap(unordered_map& other)
    {
        ht.swap(other.ht);
    }

    //=====================查找模块===================
    //返回拥有与指定实参 key 比较相等的键的元素数，
    //因为此容器不允许重复故为 1 或 0。
    size_type count(const Key& key) const
    {
        if (find(key) != end())
            return 1;
        return 0;
    }

    //寻找键等于 key 的的元素。
    iterator find(const Key& key)
    {
        return iterator(ht.find(key), &ht);
    }

    const_iterator find(const Key& key) const
    {
        return const_iterator(ht.find(key), &ht);
    }

    //=====================桶接口模块=================
    //暂略
};

//===========================非成员函数模块============
template<typename Key, typename T>
bool operator==(
        const unordered_map<Key, T>& lhs,
        const unordered_map<Key, T>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (auto it = lhs.begin(); it != lhs.end(); ++it) {
        if (rhs.find(it->first) == rhs.end())
            return false;
    }
    return true;
}

template<typename Key, typename T>
bool operator!=(
        const unordered_map<Key, T>& lhs,
        const unordered_map<Key, T>& rhs)
{
    return !(lhs == rhs);
}

template<typename Key, typename T>
void swap(unordered_map<Key, T>& lhs, unordered_map<Key, T>& rhs)
{
    lhs.swap(rhs);
}

#endif
