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
    Deque<int> deq1 = Deque<int>();
    Deque<char> deq2 = Deque<char> (10);
    Deque<double> deq3 = Deque<double> (10, 1.15);
    Deque<double> deq4 = Deque<double>(deq3);
    Deque<double> deq5 = Deque<double>(deq3.Begin(), deq3.End());
    Deque<int> deq6 = {1, 2, 3, 4, 5};
    deq1.PushBack(10);
    deq1.PushFront(12);
    cout << deq6;
    cout << endl;
    cout << deq1.PopBack() << endl;
    cout << deq3.at(2);
    cout << endl;
    cout << deq3[2];
    cout << endl;

    deq6.Insert(deq6.Begin(), -4);
    deq1.Insert(deq1.Begin(), deq6.Begin(), deq6.End());

    deq4.Resize(128);
    cout << deq5.Empty() << endl;
    cout << deq4.Size() << endl;

    deq4.Clear();
    cout << deq4.Size() << endl;

    Deque<int>::iterator it = Deque<int>::iterator (deq6, 0);
    cout << *(it) << endl;

    Deque<int>::iterator it1 = FindIf(deq6.Begin(), deq6.End(), [](int x){return x == 4;});
    cout << *(--it1) << endl;

    deq6[3] = -10;
    cout << deq6;
    cout << endl;
    Sort(deq6.Begin(), deq6.End());
    cout << deq6;
    cout << endl;
    deq6.Erase(deq6.Begin());
    cout << *(MaxElement(deq6.Begin(), deq6.End())) << ' ' << *(MinElement(deq6.Begin(), deq6.End())) << endl;

    ForEach(deq6.Begin(), deq6.End(), [](int x){return 2*x;});
    cout << deq6;
    cout << endl;

    return 0;
}