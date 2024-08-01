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
    if(!a.IsBalance()){
        return 0;
    }

    std::cout << "erase3" << std::endl;
    a.erase(3);
    a.InOrder_Traversal();

    std::cout << "erase2" << std::endl;
    a.erase(2);
    a.InOrder_Traversal();
    // a.erase(3);

    // a.InOrder_Traversal();
    std::cout << "erase4" << std::endl;
    a.erase(4);
    a.InOrder_Traversal();

    std::cout << "erase5" << std::endl;
    a.erase(5);
    a.InOrder_Traversal();

    std::cout << "erase7" << std::endl;
    a.erase(7);
    a.InOrder_Traversal();
    if (!a.IsBalance()) {
        return 0;
    }

    std::cout << "erase1" << std::endl;
    a.erase(1);
    a.InOrder_Traversal();
    if (!a.IsBalance()) {
        return 0;
    }

    std::cout << "erase15" << std::endl;//==============
    a.erase(15);
    a.InOrder_Traversal();
    if (!a.IsBalance()) {
        return 0;
    }

    std::cout << "erase16" << std::endl;
    a.erase(16);
    a.InOrder_Traversal();

    std::cout << "erase14" << std::endl;
    a.erase(14);
    a.InOrder_Traversal();

    a.erase(1);
    a.InOrder_Traversal();

    std::cout << "erase6" << std::endl;
    a.erase(6);
    a.InOrder_Traversal();
    return 0;
}

