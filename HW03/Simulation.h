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
#include "MemoryCell.h"

using namespace std;

#pragma once

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

    int getMemory(int index);
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
    vector<Instruction> instructions;
    int mode;
};
