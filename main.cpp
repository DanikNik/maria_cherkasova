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
    Deque<int>::iterator it = deq1.Begin();
    Sort(deq1.Begin(), deq1.End());
    cout << deq1;
    cout << endl;
    return 0;
}