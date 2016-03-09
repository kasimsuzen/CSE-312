//
// Created by Kasım Süzen on 07.03.2016.
//
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
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
        cout << memory[i].getIndex() <<"  "<< memory[i].getValue() <<" , ";
        if(i%10==0){
            cout <<"\n";
        }
    }
}

void Simulation::parseFile(string &fileName) {
    string fileContent;
    int i,j;
    ifstream fileStream;
    fileStream.open(fileName.c_str());
    stringstream strStream;

    // Allocates memory space needed for this file before hand
    fileStream.seekg(0, ios::end);
    fileContent.reserve((unsigned long) fileStream.tellg());
    fileStream.seekg(0, ios::beg);

    // Transfers contents of file to the string
    strStream << fileStream.rdbuf();
    fileContent.clear();
    fileContent = strStream.str();

    // Empties and clear string stream
    strStream.str("");
    strStream.clear();

    cout << fileContent;

    // To uncomment assembly file
    for (i = 0; i < fileContent.size(); ++i) {
        if(fileContent[i] == '\n' && i < fileContent.size()-1 && fileContent[i+1] == '\n') {
            fileContent.erase(fileContent.begin() + i);
            i=0;
        }

        if(fileContent[i] == '#'){
            j=i;
            while (fileContent[j] != '\n'){
                ++j;
            }
            fileContent.erase(fileContent.begin()+i,fileContent.begin()+j);
            i=0;

        }
    }

    cout << "after un comments" << endl;
    cout << fileContent;

}

void Simulation::cpuRun() {

}

Memory &Simulation::getMemory(int index) {
    return memory[index];
}

Instruction &Simulation::getInstruction(int index) {
    return instructions[index];
}
