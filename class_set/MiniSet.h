//MiniSet.h
#pragma once
#ifndef MINI_SET_H
#define MINI_SET_H

#include<cstddef>
#include"RB_Tree.h"

template<typename Key>
class set{
private:
    typedef Key key_type;
    typedef Key value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const Key& const_reference;
    typedef RB_TreeNode<key_type, key_type> Node;

private:
    RB_Tree<key_type,key_type> rb;

    //========================辅助函数模块=============

public:
    class iterator{
    };
    class const_iterator{
    };
    class reverse_iterator{
    };
    class const_reverse_iterator{
    };

    //======================构造函数模块=============
    //默认构造函数
    set(){
    }

    //以范围 [first, last)的内容构造容器。如果范围中的多个元素的键比较相等，那么未指定哪个元素会被插入
    template<typename InputIt>
    set(InputIt first,InputIt last){
        while(first!=last){
            rb.insert(*first);
            ++first;
        }
    }

    //复制构造函数。以 other 的内容副本构造容器。
    set(const set& other){
        rb.head = _cp(other);
    }

    //移动构造函数。以 other 的内容用移动语义构造容器。
    set(set&& other){
        rb.head = other.head;
        other.set_head_null();//防止被析构++++++++++++++++++++这里换种写法
    }

    //初始化式列表构造函数。以 initializer_list init
    //的内容构造容器。如果范围中的多个元素的键比较相等，那么未指定哪个元素会被插入
    set(std::initializer_list<value_type> init){
        for (auto it = init.begin(); it != init.end();++it){
            rb.insert(*it);
        }
    }

    //====================析构函数模块==========
    ~set(){
        //rb.release();//应该不需要，自动调用
    }

    //=====================成员函数模块=======
    //复制赋值运算符。以 other 内容的副本替换内容。
    set& operator=(const set& other){
        rb.head = _cp(other);
        return *this;
    }

    //移动赋值运算符。用移动语义以 other 的内容替换内容（即从 other 移动 other
    //中的数据到此容器中）。之后 other 处于合法但未指定的状态。
    set& operator=(set&& other){
        rb.head = other.head;
        other.set_head_null(); //防止析构后清除内存++++++++++++++++++++这里换种写法
        return *this;
    }

    //以 initializer_list ilist 所标识者替换内容。
    set& operator=(std::initializer_list<value_type>ilist){
        rb.release();
        for (auto it = init.begin(); it != init.end(); ++it) {
            rb.insert(*it);
        }
        return *this;
    }

    //=======================迭代器模块=========================
    //返回指向 set 首元素的迭代器。
    //如果 set 为空，那么返回的迭代器等于 end()。
    iterator begin(){}

    const_iterator begin() const{}

    const_iterator cbegin() const noexcept{}

    //返回指向 set
    //末元素后一元素的迭代器。此元素表现为占位符；试图访问它导致未定义行为。
    iterator end(){};

    const_iterator end() const{}

    const_iterator cend() const noexcept{}

    //返回指向逆向的 set 的首元素的逆向迭代器。
    //它对应非逆向 set 的末元素。如果set 为空，那么返回的迭代器等于 rend()。
    reverse_iterator rbegin() {}

    const_reverse_iterator rbegin()const{}

    const_reverse_iterator crbegin() const noexcept{}

    //返回指向逆向的 set 末元素后一元素的逆向迭代器。它对应非逆向 set
    //首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。
    reverse_iterator rend(){}

    const_reverse_iterator rend() const{}

    const_reverse_iterator crend() const noexcept{}

    //==============================容量模块=======================
    bool empty()const{
        if(rb.size()==0){
            return true;
        }
        return false;
    }

    size_type size() const{
        return rb.size();
    }

    //size_type max_size() const;

    //==============================修改器模块====================
    //从容器擦除所有元素。此调用后 size() 返回零。
    void clear(){
        rb.release();
    }

    //插入value++++++++++++++++++++++++++++++++++++++++++++++++++++++start here
    std::pair<iterator, bool> insert(const value_type&value){

    }
};

#endif
