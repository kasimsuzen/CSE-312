//
// Created by Kasım Süzen on 07.03.2016.
//

#include <iostream>
#include <vector>
#include <string>
#include "Instruction.h"
#include "Memory.h"

using namespace std;

#ifndef HW01_SIMULATION_H
#define HW01_SIMULATION_H
#define DATA_START "Begin Data Section"
#define DATA_END "End Data Section"
#define INSTR_START "Begin Instruction Section"
#define INSTR_END "End Instruction Section"

class Simulation {
public:
    Simulation(string &filename,int md);
    ~Simulation();
    void parseFile(string &filename);
    void printMemory();
    void printInstructionList();
    void cpuRun();
    Memory& getMemory(int index);
    Instruction& getInstruction(int index);
    bool funcSET(const Instruction& inst);
    bool funcCPY(const Instruction& inst);
    bool funcCPYI(const Instruction& inst);
    bool funcCPYI2(const Instruction& inst);
    bool funcADD(const Instruction& inst);
    bool funcADDI(const Instruction& inst);
    bool funcSUBI(const Instruction& inst);
    bool funcJIF(const Instruction& inst);
    bool funcHLT(const Instruction& inst);
    bool funcSYS(const Instruction& inst);

private:
    vector<Memory> memory;
    vector<Instruction> instructions;
    int mode;
};


#endif //HW01_SIMULATION_H
