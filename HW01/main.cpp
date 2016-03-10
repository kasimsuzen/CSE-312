//
// Created by Kasım Süzen 111044034 on 07.03.2016
//
#include <iostream>
#include <string>
#include <cstdlib>
#include "Simulation.h"
#include "Instruction.h"
#include "Memory.h"

using namespace std;
void usage();

int main(int argc,char ** argv) {
    if(argc < 3)
        usage();

    string filename(argv[1]);

    Simulation sim(filename, atoi(argv[3]));
    sim.cpuRun();

    return 0;
}

void usage(){
    cout << "This program should run like this \n";
    cout << "Simulate fileName -D mode" << endl;
    cout << "Mode 0 runs all instructions and show last state of memory" << endl;
    cout << "Mode 1 run one instruction and show memory map all instructions finished"<< endl;
    cout << "Mode 2 runs one instruction shows memory map and wait to press a key " << endl;
}