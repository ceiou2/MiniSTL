//MiniVector.h
#pragma once
#ifndef _MiniVector_h_
#define _MiniVector_h_

#include<cstddef>//ptrdiff_t  头文件

/*使用动态数组new进行内存管理*/
template <typename T>
class vector{
	private:
	typedef T 					value_type;
	typedef value_type* 		pointer;
	typedef value_type*			iterator;
	typedef const value_type*	const_iterator;
	typedef value_type&			reference;
	typedef const reference		const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;

	private:
	iterator start;
	iterator finish;
	iterator end_of_storage;

	public:
	//-------------迭代器模块-----------
	//begin():获取第一个元素的迭代器
	iterator begin()const{return start;}

	//end()::获取vector最后一个元素的下一个位置的迭代器
	iterator end()const{return finish;}

	//-------------容量模块-----------
	//size():获取元素数量
	size_type size() const { return size_type(end()-begin());}
	
	//capacity():获取容器容量
	size_type capacity()const{return size_type(end_of_storage-begin());}

	//empty():vector是否为空
	bool empty()const {return begin()==end();}

	//operator[]:随机访问
	reference operator[](size_type n){return *(begin()+n);}

	//operator[]:const版本
	const_reference operator[](size_type n) const {return *(begin()+n);}

	//reserve:分配新空间并转移
	void reserve(size_type new_cap){
		//开辟空间
		pointer tmp_pointer = new value_type[new_cap];
		
		size_type _size=size();// 因为size()通过finish-start计算，但届时将改变该两指针的指向

		//转移数据
		if(start)
		{
			for(size_type i=0;i<_size;++i)
			{
				tmp_pointer[i]=start[i];
			}

			//release
			delete[] start;
		}
		start=tmp_pointer;
		finish=start+_size;
		end_of_storage=start+new_cap;
		
	}




	//-------------功能函数模块-----------


	//fill_initialize(size_type n,const T& value);
	void fill_initialize(size_type n,const T& value){
		reserve(n);
		finish=start+n;//set size
		for(size_type i=0;i<size();++i)
		{
			start[i]=value;
		}
	}

	//release():释放空间
	void release()
	{
		delete[] start;
		start=nullptr;
		finish=nullptr;
		end_of_storage=nullptr;
	}

	//fore_move():元素向前移动
	void fore_move(iterator position){
		if(position==end()) return;
		while(position+1!=end())
		{
			*position=*(position+1);
			++position;
		}
	}

	//back_move():元素向后移动一位
	void back_move(iterator position){
		if(position==end()) return;
		for(iterator it = finish-1;it!=position;--it)
		{
			if(it==begin())return;
			*it=*(it-1);
		}
	}


	//-------------构造函数模块-----------
	//默认构造函数
	vector():start(0),finish(0),end_of_storage(0){};

	//vector(size_type n,const T& value);
	vector(size_type n,const T& value):start(0),finish(0),end_of_storage(0){fill_initialize(n,value);}

	//vector(int n,const T& value)注：官方文档有这两个函数，但是size_type应该够用，暂时不知道这两个函数的定义有什么作用
	//vector(long n,const T& value)

	//列表初始化
	vector(std::initializer_list<T> init_list):start(0),finish(0),end_of_storage(0){
		//reserve(init_list.end()-init_list.begin());
		//std::copy(init_list.begin(),init_list.end(),start);
		//release();
		reserve(init_list.end()-init_list.begin());
		for(size_type i=0;i<init_list.end()-init_list.begin();++i)
		{
			*(start+i)=*(init_list.begin()+i);
			++finish;
		}
	}

	//拷贝构造函数:深拷贝版本
	vector(const vector& ori_vector):start(0),finish(0),end_of_storage(0){
		reserve(ori_vector.capacity());
		for(size_type i=0;i<ori_vector.size();++i)
		{
			*(start+i)=*(ori_vector.begin()+i);
			++finish;
		}
		
	}

	//移动构造函数
	vector(vector&& ori_vector){
		start=ori_vector.begin();
		finish=ori_vector.end();
		end_of_storage=start+ori_vector.capacity();

		ori_vector.start=nullptr;//右值中指针置空防止析构时delete掉内存
		ori_vector.finish=nullptr;
		ori_vector.end_of_storage=nullptr;
	}
		

	//拷贝赋值函数
	vector& operator=(const vector& ori_vector){
		release();
		reserve(ori_vector.capacity());
		for(size_type i=0;i<ori_vector.size();++i)
		{
			*(start+i)=*(ori_vector.begin()+i);
			++finish;
		}
		return *this;//返回自身的引用以支持链式赋值
	}


	//移动赋值函数
	vector& operator=(vector&& ori_vector){
		release();
		start=ori_vector.begin();
		finish=ori_vector.end();
		end_of_storage=start+ori_vector.capacity();

		ori_vector.start=nullptr;//右值中指针置空防止析构时delete掉内存
		ori_vector.finish=nullptr;
		ori_vector.end_of_storage=nullptr;

		return *this;//返回自身的引用以支持链式赋值
	}
		


	//vector(size_type n);
	explicit vector(size_type n):start(0),finish(0),end_of_storage(0){fill_initialize(n,T());}

	//~vector()
	~vector(){
		release();
	}

	void swap(vector& other)
	{
		if(this=&other) return;

		swap(this->start,other.start);
		swap(this->finish,other.finish);
		swap(this->end_of_storage,other.end_of_storage);
	}

	//-------------操作函数模块-----------
	reference front(){return *begin();}//第一个元素

	reference back(){return *(end()-1);}//最后一个元素

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
