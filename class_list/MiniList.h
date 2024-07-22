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
    public:
        node* current;

        //构造函数
        iterator(node* p):current(p){}

        //解引用操作
        T& operator*(){
            return current->value;
        }

        //迭代器递增操作
        //前置递增
        iterator& operator++(){
            current=current->next;
            return *this;
        }

        //后置递增
        iterator operator++(int){
            iterator temp=*this;
            ++*this;
            return temp;
        }

        //迭代器递减操作
        //前置递减
        iterator& operator--(){
            current=current->prev;
            return *this;
        }

        //后置递减
        iterator operator--(int){
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


    };


    //const_iterator
    class const_iterator{
    public:
        node* current;

        //构造函数
        const_iterator(node* p):current(p){}

        //解引用操作
        const T& operator*(){
            return current->value;
        }

        //迭代器递增操作
        //前置递增
        const_iterator& operator++(){
            current=current->next;
            return *this;
        }

        //后置递增
        const_iterator operator++(int){
            iterator temp=*this;
            ++*this;
            return temp;
        }

        //迭代器递减操作
        //前置递减
        const_iterator& operator--(){
            current=current->prev;
            return *this;
        }

        //后置递减
        const_iterator operator--(int){
            iterator temp=*this;
            --*this;
            return temp;
        }

        //迭代器比较操作
        bool operator==(const const_iterator& other)const{
            return current==other.current;
        }

        bool operator!=(const const_iterator& other)const{
            return current!=other.current;
        }


    };


    //reverse_iterator
    class reverse_iterator{
    public:
        node_type* current;

        //构造函数
        reverse_iterator(node_type* p):current(p){};

        T& operator*(){
            return current->value;
        }

        //迭代器移动
        reverse_iterator& operator++(){
            if(current==nullptr) return *this;
            current=current->prev;
            return *this;
        }

        reverse_iterator operator++(int){
            reverse_iterator temp=*this;
            ++*this;
            return temp;
        }

        reverse_iterator& operator--(){
            if(current==nullptr) return *this;
            current=current->next;
            return *this;
        }

        reverse_iterator operator--(int){
            reverse_iterator temp=*this;
            --*this;
            return temp;
        }

        //比较操作重载
        bool operator==(const reverse_iterator& other){
            if(current==other.current)return true;
            return false;
        }

        bool operator!=(const reverse_iterator& other){
            if(current==other.current)return false;
            return true;
        }


    };


    //cosnt_reverse_iterator
    class const_reverse_iterator{
    public:
        node_type* current;

        //构造函数
        const_reverse_iterator(node_type* p):current(p){};

        const T& operator*(){
            return current->value;
        }

        //迭代器移动
        const_reverse_iterator& operator++(){
            if(current==nullptr) return *this;
            current=current->prev;
            return *this;
        }

        const_reverse_iterator operator++(int){
            reverse_iterator temp=*this;
            ++*this;
            return temp;
        }

        const_reverse_iterator& operator--(){
            if(current==nullptr) return *this;
            current=current->next;
            return *this;
        }

        const_reverse_iterator operator--(int){
            reverse_iterator temp=*this;
            --*this;
            return temp;
        }

        //比较操作重载
        bool operator==(const const_reverse_iterator& other){
            if(current==other.current)return true;
            return false;
        }

        bool operator!=(const const_reverse_iterator& other){
            if(current==other.current)return false;
            return true;
        }


    };

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

    reverse_iterator rbegin(){
        return reverse_iterator(tail);
    }

    const_reverse_iterator rbegin()const{
        return const_reverse_iterator(tail);
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

    reverse_iterator rend(){
        return reverse_iterator(nullptr);
    }

    const_reverse_iterator rend()const{
        return const_reverse_iterator(nullptr);
    }

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
    bool empty()const{return head;}

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
            if(!head){delete del_p;return iterator(nullptr);}//防止单节点情况

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

    iterator erase(const_iterator pos){
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

    
    //插入元素到容器起始
    void push_front(const T& value){
        pointer newNode=new node(value,nullptr,head);

        if(head)head->prev=newNode;//防止空链表的情况

        head=newNode;

        if(!tail)tail=head;//防止空链表的情况
        
    }

    void push_front(T&& value){
        pointer newNode=new node(std::move(value),nullptr,head);

        if(head)head->prev=newNode;//防止空链表的情况

        head=newNode;

        if(!tail)tail=head;//防止空链表的情况
    }
    

    //emplace_front


    //移除首元素
    void pop_front(){
        pointer del_p=head;
        if(tail==head)tail=head->next;
        head=head->next;

        delete del_p;
        del_p=nullptr;

    }


    //改变储存元素的个数
    void resize(size_type count){
        size_type st=size();
        if(st==count)return;
        else if(st>count){
            size_type dist=st-count;
            while(dist--)
            {
                pop_back();
            }
            return;
        }
        else{
            size_type dist=count-st;
            while(dist--)
            {
                pop_back(T());
            }
            return;
        }
    }

    void resize(size_type count,const value_type& value){
        size_type st=size();
        if(st==count)return;
        else if(st>count){
            size_type dist=st-count;
            while(dist--)
            {
                pop_back();
            }
            return;
        }
        else{
            size_type dist=count-st;
            while(dist--)
            {
                pop_back(value);
            }
            return;
        }
    }


    //交换内容
    void swap(list&other)
    {
        swap(head,other.head);
        swap(tail,other.tail);
    }




    //操作模块-------------------------------------------------------------------
    //合并两个有序列表
    void merge(list&other){
        if(other==*this)return;

        pointer t_p=head;
        pointer o_p=other.head;

        size_type t_sz=size();
        size_type o_sz=other.size();
        size_type a_sz=t_sz+o_sz;//新链表大小

        pointer* sp=new pointer*[a_sz];//pointer*数组储存新链表顺序节点指针

        for(size_type i=0;i<a_sz;++i){//构造新列表节点指针数组
            if(((t_p && !o_p) || t_p->value<=o_p->value)&&t_p){
                sp[i]=t_p;
                t_p=t_p->next;
            }
            else{
                sp[i]=o_p;
                o_p=o_p->next;
            }
        }

        for(size_type i=0;i<a_sz;++i){//新列表导入*this
            head=nullptr;
            tail=nullptr;
            
            if(i==0){//首节点
                head=sp[i];
                tail=head;
                head->prev=nullptr;
            }
            else{//中间节点
                tail->next=sp[i];
                tail->next->prev=tail;
                tail=tail->next;
            }
        }
        tail->next=nullptr;//尾节点


        other.head=nullptr;//置空other
        other.tail=nullptr;

    }

    void merge(list&&other){
        if(other==*this)return;

        pointer t_p=head;
        pointer o_p=other.head;

        size_type t_sz=size();
        size_type o_sz=other.size();
        size_type a_sz=t_sz+o_sz;//新链表大小

        pointer* sp=new pointer*[a_sz];//pointer*数组储存新链表顺序节点指针

        for(size_type i=0;i<a_sz;++i){//构造新列表节点指针数组
            if(((t_p && !o_p) || t_p->value<=o_p->value)&&t_p){
                sp[i]=t_p;
                t_p=t_p->next;
            }
            else{
                sp[i]=o_p;
                o_p=o_p->next;
            }
        }

        for(size_type i=0;i<a_sz;++i){//新列表导入*this
            head=nullptr;
            tail=nullptr;
            
            if(i==0){//首节点
                head=sp[i];
                tail=head;
                head->prev=nullptr;
            }
            else{//中间节点
                tail->next=sp[i];
                tail->next->prev=tail;
                tail=tail->next;
            }
        }
        tail->next=nullptr;//尾节点


        other.head=nullptr;//置空other
        other.tail=nullptr;

    }


    //从另一个list中移动元素
    void splice(const_iterator pos, list& other){
        if(!other.head) return;//other为空链表

        if(pos==begin()){//pos=begin
            other.tail->next=head;
            head->prev=other.tail;

            head=other.head;
        }
        else
        {
        pointer p=pos->current;//pos
        pointer prevNode=p->prev;//pos->prev
        //前处链接点
        prevNode->next=other.head;
        prevNode->next->prev=prevNode;
        //后处链接点
        other.tail->next=p;
        p->prev=other.tail;
        }

        other.head=nullptr;//置空other
        other.tail=nullptr;
    }

    void splice(const_iterator pos, list&& other){
        if(!other.head) return;//other为空链表

        if(pos==begin()){//pos=begin
            other.tail->next=head;
            head->prev=other.tail;

            head=other.head;
        }
        else
        {
        pointer p=pos->current;//pos
        pointer prevNode=p->prev;//pos->prev
        //前处链接点
        prevNode->next=other.head;
        prevNode->next->prev=prevNode;
        //后处链接点
        other.tail->next=p;
        p->prev=other.tail;
        }

        other.head=nullptr;//置空other
        other.tail=nullptr;
    }

    //void splice(const_iterator pos,list& other,const_iterator it);...


    //移除满足特定标准的元素;ps:c++20标准返回size_type 删除的元素数量
    void remove(const T& value){
        for(auto it=begin();it!=end();++it){
            if(*it==value){
                it=erase(it);
                if(it==end())break;
            }
        }
    }

    //template<typename UnaryPredicate>
    //void remove_if(UnaryPredicate p);...


    //反转元素的顺序
    void reverse(){
        for(auto it=begin();it!=end();--it){//这里是--因为next和prev交换后--it才是指向下一个节点
            swap(it->next,it->prev);
        }
        swap(head,tail);
    }


    //删除连续的重复元素;ps:c++20标准返回size_type 删除的元素数量
    void unique(){
        for(auto it=begin();it!=end();++it){
            auto it2=++it;

            while(it2!=end() && *it==*it2){
                it2=erase(*it2);
            }
        }
    }
    
    //template<typename BinaryPredicate>
    //void unique(BinaryPredicate p);...


    //对元素进行排序
    void sort(){//bubble
        size_type sz=size();
        auto itje=iterator(tail);
        for(auto iti=begin();iti!=end();++iti)
        {
            for(auto itj=begin();itj!=itje;++itj)
            {
                if(*itj>itj->current->next->value){
                    swap(*itj,itj->current->next->value);
                }
            }
            --itje;
        }
    }

    //tempalte<typename Compare>
    //void sort(Compare comp);...

};


//非成员函数模块----------------------------------------------
//按照字典顺序比较两个list的值
template<typename T>
bool operator==(const list<T>& lhs,const list<T>& rhs){
    auto lit=lhs.begin();
    auto rit=rhs.begin();
    while(lit!=lhs.end() && rit!=rhs.end()){
        if(*lit!=*rit){
            return false;
        }
        else{
            ++lit;
            ++rit;
        }
    }
    if(lit==lhs.end() && rit==rhs.end()){
        return true;
    }
    return false;
}

template<typename T>
bool operator!=(const list<T>& lhs,const list<T>& rhs){
    if(lhs==rhs) return false;
    return true;
}

template<typename T>//小于或者长度小于
bool operator<(const list<T>& lhs,const list<T>& rhs){
    auto lit=lhs.begin();
    auto rit=rhs.begin();
    while(lit!=lhs.end() && rit!=rhs.end()){
        if(*lit<*rit){
            return true;
        }
        else if(*lit>*rit){
            return false;
        }
        else{
            ++lit;
            ++rit;
        }
    }
    if(lit==lhs.end() && rit!=rhs.end()){
        return true;
    }
    return false;
}

template<typename T>//小于等于或者长度小于等于
bool operator<=(const list<T>& lhs,const list<T>& rhs){
    if(lhs<rhs || lhs==rhs)return true;
    return false;
}

template<typename T>
bool operator>(const list<T>& lhs,const list<T>& rhs){
    return !(lhs<=rhs);
}

template<typename T>
bool operator>=(const list<T>& lhs,const list<T>& rhs){
    if(lhs>rhs || lhs==rhs)return true;
    return false;
}


//特化swap算法:algorithm
template<typename T>
void swap(list<T>& lhs,list<T>& rhs){
    lhs.swap(rhs);
}



#endif