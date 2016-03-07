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


class Simulation {
public:
    Simulation(string &filename,int md);
    ~Simulation();
    void parseFile(string &filename);
    void printMemory();
    void cpuRun();

private:
    vector<Memory> memory;
    vector<Instruction> instructions;
    int mode;
};


#endif //HW01_SIMULATION_H
