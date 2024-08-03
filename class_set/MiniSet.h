// MiniSet.h
#pragma once
#ifndef MINI_SET_H
#define MINI_SET_H

#include <cstddef>
#include "RB_Tree.h"

// 迭代器未实现end(),rend(),只是简单地将他们定义为nullptr;后期可以改进
template <typename Key>
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

    //========================辅助函数模块=============

public:
//=======================迭代器模块=========================
    class iterator
    {
    private:
        Node* _root;

    public:
        //默认构造函数
        iterator(){
            _root = nullptr;
        }

        iterator(Node* root):_root(root){}

        iterator(const iterator& other){
            _root = other._root;
        }

        //重载*运算符
        key_type& operator*(){
            return _root->get_key();
        }

        //重载赋值=运算符
        iterator& operator=(const iterator& other){
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        iterator& operator++(){
            _root = rb.get_next(_root);
            return *this;
        }

        //重载后置++运算符
        iterator& operator++(int){
            iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        iterator& operator--(){
            _root = rb.get_prev(_root);
            return *this;
        }

        //重载后置--运算符
        iterator& operator--(int){
            iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const iterator& other){
            if(other._root==_root){
                return true;
            }
            return false;
        }

        //重载不等于!=运算符
        bool operator!=(const iterator& other){
            return !(*this == other);
        }
    };

    class const_iterator
    {
    private:
        const Node* _root;

    public:
        //默认构造函数
        const_iterator(){
            _root = nullptr;
        }

        const_iterator(Node* root):_root(root){}

        const_iterator(const iterator& other){
            _root = other._root;
        }

        const_iterator(const const_iterator& other){
            _root = other._root;
        }

        //重载*运算符
        key_type& operator*(){
            return _root->get_key();
        }

        //重载赋值=运算符
        const_iterator& operator=(const const_iterator& other){
            _root = other._root;
            return *this;
        }

        const_iterator& operator=(const iterator& other){
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        const_iterator& operator++(){
            _root = rb.get_next(_root);
            return *this;
        }

        //重载后置++运算符
        const_iterator& operator++(int){
            const_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        const_iterator& operator--(){
            _root = rb.get_prev(_root);
            return *this;
        }

        //重载后置--运算符
        const_iterator& operator--(int){
            const_iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const const_iterator& other){
            if(other._root==_root){
                return true;
            }
            return false;
        }

        //重载不等于!=运算符
        bool operator!=(const const_iterator& other){
            return !(*this == other);
        }
    };

    class reverse_iterator
    {
    private:
        Node* _root;
    public:
        //默认构造函数
        reverse_iterator(){
            _root = nullptr;
        }

        reverse_iterator(Node* root):_root(root){}

        reverse_iterator(const reverse_iterator& other){
            _root = other._root;
        }

        //重载*运算符
        key_type& operator*(){
            return _root->get_key();
        }

        //重载赋值=运算符
        reverse_iterator& operator=(const reverse_iterator& other){
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        reverse_iterator& operator++(){
            _root = rb.get_prev(_root);
            return *this;
        }

        //重载后置++运算符
        reverse_iterator& operator++(int){
            reverse_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        reverse_iterator& operator--(){
            _root = rb.get_next(_root);
            return *this;
        }

        //重载后置--运算符
        reverse_iterator& operator--(int){
            reverse_iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const reverse_iterator& other){
            if(other._root==_root){
                return true;
            }
            return false;
        }

        //重载不等于!=运算符
        bool operator!=(const reverse_iterator& other){
            return !(*this == other);
        }
    };

    class const_reverse_iterator
    {
    private:
        const Node* _root;
    public:
        //默认构造函数
        const_reverse_iterator(){
            _root = nullptr;
        }

        const_reverse_iterator(Node* root):_root(root){}

        const_reverse_iterator(const const_reverse_iterator& other){
            _root = other._root;
        }

        const_reverse_iterator(const reverse_iterator& other){
            _root = other._root;
        }

        //重载*运算符
        key_type& operator*(){
            return _root->get_key();
        }

        //重载赋值=运算符
        const_reverse_iterator& operator=(const const_reverse_iterator& other){
            _root = other._root;
            return *this;
        }

        const_reverse_iterator& operator=(const reverse_iterator& other){
            _root = other._root;
            return *this;
        }

        //重载前置++运算符
        const_reverse_iterator& operator++(){
            _root = rb.get_prev(_root);
            return *this;
        }

        //重载后置++运算符
        const_reverse_iterator& operator++(int){
            const_reverse_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        //重载前置--运算符
        const_reverse_iterator& operator--(){
            _root = rb.get_next(_root);
            return *this;
        }

        //重载后置--运算符
        const_reverse_iterator& operator--(int){
            const_reverse_iterator temp(*this);
            --*this;
            return temp;
        }

        //重载等于==运算符
        bool operator==(const const_reverse_iterator& other){
            if(other._root==_root){
                return true;
            }
            return false;
        }

        //重载不等于!=运算符
        bool operator!=(const const_reverse_iterator& other){
            return !(*this == other);
        }
    };

    //返回指向 set 首元素的迭代器。
    //如果 set 为空，那么返回的迭代器等于 end()。
    iterator begin() {
        return iterator(rb.head->left_child);
    }

    const_iterator begin() const {
        return const_iterator(rb.head->left_child);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(rb.head->left_child);
    }

    //返回指向 set
    //末元素后一元素的迭代器。此元素表现为占位符；试图访问它导致未定义行为。
    iterator end(){
        return iterator();
    }

    const_iterator end() const {
        return const_iterator();
    }

    const_iterator cend() const noexcept {
        return const_iterator();
    }

    //返回指向逆向的 set 的首元素的逆向迭代器。
    //它对应非逆向 set 的末元素。如果set 为空，那么返回的迭代器等于 rend()。
    reverse_iterator rbegin() {
        return reverse_iterator(rb.head->right_child);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(rb.head->right_child);
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(rb.head->right_child);
    }

    //返回指向逆向的 set 末元素后一元素的逆向迭代器。它对应非逆向 set
    //首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。
    reverse_iterator rend() {
        return reverse_iterator();
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator();
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator();
    }

    //override oper==
    bool operator==(const iterator& rhs,const const_iterator& lhs){
        if(rhs._root==lhs._root){
            return true;
        }
        return false;
    }

    bool operator==(const const_iterator& rhs,const iterator& lhs){
        if(rhs._root==lhs._root){
            return true;
        }
        return false;
    }

    bool operator!=(const iterator& rhs,const const_iterator& lhs){
        if(rhs._root!=lhs._root){
            return true;
        }
        return false;
    }

    bool operator!=(const const_iterator& rhs,const iterator& lhs){
        if(rhs._root!=lhs._root){
            return true;
        }
        return false;
    }

    bool operator==(const reverse_iterator& rhs,const const_reverse_iterator& lhs){
        if(rhs._root==lhs._root){
            return true;
        }
        return false;
    }

    bool operator==(const const_reverse_iterator& rhs,const reverse_iterator& lhs){
        if(rhs._root==lhs._root){
            return true;
        }
        return false;
    }

    bool operator!=(const reverse_iterator& rhs,const const_reverse_iterator& lhs){
        if(rhs._root!=lhs._root){
            return true;
        }
        return false;
    }

    bool operator!=(const const_reverse_iterator& rhs,const reverse_iterator& lhs){
        if(rhs._root!=lhs._root){
            return true;
        }
        return false;
    }

    //======================构造函数模块=============
    //默认构造函数
    set() {}

    set(int count, value_type value)
    {
        while (count--) {
            rb.insert(value, value);
        }
    }

    //以范围 [first,
    //last)的内容构造容器。如果范围中的多个元素的键比较相等，那么未指定哪个元素会被插入
    template<typename InputIt>
    set(InputIt first, InputIt last)
    {
        while (first != last) {
            rb.insert(std::make_pair(*first, *first));
            ++first;
        }
    }

    //复制构造函数。以 other 的内容副本构造容器。
    set(set& other)
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

    size_type size()
    {
        return rb.size();
    }

    // size_type max_size() const;

    //==============================修改器模块====================
    //从容器擦除所有元素。此调用后 size() 返回零。
    void clear()
    {
        rb.release();
    }
};

#endif
