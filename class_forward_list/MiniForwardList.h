//MiniForwardList.h
#pragma once
#ifndef _Mini_Forward_List_h_
#define _Mini_Forward_list_h_

#include<cstddef>//ptrdiff_t size_t 头文件
#include<limits>//std::numeric_limits<size_t>::max()
#include<utility>//std::move

/*使用链表进行内存管理*/
template <typename T>
class forward_list{
	private:
	struct node{
		T value;
		node* next;
	};
	
	//node构造函数
	node():value(T()),next(nullptr){}

	node(value_type v):value(v),next(nullptr){}

	node(value_type v,node* n):value(v),next(n){}


	typedef node				node_type;
	typedef T 					value_type;
	typedef node_type*	 		pointer;
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
	class iterator{
		private:
		node* current;

		public:
		//构造函数
		iterator(node *p):current(p){}

		// 解引用操作符
        T& operator*() const { return current->value; }

        // 递增操作符（前置）
        iterator& operator++() {
            current = current->next;
            return *this;
        }

        // 递增操作符（后置）
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

		pointer operator->()const{
			return &(current->value);
		}

        // 比较操作符
        bool operator!=(const iterator& other) const { return current != other.current; }
        bool operator==(const iterator& other) const { return current == other.current; }
	};

	class const_iterator{
		private:
		node* current;

		public:
		//构造函数
		const_iterator(node *p):current(p){}

		const_iterator(iterator it):current(it->current){}

		// 解引用操作符
        const T& operator*() const { return current->value; }

		const pointer operator->()const{
			return &(current->value);
		}

        // 递增操作符（前置）
        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        // 递增操作符（后置）
        const_iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }


        // 比较操作符
        bool operator!=(const const_iterator& other) const { return current != other.current; }
        bool operator==(const const_iterator& other) const { return current == other.current; }
	};

	//begin():获取第一个元素的迭代器
	iterator begin()const{return head;}

	//end()::获取forward_list最后一个元素的下一个位置的迭代器
	iterator end()const{return tail;}

	//-------------容量模块-----------
	//size():获取元素数量
	size_type max_size() const { return std::numeric_limits<size_t>::max();}
	
	//empty():forward_list是否为空
	bool empty()const {return _size;}


	//-------------辅助函数模块-----------


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


	//------------元素访问----------------
	reference front(){return *begin();}//第一个元素

	//------------修改器模块--------------
	void swap(forward_list& other)//交换内容
	{
		if(this=&other) return;
		swap(_size,other._size);
		swap(head,other.head);
	}


	//从容器擦除所有元素
	void clear()
	{release();}



	//将元素插入链表头部
	void push_front(const T& x){
		node *tmp=new node(x);
		tmp->next=head;
		head=tmp;
		++_size;
	}

	void push_front(T&& value);
	{
		node* newNode = new node(value);
		newnode->next=head;
		head=newnode;
	}

	//emplace_front

	//prepend_range

	//移除首端元素
	void pop_front(){
		if(!head) return;
		node* tmp=head;
		head=head->next;
		delete tmp;
		tmp=nullptr;
		--_size;
	}

		//在容器中的指定位置后插入元素
	iterator insert_after( const_iterator pos, const T& value)
	{
		if(pos.current==nullptr){
			//如果pos为尾后迭代器
			if(head) return pos;//防止链表不为空时传入end()
			head=new node(value);
		}
		pos->next=new node(value,pos->next);
		return pos->next;
	}

	iterator insert_after(const_iterator pos, T&& value)
	{
		if(pos.current==nullptr){
			//如果pos为尾后迭代器
			if(head) return pos;//防止链表不为空时传入end()
			head=new node(value);
		}
		pos->next=new node(value,pos->next);
		return pos->next;
	}

	iterator insert_after(const_iterator pos,size_type count,const T& value)
	{
		if(pos.current==nullptr){
			//如果pos为尾后迭代器
			if(head) return pos;//防止链表不为空时传入end()
			head=new node(value);
			--count;
			pos.current=head;
		}
		while(count--)
		{
			pos->next=new node(value,pos->next);
		}
		return pos->next;
	}

	template<typename InputIt>
	iterator insert_after(const_iterator pos, InputIt first, InputIt last)
	{
		if(pos.current==nullptr){
			//如果pos为尾后迭代器
			if(head) return pos;//防止链表不为空时传入end()
			head=new node(value);
			pos.current=head;
			++first;
		}
		node* prevNode=pos.current;//插入位置
		node* newhead=new node();//新链表,哑节点
		node* newnode=newhead;//新链表的尾部插入位置
		iterator res=nullptr;
		for(auto it=first;it!=last;++it)
		{
			newnode->next=new node(*it);
			newnode=newnode->next;
		}
		res=iterator(newnode);//返回最后被插入元素的迭代器
		newnode->next=prevNode->next;//新链表尾部链接原链表插入的后一个节点
		newnode=newhead->next;
		prevNode->next=newnode;//原链表插入节点的next链接新链表
		delete newhead;//删除哑节点
		return res;//返回最后被插入元素的迭代器
	}

	//iterator insert_after(const_iterator pos,std::initializer_list<T> ilist);

	//template<class... Arg>
	//iterator emplace_after(const_iterator pos, Args&&... args);

	//从容器移除指定元素
	iterator erase_after(const_iterator pos)//移除pos后的元素
	{
		node* curnode=pos->current;
		if(!curnode->next) return end();
		node* tmp=curnode->next;
		curnode->next=curnode->next->next;
		delete tmp;
		return iterator(curnode->next);
	}

	iterator erase_after(const_iterator first, const_iterator last)//移除first后直至last前的元素
	{
		iterator it=iterator(first->current);
		while(first!=last)
		{
			first=erase_after(const_iterater(first->current));
		}
		return last;
	}
	

	//改变储存元素的个数
	void resize(size_type count)
	{
		if(count==_size)return;
		else if(count<_size)//减小到前count个元素
		{
			const_iterator first=begin();
			const_iterator last=end();
			size_type st=_size-count;
			while(st--)
			{
				++first;
			}
			erase_after(first,last);
		}
		else if(count>_size)//追加额外的默认插入的元素
		{
			size_type st=count-_size;
			size_type steps=_size;
			auto pos=begin();
			while(--steps)
			{
				++pos;
			}
			insert_after(pos,st,T());
		}
	}

	void resize(size_type count, const value_type& value)
	{
		if(count==_size)return;
		else if(count<_size)//减小到前count个元素
		{
			const_iterator first=begin();
			const_iterator last=end();
			size_type st=_size-count;
			while(st--)
			{
				++first;
			}
			erase_after(first,last);
		}
		else if(count>_size)//追加额外的默认插入的元素
		{
			size_type st=count-_size;
			size_type steps=_size;
			auto pos=begin();
			while(--steps)
			{
				++pos;
			}
			insert_after(pos,st,value);
		}
	}

	//prepend_range

	

	//----------------操作模块------------------
	
	//start here ----------------------------------------操作

};





#endif
