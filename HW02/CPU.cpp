//
// Created by Kasım Süzen 111044034 on 28.03.2016.
//

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "CPU.h"
#include "Process.h"
using namespace std;
vector<Memory> CPU::memoryData;
vector<ProcessTable> CPU::processTable;
int CPU::indexOfMem;

CPU::CPU(int md) {

    memoryData.clear();
    for (int i = 0; i < 250; ++i) {
        memoryData.push_back(Memory(i,0));
    }
    mode = md;
}

CPU::~CPU() {

}

char CPU::tick(Process &proc) {
    char control;
    control = proc.cpuRun();
    return  control;
}

bool CPU::isHalted() {
    return processTable.size() == 0;
}

int CPU::addProcess(string fileName, int md, int pcValue) {
    ProcessTable temp;
    temp.processName = fileName;
    temp.state = 'r';
    temp.elapsedTicks = 0;
    temp.pid = processTable.size();
    temp.ppid = 0;
    temp.startTimeAsCPUTick = elapsedTime;
    processTable.push_back(temp);
    return temp.pid;
}

bool CPU::updateProcessList() {
    for (int i = 0; i < loadedProcess.size(); ++i) {
        if(loadedProcess[i].isHalted() || processTable[i].state == 'f'){
            loadedProcess.erase(loadedProcess.begin() + i);
            processTable.erase(processTable.begin() + i);
        }
    }

    if(processTable.size() == loadedProcess.size())
        return true;
    else{
        for(int i= loadedProcess.size();i < processTable.size();++i)
            loadedProcess.push_back(Process(processTable[i].processName,mode));
    }
}

void CPU::run() {
    char control=0;
    updateProcessList();
    for (int i = 0; i < processTable.size(); ++i) {
        if(processTable[i].state == 'r'){
            control = tick(loadedProcess[i]);
            if(control == 'b'){
                srand(time(0));
                processTable[i].startTimeAsCPUTick = elapsedTime + rand()%6 + 5;
                elapsedTime = elapsedTime + 20;

                processTable[i].state = 'b';
            }
        }
        if(processTable[i].state == 'b'){
            if (processTable[i].startTimeAsCPUTick < elapsedTime)
                processTable[i].state = 'r';
        }
        if(control == 'f')
            processTable[i].state = 'f';
        updateProcessList();
        if(i == processTable.size()-1)
            i = -1;
    }
}

