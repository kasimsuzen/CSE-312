//
// Created by siyah on 28.03.2016.
//

#include <string>
#include <vector>
#include "Process.h"

using namespace std;

#ifndef HW02_CPU_H
#define HW02_CPU_H

namespace {
    int elapsedTime = 0;
}

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
    CPU(int md);
    ~CPU();

    void tick();
    bool isHalted();

    static bool addProcess(string fileName, int pid, int md, int pcValue=0);
    bool updateProcessList();
    static vector<Memory> memoryData;
    static int indexOfMem;
    static vector<ProcessTable> processTable;
private:
    vector<Process> loadedProcess;
    int mode;
};

#endif //HW02_CPU_H
