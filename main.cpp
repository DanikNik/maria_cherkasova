//
// Created by daniknik on 19.05.18.
//

#include "Deque.h"
#include "Algorithm.h"
#include <iomanip>
using namespace std;
int main()
{
    Deque<int> deq1 = {-10, -2, -3, -41, 0, -5, -124, -102};
    Deque<int> deq2 = {1, 2, 3, 4, 5};
    auto it = DequeIterator<int>(deq1, 3);
    deq1.Insert(it, deq2.Begin(), deq2.End());
    cout << deq1;
    cout << endl;
    return 0;
}