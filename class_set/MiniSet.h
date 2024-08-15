// MiniSet.h
#pragma once
#ifndef MINI_SET_H
#define MINI_SET_H

#include <cstddef>
#include "RB_Tree.h"

// 迭代器未实现end(),rend(),只是简单地将他们定义为nullptr;后期可以改进
template<typename Key>
class set
{
private:
    typedef Key key_type;
    typedef Key value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const Key& const_reference;
    typedef RB_TreeNode<key_type, key_type> Node;

private:
    RB_Tree<key_type, key_type> rb;

public:
    //前向声明
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    //=======================迭代器模块=========================
    class iterator
    {
    private:
        Node* _root;

    public:
        //默认构造函数
        iterator()
        {
            _root = nullptr;
        }

        iterator(Node* root): _root(root) {}

        iterator(const iterator& other)
        {
            _root = other._root;
        }

        //重载*运算符
        const key_type& operator*()
        {
            return _root->get_key();
        }

        //重载赋值=运算符
        iterator& operator=(const iterator& other)
        {
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        iterator& operator++()
        {
            _root = RB_Tree<key_type, key_type>::get_next(_root);
            return *this;
        }

        //重载后置++运算符
        iterator operator++(int)
        {
            iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        iterator& operator--()
        {
            _root = RB_Tree<key_type, key_type>::get_prev(_root);
            return *this;
        }

        //重载后置--运算符
        iterator operator--(int)
        {
            iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const iterator& other) const
        {
            return other._root == _root;
        }

        //重载不等于!=运算符
        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        // override oper==
        bool operator==(const const_iterator& other) const
        {
            return _root == other._root;
        }

        // override oper!=
        bool operator!=(const const_iterator& other) const
        {
            return _root != other._root;
        }

        //声明友元类
        friend class const_iterator;
        friend class set;
    };

    class const_iterator
    {
    private:
        const Node* _root;

    public:
        //默认构造函数
        const_iterator()
        {
            _root = nullptr;
        }

        const_iterator(Node* root): _root(root) {}

        const_iterator(const iterator& other)
        {
            _root = other._root;
        }

        const_iterator(const const_iterator& other)
        {
            _root = other._root;
        }

        //重载*运算符
        const key_type& operator*()
        {
            return _root->get_key();
        }

        //重载赋值=运算符
        const_iterator& operator=(const const_iterator& other)
        {
            _root = other._root;
            return *this;
        }

        const_iterator& operator=(const iterator& other)
        {
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        const_iterator& operator++()
        {
            _root = RB_Tree<key_type, key_type>::get_next(_root);
            return *this;
        }

        //重载后置++运算符
        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        const_iterator& operator--()
        {
            _root = RB_Tree<key_type, key_type>::get_prev(_root);
            return *this;
        }

        //重载后置--运算符
        const_iterator operator--(int)
        {
            const_iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const const_iterator& other) const
        {
            return other._root == _root;
        }

        //重载不等于!=运算符
        bool operator!=(const const_iterator& other) const
        {
            return !(*this == other);
        }

        //重载等于==运算符
        bool operator==(const iterator& other) const
        {
            return other._root == _root;
        }

        //重载不等于!=运算符
        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        //声明友元类
        friend class iterator;
        friend class set;
    };

    class reverse_iterator
    {
    private:
        Node* _root;

    public:
        //默认构造函数
        reverse_iterator()
        {
            _root = nullptr;
        }

        reverse_iterator(Node* root): _root(root) {}

        reverse_iterator(const reverse_iterator& other)
        {
            _root = other._root;
        }

        //重载*运算符
        const key_type& operator*()
        {
            return _root->get_key();
        }

        //重载赋值=运算符
        reverse_iterator& operator=(const reverse_iterator& other)
        {
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        reverse_iterator& operator++()
        {
            _root = RB_Tree<key_type, key_type>::get_prev(_root);
            return *this;
        }

        //重载后置++运算符
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        reverse_iterator& operator--()
        {
            _root = RB_Tree<key_type, key_type>::get_next(_root);
            return *this;
        }

        //重载后置--运算符
        reverse_iterator operator--(int)
        {
            reverse_iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const reverse_iterator& other) const
        {
            return other._root == _root;
        }

        //重载不等于!=运算符
        bool operator!=(const reverse_iterator& other) const
        {
            return !(*this == other);
        }

        //重载等于==运算符
        bool operator==(const const_reverse_iterator& other) const
        {
            return other._root == _root;
        }

        //重载不等于!=运算符
        bool operator!=(const const_reverse_iterator& other) const
        {
            return !(*this == other);
        }

        //声明友元类
        friend class const_reverse_iterator;
        friend class set;
    };

    class const_reverse_iterator
    {
    private:
        const Node* _root;

    public:
        //默认构造函数
        const_reverse_iterator()
        {
            _root = nullptr;
        }

        const_reverse_iterator(Node* root): _root(root) {}

        const_reverse_iterator(const const_reverse_iterator& other)
        {
            _root = other._root;
        }

        const_reverse_iterator(const reverse_iterator& other)
        {
            _root = other._root;
        }

        //重载*运算符
        const key_type& operator*()
        {
            return _root->get_key();
        }

        //重载赋值=运算符
        const_reverse_iterator& operator=(const const_reverse_iterator& other)
        {
            _root = other._root;
            return *this;
        }

        const_reverse_iterator& operator=(const reverse_iterator& other)
        {
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        const_reverse_iterator& operator++()
        {
            _root = RB_Tree<key_type, key_type>::get_prev(_root);
            return *this;
        }

        //重载后置++运算符
        const_reverse_iterator operator++(int)
        {
            const_reverse_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        const_reverse_iterator& operator--()
        {
            _root = RB_Tree<key_type, key_type>::get_next(_root);
            return *this;
        }

        //重载后置--运算符
        const_reverse_iterator operator--(int)
        {
            const_reverse_iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const const_reverse_iterator& other) const
        {
            return other._root == _root;
        }

        //重载不等于!=运算符
        bool operator!=(const const_reverse_iterator& other) const
        {
            return !(*this == other);
        }

        //重载等于==运算符
        bool operator==(const reverse_iterator& other) const
        {
            return other._root == _root;
        }

        //重载不等于!=运算符
        bool operator!=(const reverse_iterator& other) const
        {
            return !(*this == other);
        }

        //声明友元类
        friend class reverse_iterator;
        friend class set;
    };

    //返回指向 set 首元素的迭代器。
    //如果 set 为空，那么返回的迭代器等于 end()。
    iterator begin()
    {
        return iterator(rb.head->left_child);
    }

    const_iterator begin() const
    {
        return const_iterator(rb.head->left_child);
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(rb.head->left_child);
    }

    //返回指向 set
    //末元素后一元素的迭代器。此元素表现为占位符；试图访问它导致未定义行为。
    iterator end()
    {
        return iterator();
    }

    const_iterator end() const
    {
        return const_iterator();
    }

    const_iterator cend() const noexcept
    {
        return const_iterator();
    }

    //返回指向逆向的 set 的首元素的逆向迭代器。
    //它对应非逆向 set 的末元素。如果set 为空，那么返回的迭代器等于 rend()。
    reverse_iterator rbegin()
    {
        return reverse_iterator(rb.head->right_child);
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(rb.head->right_child);
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(rb.head->right_child);
    }

    //返回指向逆向的 set 末元素后一元素的逆向迭代器。它对应非逆向 set
    //首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。
    reverse_iterator rend()
    {
        return reverse_iterator();
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator();
    }

    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator();
    }

    //======================构造函数模块=============
    //默认构造函数
    set() {}

    //以范围 [first,
    // last)的内容构造容器。如果范围中的多个元素的键比较相等，那么未指定哪个元素会被插入
    template<typename InputIt>
    set(InputIt first, InputIt last)
    {
        while (first != last) {
            rb.insert(std::make_pair(*first, *first));
            ++first;
        }
    }

    //复制构造函数。以 other 的内容副本构造容器。
    set(const set& other)
    {
        if (!rb.head) {
            delete rb.head; //删除首结点
        }
        rb.head = other.rb._cp();
    }

    //移动构造函数。以 other 的内容用移动语义构造容器。
    set(set&& other)
    {
        std::swap(
                rb.head,
                other.rb.head); //这样就可以在other析构时候释放set初始化的首节点
    }

    //初始化式列表构造函数。以 initializer_list init
    //的内容构造容器。如果范围中的多个元素的键比较相等，那么未指定哪个元素会被插入
    set(std::initializer_list<value_type> init)
    {
        for (auto it = init.begin(); it != init.end(); ++it) {
            rb.insert(std::make_pair(*it, *it));
        }
    }

    //====================析构函数模块==================
    ~set()
    {
        // rb.release();//应该不需要，自动调用
    }

    //=====================成员函数模块=================
    //复制赋值运算符。以 other 内容的副本替换内容。
    set& operator=(const set& other)
    {
        delete rb.head; //删除首节点
        rb.head = other._cp();
        return *this;
    }

    //移动赋值运算符。用移动语义以 other 的内容替换内容（即从 other 移动 other
    //中的数据到此容器中）。之后 other 处于合法但未指定的状态。
    set& operator=(set&& other)
    {
        std::swap(
                rb.head,
                other.rb.head); //这样就可以在other析构时候释放set初始化的首节点
        return *this;
    }

    //以 initializer_list ilist 所标识者替换内容。
    set& operator=(std::initializer_list<value_type> ilist)
    {
        rb.release();
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            rb.insert(*it);
        }
        return *this;
    }

    //==============================容量模块=======================
    bool empty()
    {
        if (rb.size() == 0) {
            return true;
        }
        return false;
    }

    size_type size() const
    {
        return rb.size();
    }

    // size_type max_size() const;

    //==============================修改器模块====================
    //从容器擦除所有元素。此调用后 size() 返回零。
    void clear()
    {
        rb.clear();
    }

    // insert:插入元素到容器，如果容器未含拥有等价关键的元素。
    std::pair<iterator, bool> insert(const value_type& value)
    {
        bool res_bool = rb.insert(std::make_pair(value, value));
        return std::make_pair(iterator(rb.find(value)), res_bool);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        bool res_bool = rb.insert(std::make_pair(value, value));
        return std::make_pair(iterator(rb.find(value)), res_bool);
    }

    //插入来自范围 [first, last) 的元素。
    template<class InputIt>
    void insert(InputIt first, InputIt last)
    {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    //插入来自 initializer_list ilist 的元素。
    void insert(std::initializer_list<value_type> ilist)
    {
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            insert(*it);
        }
    }

    //从容器移除指定的元素。
    iterator erase(iterator pos)
    {
        iterator res = pos;
        ++res;
        rb.erase(pos._root); //调用rbtree的erase
        return res;
    }

    // 移除范围 [first, last) 中的元素，它必须是 *this 中的合法范围。
    iterator erase(iterator first, iterator last)
    {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }

    //移除键等价于 key 的元素（如果存在一个）。
    size_type erase(const Key& key)
    {
        if (rb.erase(key))
            return 1;
        return 0;
    }

    // swap
    //将内容与 other 的交换。不在单独的元素上调用任何移动、复制或交换操作。
    //所有迭代器和引用仍然有效。end() 迭代器失效。
    void swap(set& other)
    {
        std::swap(other.rb.head, this->rb.head);
    }

    //============查找模块=============
    //返回拥有与指定实参比较等价的键的元素数。
    //返回拥有键 key 的元素数。，因为此容器不允许重复，故只能为 1 或 0。
    size_type count(const Key& key) const
    {
        if (rb.find(key))
            return 1;
        return 0;
    }

    //寻找键等于 key 的的元素。
    iterator find(const Key& key)
    {
        return iterator(rb.find(key));
    }

    const_iterator find(const Key& key) const
    {
        return const_iterator(rb.find(key));
    }
};

//非成员函数
template<typename Key>
bool operator==(const set<Key>& lhs, const set<Key>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    auto itl = lhs.begin();
    auto itr = rhs.begin();
    while (itl != lhs.end()) {
        if (*itl != *itr) {
            return false;
        }
        ++itl;
        ++itr;
    }
    return true;
}

template<typename Key>
bool operator!=(const set<Key>& lhs, const set<Key>& rhs)
{
    return !(lhs == rhs);
}

template<typename Key>
bool operator<(const set<Key>& lhs, const set<Key>& rhs)
{
    auto itl = lhs.begin();
    auto itr = rhs.begin();
    while (!(itl == lhs.end() && itr == rhs.end())) {
        if (itl == lhs.end())
            return true;
        if (itr == rhs.end())
            return false;
        if (*itl > *itr)
            return false;
        if (*itl < *itr)
            return true;
        ++itl;
        ++itr;
    }
    return false; // lhs==rhs;
}

template<typename Key>
bool operator<=(const set<Key>& lhs, const set<Key>& rhs)
{
    return (lhs == rhs) || (lhs < rhs);
}

template<typename Key>
bool operator>(const set<Key>& lhs, const set<Key>& rhs)
{
    return !((lhs == rhs) || (lhs < rhs));
}

template<typename Key>
bool operator>=(const set<Key>& lhs, const set<Key>& rhs)
{
    return !(lhs < rhs);
}

template<typename Key>
void swap(set<Key>& lhs, set<Key>& rhs)
{
    lhs.swap(rhs);
}

#endif
