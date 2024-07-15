//MiniForwardList.h
#pragma once
#ifndef _Mini_Forward_List_h_
#define _Mini_Forward_list_h_

#include<cstddef>//ptrdiff_t  头文件

/*使用链表进行内存管理*/
template <typename T>
class forward_list{
	private:
	struct node{
		T value;
		node* next;
	}
	
	//node构造函数
	node():value(T()),next(nullptr){}

	node(value_type v):value(v),next(nullptr){}


	typedef node				node_type;
	typedef T 					value_type;
	typedef node_type*	 		pointer;
	typedef node_type*			iterator;
	typedef const node_type*	const_iterator;
	typedef node_type&			reference;
	typedef const reference		const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;

	//成员变量
	pointer head;//forward_list头节点
	
	pointer tail;//forward_list尾部节点的后一个节点

	size_type _size;//记录节点数量



		
	public:
	//-------------迭代器模块-----------
	//begin():获取第一个元素的迭代器
	iterator begin()const{return head;}

	//end()::获取forward_list最后一个元素的下一个位置的迭代器
	iterator end()const{return tail;}

	//-------------容量模块-----------
	//size():获取元素数量
	size_type size() const { return _size;}
	
	//empty():forward_list是否为空
	bool empty()const {return _size;}


	//-------------功能函数模块-----------


	//release():释放空间
	void release()
	{
		while(head)
		{
			pointer tmp_p=head;
			head=head->next;
			delete tmp_p;
		}
		_size=0;
		tail=nullptr;
	}

	//fill_initialize(size_type n,const T& value);
	void fill_initialize(size_type n,const T& value){
		_size=n;
		pointer tmp_p=head;
		while(n--)
		{
			pointer s=new node(value);
			tmp_p->next=s;
			tmp_p=tmp_p->next;
		}
	}

	//-------------构造函数模块-----------
	//默认构造函数
	forward_list():head(0),tail(0),_size(0){}

	//forward_list(size_type n,const T& value);
	forward_list(size_type n,const T& value):head(0),tail(0),_size(0){fill_initialize(n,value);}


	//列表初始化
	forward_list(std::initializer_list<T> init_list):head(0),tail(0),_size(0){
		initializer_list<T>::iterator tmp_it=init_list.begin();
		pointer tmp_p=head;
		while(tmp_it!=init_list.end())
		{
			++_size;
			pointer s=new node(*tmp_it);
			tmp_p=s;
			tmp_p=tmp_p->next;
		}
	}

	//拷贝构造函数:深拷贝版本
	forward_list(const forward_list& other):head(0),tail(0),_size(0){
		iterator other_p=other.begin();
		pointer tmp_p=head;
		while(other_p!=other.end())
		{
			++_size;
			pointer s=new node(*other_p);
			tmp_p=s;
			tmp_p=tmp_p->next;
		}

		
	}

	//移动构造函数
	forward_list(forward_list&& other){
		head=other.begin();
		_size=other.size();

		other.head=nullptr;//右值中指针置空防止析构时delete掉内存
		other._size=0;
	}
		

	//拷贝赋值函数
	forward_list& operator=(const forward_list& other){
		release();
		iterator other_p=other.begin();
		pointer tmp_p=head;
		while(other_p!=other.end())
		{
			++_size;
			pointer s=new node(*other_p);
			tmp_p=s;
			tmp_p=tmp_p->next;
		}
		return *this;//返回自身的引用以支持链式赋值
	}


	//移动赋值函数
	forward_list& operator=(forward_list&& other){
		release();
		head=other.begin();
		_size=other.size();

		other.head=nullptr;//右值中指针置空防止析构时delete掉内存
		other._size=0;

		return *this;//返回自身的引用以支持链式赋值
	}
		


	//forward_list(size_type n);
	explicit forward_list(size_type n):start(0),finish(0),end_of_storage(0){fill_initialize(n,T());}

	//~forward_list()
	~forward_list(){
		release();
	}

	void swap(forward_list& other)
	{
		if(this=&other) return;
		swap(_size,other._size);
		swap(head,other.head);
	}

	//-------------操作函数模块-----------
	reference front(){return *begin();}//第一个元素

	//start here----------------------------------我觉得要不先把设计文档写了先，迭代器好像不那么简单---------------------------start here 
	void push_back(const T& x){//将元素插入尾端
		if(finish!=end_of_storage){
			*finish=x;
			++finish;
		}
		else{
			reserve((capacity() == 0)?1:2*capacity());//空间分配，1或原空间翻倍 
			push_back(x);
		}
	}

	void pop_back(){//移除尾端元素
		--finish;
	}

	iterator erase(iterator position){//清除某位置上的元素
		if(position+1 != end())
		{
			fore_move(position);//后续元素向前移动
		}
		--finish;
		return position;
	}

	//iterator erase(iterator begin,iterator end)
	//略

	iterator insert(iterator position,const T& x){//在迭代器位置插入值，返回插入位置的迭代器
		if(finish!=end_of_storage)
		{
			++finish;
			back_move(position);
			*position=x;
		}
		else
		{
			size_type tmp_size=size_type(position-start);//处理position失效
			reserve((capacity() == 0)?1:2*capacity());//空间分配，1或原空间翻倍
			return insert(start+tmp_size,x);
		}
		return position;
		
	}

	//写一个move版本的insert规避迭代器失效
	
	void resize(size_type new_size,const T& x)//改变元素数量
	{
		if(new_size<=size())
		{
			finish=start+new_size;
		}
		else{
			reserve(new_size);
			while(finish!=start+new_size)
			{
				*finish=x;
				++finish;
			}
		}
	}

	void resize(size_type new_size){resize(new_size,T());}//重载

	void clear(){finish=start;}

	

	//assign
	void assign(size_type count,const T& value)//以count份 value的副本替换内容
	{
		*this=vector<T> (count,value);
	}

	void assign(const_iterator first,const_iterator last)//将区间[fast,last)的元素赋值到当前vector容器中，原内容释放，其中有任何一个实参是指向*this中的迭代器时行为未定义
	{
		release();
		reserve(last-first);
		for(size_type i=0;i<last-first;++i)
		{
			*(start+i)=*(first+i);
			++finish;
		}
	}





};





#endif
