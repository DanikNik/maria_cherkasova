//
// Created by daniknik on 19.05.18.
//

#include "Deque.h"
#include "Algorithm.h"
#include <iomanip>
using namespace std;
int main()
{
    Deque<int> deq1 = {10, 2, 3, -4, -2, 5, -124, 102};
    Deque<int> deq2 = Deque<int>(10);
    CopyIf(deq1.Begin(), deq1.End(), deq2.Begin(), [](int x){return x<0;});
    cout << deq2;
    cout << endl;
    return 0;
}