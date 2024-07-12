#include<iostream>
#include"MiniVector.h"
//#include<vector>

using namespace std;

void printVec(const vector<int> & v)
{
	for(int i=0;i<v.size();++i)
	{
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

int main(){
	//test 构造
	vector<int> v1;
	vector<int> v2(10,2);
	vector<int> v3(5);

	cout<<v1.size()<<endl;//print: 0
	cout<<v1.capacity()<<endl;//print:0
	//printVec
	printVec(v2);//print 2 2 2 2 2 2 2 2 2 2 
	
	//testing here start
	//begin
	cout<<*v2.begin()<<endl;//print: 2

	//end
	cout<<*(v2.end()-1)<<endl;//print: 2


	//size
	cout<<v2.size()<<endl;//print: 10

	//capacity
	cout<<v2.capacity()<<endl;//print: 10

	//empty
	if(v1.empty())
	{
		cout<<"v1 is empty"<<endl;//print: v1 is empty
	}
	else
	{
		cout<<"bugged"<<endl;
	}

	//push_back
	v1.push_back(6);
	cout<<*v1.begin()<<endl;//print: 6
	v1.push_back(-1);
	v1.push_back(0);
	cout<<v1[2]<<endl;//print 0
	cout<<v1.capacity()<<endl; //print 4
	cout<<v1.size()<<endl; //print 3

	//operator[]
	v1[0]=20;
	cout<<*v1.begin()<<endl;//print 20
	cout<<v1.size()<<endl;//print 3

	//testing 02 start here
	cout<<"=========="<<endl;

	cout<<v1[v1.size()-1]<<endl;//print 0

	cout<<v1.size()<<endl;//print 3
	v1.pop_back();
	cout<<v1.size()<<endl;//print 2
	//cout<<v1[2]<<endl;

	cout<<v1.capacity()<<endl;//print 4
	v1.reserve(10);
	cout<<v1.capacity()<<endl;//print 10

	printVec(v1);//print 20 -1
	auto k=v1.erase(v1.begin());
	printVec(v1);//print -1
	
	vector<int>v(5,1);
	printVec(v);//print 1 1 1 1 1
	v.resize(10,2);
	printVec(v);//print 1 1 1 1 1 2 2 2 2 2 
	v.resize(3);
	printVec(v);//print 2 2 2

	cout<<v.capacity()<<endl;//print 10
	cout<<v.size()<<endl;//print 3
	v.clear();
	cout<<v.size()<<endl;//print 0

	cout<<"hhhhhh"<<endl;

	vector<int>vec;
	for(int i=0;i<5;++i){
		vec.push_back(i);
	}
	printVec(vec);//print 0 1 2 3 4

	vec.erase(vec.begin()+2);
	printVec(vec);//print 0 1 3 4

	vec.insert(vec.begin(),1);
	printVec(vec);//print 1 0 1 3 4

	vector<int>vec2(1,5);
	printVec(vec2);//print 5
	vec2.insert(vec2.begin(),3);
	printVec(vec2);//print 3 5
	
	//test 03 start right here
	cout<<"test 03 start right here"<<endl;

	//拷贝构造+++++++++++++++++++++++++++++++++start here------assign
	vector<int>vk1={1,2,3};
	printVec(vk1);//print 1 2 3
	vector<int>vk2(vk1);
	printVec(vk2);//print 1 2 3

	vk2.assign(vec2.begin(),vec2.end());
	printVec(vk2);//3 5
	cout<<vk2.capacity()<<endl;//2

	return 0;
}

