//
// Created by Kasım Süzen 111044034 on 28.03.2016.
//

#include "CPU.h"
#include "Process.h"
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

void CPU::tick() {
    updateProcessList();
    cout << processTable.size() << endl;
    for (int i = 0; i < processTable.size(); ++i) {
        if(processTable[i].state == 'r'){
            loadedProcess[i].cpuRun();
            break;
        }
    }
}

bool CPU::isHalted() {
    return processTable.size() == 0;
}

bool CPU::addProcess(string fileName, int pid, int md, int pcValue) {
    ProcessTable temp;
    temp.processName = fileName;
    temp.state = 'r';
    temp.elapsedTicks = 0;
    temp.pid = processTable.size();
    temp.ppid = 0;
    temp.startTimeAsCPUTick = elapsedTime;
    processTable.push_back(temp);
    return true;
}

bool CPU::updateProcessList() {
    if(processTable.size() == loadedProcess.size())
        return true;
    else{
        for(int i= loadedProcess.size();i < processTable.size();++i)
            loadedProcess.push_back(Process(processTable[i].processName,mode));
    }

    for (int i = 0; i < loadedProcess.size(); ++i) {
        if(loadedProcess[i].isHalted()){
            loadedProcess.erase(loadedProcess.begin() + i);
            processTable.erase(processTable.begin() + i);
        }
    }
}

