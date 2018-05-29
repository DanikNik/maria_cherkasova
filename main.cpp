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
    Deque<int> deq1 = Deque<int>();							//default
    Deque<A> deq2 = Deque<A>(10);							//with len
    Deque<int> deq3 = Deque<int>(15, 1);		//with len and default
    Deque<int> deq4 = Deque<int>(deq3.Begin(), deq3.End());
    Deque<A> deq0 = Deque<A>(deq2);
    Deque<int> deq5 ={1, 2, -3, 4, 5, 6};

    cout << deq5.at(4) << endl;
    deq1.PushBack(180);
    deq1.PushFront(90);
    cout << deq1.PopBack() << endl;
    cout << deq1.PopFront() << endl;
    Deque<int>::iterator it = Deque<int>::iterator(deq5, 3);
    deq5.Insert(it++, 100);
    deq5.Insert(++it, deq3.Begin()+2, deq3.End()-5);
    cout << deq5; cout << endl;
    deq5.Erase(it + 3);
    deq3.Resize(25);
    cout << deq1.Empty() << endl;
    cout << deq3.Size() << endl;

    Deque<int>::iterator it_find = FindIf(deq5.Begin(), deq5.End(), [](int x){return x < 0;});

    Deque<int>::iterator it_min = MinElement(deq5.Begin(), deq5.End());

    Deque<int>::iterator it_max = MaxElement(deq5.Begin(), deq5.End());

    Sort(deq5.Begin(), deq5.End());

    ForEach(deq5.Begin(), deq5.End(), [](int x){return 2*x;});

    cout << *it_find << endl;
    cout << *it_max << endl;
    cout << *it_min << endl;
    cout << deq5 << endl;


    return 0;
}