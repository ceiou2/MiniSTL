#include<iostream>
#include"MiniArray.h"

using namespace std;

int main()
{
	array<int,3> arr={1,2,3};
	for(int i=0;i<arr.size();++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
