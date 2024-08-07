//MiniUnorderedSet.h
#pragma once
#ifndef MINI_UNORDERED_SET_H
#define MINI_UNORDERED_SET_H

#include"HashTable.h"
#include<cstddef>

template<typename K>//仿函数，获取set键
class KeyOfT{
public:
    K& operator()(K& key){
        return key;
    }
};

template<typename Key>
class unordered_set{
private:
    typedef Key key_type;
    typedef Key value_type;
    typedef size_t size_type;
    typedef value_type& reference;
    typedef const Key& const_reference;
    typedef HashNode<Key> Node;
    typedef HashTable<Key, Key, KeyOfT> HashTable;

    HashTable ht;

    //前向声明
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    //===================辅助函数模块=============
    void clear(){
        ht.clear();
    }

public:
    //=======迭代器模块========
    class iterator{
    private:
        Node* cur;
        HashTable* hp;

    public:
        //构造函数
        iterator(){}

        iterator(Node* c,HashTable* h):cur(c),hp(hp){}

        //重载operator*
        const value_type& operator*(){
            return cur->data;
        }

        //重载operator=
        iterator& operator=(const Node* other){
            cur = other.cur;
            hp = other.hp;
            return *this;
        }

        //重载operator++
        iterator& operator++(){
            cur = hp->get_next(cur);
            return *this;
        }

        //override operator++(int)
        iterator operator++(int){
            iterator res = cur;
            ++cur;
            return res;
        }

        //override operator--
        iterator& operator--(){
            cur = hp->get_prev(cur);
            return *this;
        }

        //override operator--(int)
        iterator operator--(int){
            iterator res = cur;
            --cur;
            return res;
        }

        //override operator==
        bool operator==(const iterator& other)const{
            if(cur==other.cur)
                return true;
            return false;
        }

        //override operator!=
        bool operator!=(const iterator& other)const{
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
        friend class unordered_set;
    };
    class const_iterator{
    private:
        const Node* cur;
        const HashTable* hp;

    public:
        //构造函数
        const_iterator() {}

        const_iterator(Node* c,HashTable* h): cur(c),hp(h) {}

        //重载operator*
        const value_type& operator*()
        {
            return cur->data;
        }

        //重载operator=
        const_iterator& operator=(const Node* other)
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
            const_iterator res = cur;
            ++cur;
            return res;
        }

        // override operator--
        const_iterator& operator--()
        {
            cur = hp->get_prev(cur);
            return *this;
        }

        // override operator--(int)
        const_iterator operator--(int)
        {
            const_iterator res = cur;
            --cur;
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
        friend class unordered_set;
    };
    class reverse_iterator{
    private:
        Node* cur;
        HashTable* hp;

    public:
        //构造函数
        reverse_iterator() {}

        reverse_iterator(Node* c, HashTable* h): cur(c),hp(h) {}

        //重载operator*
        const value_type& operator*()
        {
            return cur->data;
        }

        //重载operator=
        reverse_iterator& operator=(const Node* other)
        {
            cur = other.cur;
            hp = other.hp;
            return *this;
        }

        //重载operator++
        reverse_iterator& operator++()
        {
            cur = hp->get_prev(cur);
            return *this;
        }

        // override operator++(int)
        reverse_iterator operator++(int)
        {
            reverse_iterator res = cur;
            ++cur;
            return res;
        }

        // override operator--
        reverse_iterator& operator--()
        {
            cur = hp->get_next(cur);
            return *this;
        }

        // override operator--(int)
        reverse_iterator operator--(int)
        {
            reverse_iterator res = cur;
            --cur;
            return res;
        }

        // override operator==
        bool operator==(const reverse_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const reverse_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        // override operator==
        bool operator==(const const_reverse_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const const_reverse_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        //声明友元类
        friend class const_reverse_iterator;
        friend class unordered_set;
    };
    class const_reverse_iterator{
    private:
        const Node* cur;
        const HashTable* hp;

    public:
        //构造函数
        const_reverse_iterator() {}

        const_reverse_iterator(Node* c, HashTable* h): cur(c),hp(h) {}

        //重载operator*
        const value_type& operator*()
        {
            return cur->data;
        }

        //重载operator=
        const_reverse_iterator& operator=(const Node* other)
        {
            cur = other.cur;
            hp = other.hp;
            return *this;
        }

        //重载operator++
        const_reverse_iterator& operator++()
        {
            cur = hp->get_prev(cur);
            return *this;
        }

        // override operator++(int)
        const_reverse_iterator operator++(int)
        {
            const_reverse_iterator res = cur;
            ++cur;
            return res;
        }

        // override operator--
        const_reverse_iterator& operator--()
        {
            cur = hp->get_next(cur);
            return *this;
        }

        // override operator--(int)
        const_reverse_iterator operator--(int)
        {
            const_reverse_iterator res = cur;
            --cur;
            return res;
        }

        // override operator==
        bool operator==(const const_reverse_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const const_reverse_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        // override operator==
        bool operator==(const reverse_iterator& other) const
        {
            if (cur == other.cur)
                return true;
            return false;
        }

        // override operator!=
        bool operator!=(const reverse_iterator& other) const
        {
            if (cur != other.cur)
                return true;
            return false;
        }

        //声明友元类
        friend class reverse_iterator;
        friend class unordered_set;
    };

    //local_iterator
    //const_local_iterator

    //迭代器操作
    iterator begin(){
        return iterator(ht.begin(),&ht);
    }

    const_iterator begin()const{
        return const_iterator(ht.begin(),&ht);
    }

    const_iterator cbegin()const{
        return const_iterator(ht.begin(),&ht);
    }

    iterator end()
    {
        return nullptr;
    }

    const_iterator end()const{
        return nullptr;
    }

    const_iterator cend()const{
        return nullptr;
    }

    //***********成员函数模块**********
    //============构造函数=============
    //默认构造函数
    unordered_set(){}

    //构造具有范围 [first, last) 的内容的容器。
    template<typename InputIt>
    unordered_set(InputIt first, InputIt last){
        while(first!=last){
            ht.insert(*first);
        }
    }

    //复制构造函数
    unordered_set(const unordered_set& other){
        other.ht._cp(ht);
    }

    //移动构造函数
    unordered_set(unorder_set&& other){
        other.ht.move_to(ht);
    }

    //初始化列表构造函数
    unordered_set(std::initializer_list<value_type>ilist){
        for (auto it = ilist.begin(); it != ilist.end();++it){
            ht.insert(*it);
        }
    }

    //=========析构函数模块=========
    //析构函数
    ~unordered_set(){}//hashtable会自行析构销毁

    // operator=
    //复制赋值运算符。以 other 内容的副本替换内容。
    unordered_set& operator=(const unordered_set& other){
        ht = other.ht._cp();
        return *this;
    }

    //移动赋值运算符。用移动语义以 other 的内容替换内容（即从 other 移动 other
    //中的数据到此容器中）。之后 other 处于合法但未指定的状态。
    unordered_set& operator=(unordered_set&& other){
        //不用release，成员hashmap对象会自动调用析构函数
        other.ht.move_to(ht);
        return *this;
    }

    //以 initializer_list ilist 所标识者替换内容。
    unordered_set& operator=(std::initializer_list ilist){
        release();
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            ht.insert(*it);
        }
        return *this;
    }

    //+++++++++++++++++++++++++++start here 该写测试了
};

#endif
