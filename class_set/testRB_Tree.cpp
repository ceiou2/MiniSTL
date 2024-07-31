#include<iostream>
#include"RB_Tree.h"

int main()
{
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    //int arr[] = {4, 2, 6, 1, 3, 5, 15, 7, 16};
    RBTree<int, int> a;
	for (auto e : arr)
	{
		a.insert(std::make_pair(e, e));
	}
    a.InOrder_Traversal();

    a.erase(3);

    a.InOrder_Traversal();

    a.erase(2);

    a.InOrder_Traversal();
    a.erase(3);

    a.InOrder_Traversal();
    a.erase(4);

    a.InOrder_Traversal();
    a.erase(5);

    a.InOrder_Traversal();
    return 0;
}

