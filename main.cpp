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
    Deque<int> deq1 = {-1, -2, -3, -4, -5, -6};
    Deque<int>::iterator it = deq.Begin();
    deq.Insert(it, deq1.Begin(), deq1.End());
    cout << deq;

    return 0;
}