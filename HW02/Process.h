//
// Created by Kasım Süzen on 07.03.2016.
//
//
// Created by Kasım Süzen 111044034 on 07.03.2016
//
#include <iostream>
#include <vector>
#include <string>
#include "Instruction.h"
#include "Memory.h"

using namespace std;

#ifndef HW02_PROCESS_H
#define HW02_PROCESS_H

#define DATA_START "Begin Data Section"
#define DATA_END "End Data Section"
#define INSTR_START "Begin Instruction Section"
#define INSTR_END "End Instruction Section"

class Process {
public:
    Process();
    Process(string &filename,int md);
    ~Process();
    void parseFile(string &filename);
    void printInstructionList();
    void cpuRun();
    Instruction& getInstruction(int index);
    bool isHalted();

    bool funcSET(const Instruction& inst);
    bool funcCPY(const Instruction& inst);
    bool funcCPYI(const Instruction& inst);
    bool funcCPYI2(const Instruction& inst);
    bool funcADD(const Instruction& inst);
    bool funcADDI(const Instruction& inst);
    bool funcSUBI(const Instruction& inst);
    bool funcJIF(const Instruction& inst);
    bool funcHLT(const Instruction& inst);
    bool funcFORK(const Instruction& inst);
    bool funcEXEC(const Instruction& inst);
    bool funcPRN(const Instruction &inst);

private:
    vector<Instruction> instructions;
    int mode,basePointer,limitPointer,SysCallResult;
    bool isFinished;
};


#endif //HW02_PROCESS_H
