//MiniList.h
#pragma once
#ifndef _Mini_List_H_
#define _Mini_List_H_

#include<cstddef>//ptrdiff_t size_t
#include<utility>//std::move

template<typename T>
class list{
private:

    class node{
        T value;
        node* prev;
        node* next;

        //node 构造函数
        node():value(),prev(nullptr),next(nullptr){}
        
        node(T v):value(v),prev(nullptr),next(nullptr){}

        node(T v,node* p,node* n=nullptr):value(v),prev(p),next(n){}

    };

    typedef node				node_type;
	typedef T 					value_type;
	typedef node_type*	 		pointer;
	typedef node_type&			reference;
	typedef const reference		const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;

    //成员变量-------------------------------------------------------------------
    pointer head;//指向链表头部的指针
    pointer tail;//指向链表尾部的指针

    //辅助函数-------------------------------------------------------------------
    //release():释放内存资源，指针置空。
    void release(){
        while(head!=nullptr){
            pointer tmp=head;
            head=head->next;
            delete tmp;
        }
        tail=nullptr;
    }
public:

    //迭代器---------------------------------------------------------------------
    //iterator


    //const_iterator



    //构造函数-------------------------------------------------------------------
    //从各种数据源构造新容器
    //默认构造函数
    list(){}

    //构造拥有count个值value的元素的容器

    //构造拥有count个默认插入的T实例的容器。

    //复制构造函数

    //移动构造函数

    //构造拥有初始化列表init内容的容器


    //析构函数-------------------------------------------------------------------
    //销毁list。调用各元素的析构函数，然后解分配所用的储存。注意，若元素是指针，则不销毁所指向的对象
    ~list(){
        release();
    }


    //赋值函数-------------------------------------------------------------------


    //容量模块-------------------------------------------------------------------

    
    //修改器模块-----------------------------------------------------------------


    //操作模块-------------------------------------------------------------------




};


//非成员函数模块----------------------------------------------



#endif