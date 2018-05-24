//
// Created by daniknik on 19.05.18.
//

#include "Deque.h"
#include "Algorithm.h"
#include <iomanip>
using namespace std;

struct A{
    int a;
    int b;
};
int main()
{
    Deque<int> deq = {1, 2, 3, 4, 5, 6};
    Deque<int> deq2 = {-1, -2, -3, -4, -5};
    Deque<int>::iterator it = Deque<int>::iterator(deq, 3);
    deq.PushBack(10);
    deq.PushBack(20);
    deq.PushBack(30);
    deq.Insert(it, deq2.Begin(), deq2.End());
    cout << deq;

    return 0;
}