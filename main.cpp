//
// Created by daniknik on 19.05.18.
//

#include "Deque.h"
#include "Algorithm.h"
#include <iomanip>
using namespace std;
int main()
{
    Deque<int> deq1 = {10, 2, 3, 4, 0, 5, 124, 102};
    deq1.Resize(20);
    cout << deq1;
    cout << endl;
    return 0;
}