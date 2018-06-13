//
// Created by daniknik on 19.05.18.
//

#include "Deque.h"
#include "Algorithm.h"
#include <iomanip>
using namespace std;

struct students{
    unsigned id;
    string name;
    string group;
    double last_mark;
};


int main()
{

    Deque<students> deq = Deque<students>();
    for (int i = 0; i < 5; ++i) {
        students new_student;
        cout << "[>] Enter id, name, group and last mark\n";
        cin >> new_student.id >> new_student.name >> new_student.group >> new_student.last_mark;
        deq.PushBack(new_student);
    }
    Deque<students> deq1 = {{12, "grisha", "11", 2.0},
                            {101, "borya", "11", 4.7},
                            {1704, "sigizmund", "12", 6.0},
                            {104, "henessy", "VSOP", 40.0}};
    deq.Insert(deq.Begin(), deq1.Begin(), deq1.End());
    ForEach(deq.Begin(), deq.End(), [](students a){cout << a.id << ' ' << a.name << ' ' << a.group << ' ' << a.last_mark << endl; return a;});

    Deque<students> deq2 = Deque<students>(deq1.Size());
    CopyIf(deq1.Begin(), deq1.End(), deq2.Begin(), [](students a){return a.group == "11";});
    ForEach(deq2.Begin(), deq2.End(), [](students a){cout << a.id << ' ' << a.name << ' ' << a.group << ' ' << a.last_mark << endl; return a;});

    double min = deq1[0].last_mark;
    for (int j = 0; j < deq1.Size(); ++j) {
        if (min > deq1[j].last_mark) min - deq[j].last_mark;
    }
    Deque<students>::iterator it = FindIf(deq1.Begin(), deq1.End(), [min](students a){return a.last_mark == min;});
    cin >> it -> group;
    ForEach(deq1.Begin(), deq1.End(), [](students a){cout << a.id << ' ' << a.name << ' ' << a.group << ' ' << a.last_mark << endl; return a;});
    return 0;
}