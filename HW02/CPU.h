//
// Created by siyah on 28.03.2016.
//

#include <string>
#include <vector>

using namespace std;

#ifndef HW02_CPU_H
#define HW02_CPU_H

struct ProcessTable{
    string processName;
    int pid;
    int ppid;
    int startTimeAsCPUTick;
    int elapsedTicks;
    char state;
    int startPoint;
};

class CPU{
public:
    CPU();
    ~CPU();

    void tick();
    bool isHalted();


private:
    vector<ProcessTable> procTable;
};

#endif //HW02_CPU_H
