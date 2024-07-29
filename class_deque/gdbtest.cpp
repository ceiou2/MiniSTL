#include <iostream>
#include "MiniDeque.h"
using namespace std;

void printdeque(deque<int> dq)
{
    for (auto it = dq.start; it != dq.finish; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return;
}

int main()
{
    deque<int> d10{1, 2, 3, 4, 5};

    printdeque(d10);
    d10.push_back(6);
    cout << d10.back() << endl;

    // pop_back()
    d10.pop_back();

    // push_front()
    d10.push_front(10);

    printdeque(d10);

    // pop_front()
    d10.pop_front();

    // erase
    d10.erase(d10.begin());

    printdeque(d10);

    d10.erase(d10.begin() + 1);

    printdeque(d10);

    d10.erase(d10.begin() + 1, d10.end());

    printdeque(d10);

    // resize
    d10.resize(10);

    d10.resize(15, 3);

    d10.resize(10);

    d10.resize(10);

    // swap
    deque<int> dOther{1, 2, 3};
    d10.swap(dOther);
    return 0;
}
