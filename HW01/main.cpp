#include <iostream>
#include <string>

#include "Simulation.h"
#include "Instruction.h"
#include "Memory.h"

using namespace std;

int main() {

    string filename("pr.txt");

    Simulation sim(filename, 2);
    sim.cpuRun();

    return 0;
}