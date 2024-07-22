//MiniDeque
#pragma once
#ifndef _Mini_Deque_
#define _Mini_Deque_

#include<cstddef>
#include"MiniVector.h"

template<typename T>
class deque{
private:
    typedef T 					value_type;
	typedef value_type* 		pointer;
    typedef pointer*            map_pointer;//指向map元素的二级指针
	typedef value_type&			reference;
	typedef const reference		const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;
    typedef 128                 buffer_size;
    typedef T*                  buffer;


pubilc:

//=============================辅助功能模块======================
// //buffer 模块
// class buffer{//buffer数据结构
// public:
//     T* arr;

//     buffer(){
//         arr=new T[buffer_size](T());//buffer初始化
//     }

//     ~buffer(){//buffer析构函数
//         delete arr;
//         arr=nullptr;
//     }

    
// };



// class map{
// public:
//     vector<T> m;

// };

//==============================迭代器模块=======================
class iterator{
public:
    T* cur;
    T* first;
    T* last;
    map_pointer node;



    //构造函数
    iterator(){
        cur=nullptr;
        first=nullptr;
        last=nullptr;
        node=nullptr;
    }

    //重载*运算符
    reference operator*()const{
        return *cur;
    }

    //辅助函数
    void set_node(map_pointer newNode){
        node=newNode;
        first=*newNode;
        last=first+buffer_size;
    }

    //重载前置递增
    iterator& operator++(){
        ++cur;
        if(cur==last)//cur走到了最后一个元素的下一个位置
        {
            set_node(node+1);
            cur=first;
        }
        return *this;
    }

    //重载前置递减
    iterator& operator--(){
        if(cur==first)//cur移动到上一个buffer情况
        {
            set_node(node-1);
            cur=last-1;
        }
        --cur;
        return *this;
    }
};
//----------迭代器功能函数-------------
iterator begin(){
    return first;
}

iterator end(){
    return finish;
}

//=============================成员变量模块=======================

vector<T*> map;
iterator start;//指向第一个map节点
iterator finish;//指向最后一个map节点,finish->cur指向最后一个元素的下一个位置

//===============================辅助函数模块=====================
void add_buffer_back(){//尾部添加一个buffer
    buffer buff=new T[buffer_size];
    map.push_back(buff);
    //init finish
    finish->cur=buff;//最后一个元素的下一个位置
    finish->first=buff;//buffer第一个位置
    finish->last=buff+buffer_size;//buffer尾部的下一个位置
    ++(finish->node);
}

void _push_back(const T& value){
    if(map.size()==0){//处理空deque情况
        buffer buff=new T[buffer_size];
        map.push_back(buff);

        //init start
        start->cur=buff;//第一个元素的位置
        start->first=buff;
        start->last=buff+buffer_size;//buffer尾部的下一个位置
        start->node=map;

        //init finish
        finish->cur=buff+1;//最后一个元素的下一个位置
        finish->first=buff;
        finish->last=buff+buffer_size;//buffer尾部
        finish->node=map;

        //赋值
        *(buff+0)=value;

        return;
    }
    else if(finish->cur==finish->last){//尾部满了需要在尾部新添加一个buffer的情况
        add_buffer_back();//添加尾部一个buffer
        finish->cur=value;//赋值
        ++(finish->cur);//++末尾
        return;
    }
    else{
        finish->cur=value;
        ++(finish->cur);
        return;
    }

}

//释放空间，清空deque
void release(){
    for(size_type i=0;i<map.size();++i){//释放buffer
        delete *(map+i);
        *(map+i)=nullptr;
    }
    start=nullptr;
    finish=nullptr;
}


//***************************************************************
//==============================成员函数模块=======================

//构造函数
//默认构造函数
deque(){
    map.clear();
    start=iterator();
    finish=iterator();
}

deque(size_type count,const T& value = T()){
    while(count--){
        _push_back(value);
    }
}

//构造[first,last)内容的容器
template<typename InputIt>
deque(InputIt first,InputIt last){
    while(first!=last){
        _push_back(*first);
        ++first;
    }
}

//复制构造函数
deque(const deque& other){
    for(auto it=other.begin();it!=other.end();++it){
        _push_back(*it);
    }
}

//移动构造函数
deque(deque&& other){
    this->map=other.map;
    other.map.clear();
}

//列表初始化构造
deque(std::initializer_list<T> init){
    for(auto it=init.begin();it!=init.end();++it){
        _push_back(*it);
    }
}


//析构函数
~deque(){
    release();
}


//赋值函数
//拷贝赋值运算符
deque& operator=(const deque& other){
    release();//释放原空间
    for(auto it=other.begin();it!=other.end();++it){
        _push_back(*it);
    }
    return *this;
}

//移动赋值运算符
deque& operator=(deque&& other){
    release();//释放原空间
    this->map=other.map;
    other.map.clear();
    return *this;
}


//将值赋给容器
//以count份value的副本替换内容
void assign(size_type count, const T& value){
    release();
    while(count--){
        _push_back(value);
    }
}

//以范围 [first, last) 中元素的副本替换内容。
template<typename InputIt>
void assign(InputIt first,InputIt last){
    release();
    while(first!=last){
        _push_back(*first);
        ++first;
    }
}

//以来自 initializer_list ilist 的元素替换内容。
void assign(std::initializer_list<T> init){
    release();
    for(auto it=init.begin();it!=init.end();++it){
        _push_back(*it);
    }
}

//返回位于指定位置 pos 的元素的引用，有边界检查。
//若 pos 不在容器范围内，则抛出 std::out_of_range 类型的异常。
reference at(sizr_type pos){
    size_type map_offset=pos/buffer_size;//map偏移量（也是buffer组偏移量）
    size_type buffer_offset=pos%buffer_size;//buffer元素偏移量

    size_type last_elem_offset=0;//最后一个元素的下一个位置在最后一个buffer的偏移量
    for(pointer p=finish->first;p!=finish->cur;++p){
        ++last_elem_offset;
    }

    if(map.size()==0 || map_offset>map.size() || buffer_offset>=last_elem_offset){
        throw std::out_of_range("Index out of range");
    }
    return map[map_offset][buffer_offset];
}

const_reference at(size_type pos)const{
    size_type map_offset=pos/buffer_size;//map偏移量（也是buffer组偏移量）
    size_type buffer_offset=pos%buffer_size;//buffer元素偏移量

    size_type last_elem_offset=0;//最后一个元素的下一个位置在最后一个buffer的偏移量
    for(pointer p=finish->first;p!=finish->cur;++p){
        ++last_elem_offset;
    }

    if(map.size()==0 || map_offset>map.size() || buffer_offset>=last_elem_offset){
        throw std::out_of_range("Index out of range");
    }
    return map[map_offset][buffer_offset];
}

//返回位于指定位置 pos 的元素的引用。不进行边界检查。
reference operator[](size_type pos){
    size_type map_offset=pos/buffer_size;//map偏移量（也是buffer组偏移量）
    size_type buffer_offset=pos%buffer_size;//buffer元素偏移量

    return map[map_offset][buffer_offset];
}

const_reference operator[](size_type pos)const{
    size_type map_offset=pos/buffer_size;//map偏移量（也是buffer组偏移量）
    size_type buffer_offset=pos%buffer_size;//buffer元素偏移量

    return map[map_offset][buffer_offset];
}


//访问第一个元素
reference front(){
    return *(start->cur);
}

const_reference front()const{
    return *(start->cur);
}


//访问最后一个元素
reference back(){
    return *((finish->cur)-1);
}

const_reference back()const{
    return *((finish->cur)-1);
}


//检查容器是否无元素
bool empty()const{
    if(begin()==end())return true;
    return false;
}


//返回容器中的元素数量
size_type size() const{
    if(!map.size())return 0;//空deque的情况
    size_type sz=map.size()*buffer_size;//总容量

    //计算首尾两buffer的空余数量（注意单buffer的可能性）
    pointer tmp_s=start->cur;
    pointer tmp_f=finish->cur;//最后一个元素的下一个位置
    
    while(tmp_s!=start->first){//减去第一个buffer的空位置
        --sz;
    }

    if(start==finish)return sz;//单buffer的情况
    else{
        while(tmp_f!=finish->last){//减去最后一个buffer的空位置
            --sz;
        }
        return sz;
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++start here

void push_back(const T& value){
    _push_back(value);
}

};
















#endif