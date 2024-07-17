//MiniList.h
#pragma once
#ifndef _Mini_List_H_
#define _Mini_List_H_

#include<cstddef>//ptrdiff_t size_t
#include<utility>//std::move
#include<limits>//std::numeric_limits<size_t>::max()

template<typename T>
class list{
private:

    class node{
        T value;
        node* prev;
        node* next;

        //node 构造函数
        // node():value(),prev(nullptr),next(nullptr){}
        
        // node(T v):value(v),prev(nullptr),next(nullptr){}

        // node(T v,node* p):value(v),prev(p),next(nullptr){}

        node(T v=T(),node* p=nullptr, node* n=nullptr):value(v),prev(p),next(n){}

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

    //fill_initialize:初始化n个有value值的双向链表
    void fill_initialize(size_type n,const T& value){
        head=new node();//哑节点
        tail=head;
        pointer tmp=head;
        while(n--)
        {
            tmp=new node(value);//tmp->新尾节点
            tail->next=tmp;//尾节点指向新尾节点
            tmp=tail;//tmp->旧尾节点
            tail=tail->next;//更新尾节点
            tail->prev=tmp;//新尾节点前指向旧尾节点
        }
        tmp=head;
        head=head->next;
        head->prev=nullptr;
        delete tmp;//删除哑节点

    }

    //push_back:将尾部插入一个新节点,值为value
    void push_back(const T& value){
        if(head==nullptr) fill_initialize(1,value);
        /*
        if(head==nullptr){
        head=new node(value);
        tail=head;
        }
        */

        pointer tmp=new node(value);
        tail->next=tmp;
        tmp=tail;
        tail=tail->next;
        tail->prev=tmp;

    }


public:

    //迭代器---------------------------------------------------------------------
    //iterator
    class iterator{
    private:
        node* current;

    public:
        //构造函数
        iterator(node* p):current(p){}

        //解引用操作
        T& operator*(){
            return current->value;
        }

        //迭代器递增操作
        //前置递增
        Iterator& operator++(){
            current=current->next;
            return *this;
        }

        //后置递增
        Iterator operator++(int){
            iterator temp=*this;
            ++*this;
            return temp;
        }

        //迭代器递减操作
        //前置递减
        Iterator& operator--(){
            current=current->prev;
            return *this;
        }

        //后置递减
        Iterator operator--(int){
            iterator temp=*this;
            --*this;
            return temp;
        }

        //迭代器比较操作
        bool operator==(const iterator& other)const{
            return current==other.current;
        }

        bool operator!=(const iterator& other)const{
            return current!=other.current;
        }


    }


    //const_iterator
    class const_iterator{
    private:
        node* current;

    public:
        //构造函数
        const_iterator(node* p):current(p){}

        //解引用操作
        const T& operator*(){
            return current->value;
        }

        //迭代器递增操作
        //前置递增
        const_Iterator& operator++(){
            current=current->next;
            return *this;
        }

        //后置递增
        const_Iterator operator++(int){
            iterator temp=*this;
            ++*this;
            return temp;
        }

        //迭代器递减操作
        //前置递减
        const_Iterator& operator--(){
            current=current->prev;
            return *this;
        }

        //后置递减
        const_Iterator operator--(int){
            iterator temp=*this;
            --*this;
            return temp;
        }

        //迭代器比较操作
        bool operator==(const iterator& other)const{
            return current==other.current;
        }

        bool operator!=(const iterator& other)const{
            return current!=other.current;
        }


    }


    //逆向迭代器+++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //返回指向起始的迭代器
    iterator front(){
        return iterator(head);
    }

    const_iterator begin()const{
        return const_iterator(head);
    }

    const_iterator cbegin()const{
        return const_iterator(head);
    }

    //返回指向末尾的迭代器
    iterator end(){
        return iterator(nullptr);
    }

    const_iterator end()const {
        return const_iterator(nullptr);
    }

    const_iterator cend()const{
        return const_iterator(nullptr);
    }

    //逆向迭代器
    //++++++++++++

    //构造函数-------------------------------------------------------------------
    //从各种数据源构造新容器
    //默认构造函数
    list():head(nullptr),tail(nullptr){}

    //构造拥有count个值value的元素的容器
    explicit list(size_type count,const T& value){
        fill_initialize(count,value);
    }

    //构造拥有count个默认插入的T实例的容器。
    explicit list(size_type count){fill_initialize(count,T());}

    //复制构造函数
    list(const list& other){
        pointer o_head=other.head;
        while(o_head!=nullptr)
        {
            push_back(o_head->value);
        }
    }

    //移动构造函数
    list(list&& other){
        head=other.head;
        tail=other.tail;

        //other指针置空，防止析构时释放内存
        other.head=nullptr;
        other.tail=nullptr;
    }

    //构造拥有初始化列表init内容的容器
    list(std::initializer_list<T>init){
        for(auto it=init.begin();it!=init.end();++it)
        {
            push_back(*it);
        }
    }


    //析构函数-------------------------------------------------------------------
    //销毁list。调用各元素的析构函数，然后解分配所用的储存。注意，若元素是指针，则不销毁所指向的对象
    ~list(){
        release();
    }


    //赋值函数-------------------------------------------------------------------
    //拷贝赋值运算符
    list& operator=(const list& other){
        release();//释放原容器内存
        pointer o_head=other.head;
        while(o_head!=nullptr)
        {
            push_back(o_head->value);
        }
    }

    //移动复制运算符
    list& operator=(list&& other)
    {
        release();//释放原容器内存
        head=other.head;
        tail=other.tail;

        //other指针置空，防止析构时释放内存
        other.head=nullptr;
        other.tail=nullptr;
    }

    //assign


    //容量模块-------------------------------------------------------------------
    bool empty()const{return head}

    size_type size()const{
        size_type s=0;
        for(pointer p=head;p!=nullptr;p=p->next){
            ++s;
        }
        return s;

        /*
        size_type s=0;
        for(iterator it=begin();it!=end();++it)
        {
            ++s;
        }
        return s;
        */
    }

    size_type max_size()const{
        return std::numeric_limits<size_t>::max();
    }

    
    //修改器模块-----------------------------------------------------------------
    //清除内容
    void clear(){
        release();
    }


    //插入元素 返回(首个)被插入元素的迭代器
    //在pos前插入value
    iterator insert(const_iterator pos, const T& value){
        pointer cur=pos->current;
        pointer tmp=new node(value,cur->prev,cur);
        if(!cur->prev){cur->prev->next=tmp;}
        cur->prev=tmp;
        return iterator(tmp);
        
    }
    iterator insert(const_iterator pos, T&& value){
        pointer cur=pos->current;
        pointer tmp=new node(std::move(value),cur->prev,cur);//显示表达move中value是右值，可以不move因为已经是右值，不影响
        if(!cur->prev){cur->prev->next=tmp;}
        cur->prev=tmp;
        return iterator(tmp);
    }
    
    //在pos前插入value的count个副本
    iterator insert(const_iterator pos, size_type count, const T& value){
        auto npos=pos;
        while(count--){
            npos=insert(npos,value);
        }
        return iterator(npos->current);
    }

    //在pos前插入来自范围[first,last)的元素
    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last){
        auto npos=pos;
        for(auto it=first;it!=last;++it)
        {
            npos=insert(npos,*it);
        }
        return iterator(npos->current);
    }

    //在pos前插入来自初始化列表ilist的元素
    iterator insert(const_iterator pos, std::initializer_list<T> ilist){
        auto npos=pos;
        for(auto it=ilist.being();it!=ilist.end();++it)
        {
            npos=insert(npos,*it);
        }
        return iterator(npos->current);
    }

    //擦除元素
    //从容器擦除指定的元素,返回end()或删除元素的下一个位置
    iterator erase(iterator pos){
        pointer cur=pos.current;
        if(!cur) return iterator(nullptr);//防止传入end()

        pointer del_p=cur;//用于释放内存
        //头部情况
        if(cur==head){
            head=head->next;
            if(!head){delete del_p;return iterator(nullptr)}//防止单节点情况

            head->prev=nullptr;
            delete del_p;
            return iterator(head);
        }
        else if(cur==tail){
            tail=tail->prev;
            //if(!tail){delete del_p;return iterator(nullptr)}//防止单节点情况

            tail->next=nullptr;
            delete del_p;
            return iterator(tail);
        }
        else{
            if(cur->prev){
                cur->prev->next=cur->next;
            }

            if(cur->next){
                cur->next->prev=cur->prev;
            }
            cur=cur->next;
            delete del_p;
            return iterator(cur);
        }

    }

    iterator erase(cosnt_iterator pos){
        pointer cur=pos.current;
        if(!cur) return iterator(nullptr);//防止传入end()

        pointer del_p=cur;//用于释放内存
        //头部情况
        if(cur==head){
            head=head->next;
            if(!head){
            delete del_p;
            tail=nullptr;
            return iterator(nullptr);}//防止单节点情况

            head->prev=nullptr;
            delete del_p;
            return iterator(head);
        }
        else if(cur==tail){
            tail=tail->prev;
            //if(!tail){delete del_p;return iterator(nullptr);}//防止单节点情况

            tail->next=nullptr;
            delete del_p;
            return iterator(tail);
        }
        else{
            if(cur->prev){
                cur->prev->next=cur->next;
            }

            if(cur->next){
                cur->next->prev=cur->prev;
            }
            cur=cur->next;
            delete del_p;
            return iterator(cur);
        }
    }

    //删除[first,last)区间的元素
    iterator erase(iterator first,iterator last){
        if(first==last){return end();}

        while(first!=last)
        {
            erase(first);
            ++first;
        }

        return last;
    }

    iterator erase(const_iterator first,const_iterator last){
        if(first==last){return end();}

        while(first!=last)
        {
            erase(first);
            ++first;
        }

        return last;
    }

    //将元素添加到容器末尾
    //push_back:definition is at line:74

    //emplace_back


    //移除末尾元素
    void pop_back(){
        erase(iterator(tail));
    }

//+++++++++++++++++++++++++++++++++++++++start here++++end() sentinel节点



    //操作模块-------------------------------------------------------------------




};


//非成员函数模块----------------------------------------------



#endif