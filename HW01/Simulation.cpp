//
// Created by Kasım Süzen on 07.03.2016.
//

#include "Simulation.h"
#include "Instruction.h"
#include "Memory.h"

Simulation::Simulation(string &filename, int md) {
    parseFile(filename);
    mode=md;
}

Simulation::~Simulation() {

}

void Simulation::printMemory() {

    for (int i = 0; i < memory.size(); ++i)
    {
        cout << Memory[i].index<<"  "<< Memory[i].value<<" , ";
        if(i%10==0){
            cout <<"\n";
        }
    }
}

void Simulation::parseFile(string &filename) {

}

void Simulation::cpuRun() {

}
