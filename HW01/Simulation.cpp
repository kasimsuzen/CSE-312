//
// Created by Kasım Süzen on 07.03.2016.
//
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <cmath>
#include "Simulation.h"
#include "Instruction.h"
#include "Memory.h"

Simulation::Simulation(string &filename, int md) {
    memory.clear();
    instructions.clear();
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
    int i,j,dataStart,dataEnd,instructionStart,instructionEnd,index=0;
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

    // To erase 3 junk character
    fileContent.erase(0,3);

    #ifdef DEBUG
        cout << "Raw file output" << endl;
        cout << fileContent << endl;
    #endif
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

    #ifdef DEBUG
        cout << "after un comments" << endl;
        cout << fileContent;
    #endif

    dataStart = (int) fileContent.find(DATA_START);
    dataEnd = (int) fileContent.find(DATA_END);
    instructionStart = (int) fileContent.find(INSTR_START);
    instructionEnd = (int) fileContent.find(INSTR_END);
    if (dataStart == string::npos || dataEnd == string::npos || instructionStart == string::npos || instructionEnd  == string::npos){
        cerr << "This has not data or instruction sections \n";
    }

    string temp = DATA_START;
    Memory memTemp;
    int spaceToJump=0;

    for (int k = (int) (temp.length() + 3); k < dataEnd; ) {
        spaceToJump = 0;
        j=k;
        while(fileContent[j] != '\n')
            ++j;

        index = atoi(&fileContent.c_str()[k]);
        if(index != 0)
            spaceToJump = (int) log10((double)(index));

        memTemp = Memory(index,atoi(&fileContent.c_str()[k + spaceToJump +2]));
        #ifdef DEBUG
            cout << k << " " << fileContent[k] << " " << index << " " << memTemp.getIndex() << " " << memTemp.getValue() << endl;
        #endif

        memory.push_back(memTemp);
        k=j+1;

    }

    #ifdef DEBUG
        cout << "memtest" << endl;
        printMemory();
    #endif

    temp = INSTR_START;
    int firstOperand,secondOperand,secondSpace;
    string operand;
    char tt;
    for (int l = instructionStart + (int) (temp.length() + 2); l < fileContent.size(); ) {
        operand.clear();
        spaceToJump = 0;
        secondSpace = 0;
        index = atoi(&fileContent.c_str()[l]);
        if(index != 0)
            spaceToJump = (int) log10(index);

        j=l;
        while(fileContent[j] != '\n')
            ++j;
        i=l+spaceToJump+2;
        while(fileContent[i] != ' '){
            tt = fileContent[i];
            operand.push_back(tt);
            ++i;
        }
        temp = fileContent.substr(l,j-l);

        if (temp.find("SET") != string::npos){
            temp = "SET";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }
            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace+1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if (temp.find("CPY") != string::npos){
            temp = "CPY";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if (temp.find("CPYI") != string::npos ){
            temp = "CPYI";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if (temp.find("CPYI2") != string::npos){
            temp = "CPYI2";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if (temp.find("ADD") != string::npos){
            temp = "ADD";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if (temp.find("ADDI") != string::npos){
            temp = "ADDI";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if (temp.find("SUBI") != string::npos){
            temp = "SUBI";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if (temp.find("JIF") != string::npos){
            temp = "JIF";
            firstOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }
            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + temp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,temp,firstOperand,secondOperand));
        }

        else if(temp.find("HLT") != string::npos){
            temp = "HLT";
            instructions.push_back(Instruction(index,temp));
        }
        else if (temp.find("SYS PARAMS") != string::npos){
            temp = "SYS PARAMS";
            instructions.push_back(Instruction(index,temp));
        }
        else{
            cerr << "Unknown instruction "<< endl;
            exit(-1);
        }

        ++j;
        l=j;
        if(l == instructionEnd)
            break;
    }

#ifdef DEBUG
    cout << "Instruction list" << endl;
    printInstructionList();
#endif

}

void Simulation::cpuRun() {

}

Memory &Simulation::getMemory(int index) {
    return memory[index];
}

Instruction &Simulation::getInstruction(int index) {
    return instructions[index];
}

void Simulation::printInstructionList() {
    for (int i = 0; i < instructions.size(); ++i) {
        cout << instructions[i].getIndex() << " " << instructions[i].getInstruction() << " " << instructions[i].getFirstOperand() << " " << instructions[i].getSecondOperand() << endl;
    }
}

bool Simulation::funcSET(const Instruction &inst) {
    if(memory.size() <= inst.getSecondOperand())
        return false;
    else{
        memory[inst.getSecondOperand()].setValue(inst.getFirstOperand());
        return true;
    }
}

bool Simulation::funcCPY(const Instruction &inst) {
    if(inst.getFirstOperand() > memory.size() || inst.getSecondOperand() > memory.size())
        return false;
    else{
        memory[inst.getSecondOperand()].setValue(memory[inst.getFirstOperand()].getValue());
        return true;
    }
}

bool Simulation::funcCPYI(const Instruction &inst) {
    if(inst.getFirstOperand() > memory.size() || inst.getSecondOperand() > memory.size())
        return false;
    else{
        int tempAddress = memory[inst.getFirstOperand()].getValue();
        memory[tempAddress].setValue(memory[inst.getSecondOperand()].getValue());
        return true;
    }
}

bool Simulation::funcCPYI2(const Instruction &inst) {
    if(inst.getFirstOperand() > memory.size() || inst.getSecondOperand() > memory.size())

        return false;
    else{
        int tempAddress = memory[inst.getSecondOperand()].getValue();
        memory[tempAddress].setValue(memory[inst.getFirstOperand()].getValue());
        return true;
    }
}

bool Simulation::funcADD(const Instruction &inst) {
    if(memory.size() < inst.getSecondOperand())
        return false;
    else{
        memory[inst.getSecondOperand()].setValue(memory[inst.getSecondOperand()].getValue() + inst.getFirstOperand());
        return true;
    }
}

bool Simulation::funcADDI(const Instruction &inst) {
    if(inst.getFirstOperand() > memory.size() || inst.getSecondOperand() > memory.size())
        return false;
    else{
        memory[inst.getSecondOperand()].setValue(memory[inst.getFirstOperand()].getValue() + memory[inst.getSecondOperand()].getValue());
        return true;
    }
}

bool Simulation::funcSUBI(const Instruction &inst) {
    if(inst.getFirstOperand() > memory.size() || inst.getSecondOperand() > memory.size())
        return false;
    else{
        memory[inst.getSecondOperand()].setValue(memory[inst.getFirstOperand()].getValue() - memory[inst.getSecondOperand()].getValue());
        return true;
    }
}

bool Simulation::funcJIF(const Instruction &inst) {
    if(inst.getFirstOperand() > memory.size())
        return false;
    else{
        if(memory[inst.getFirstOperand()].getValue() <= 0){
            memory[0].setValue(inst.getFirstOperand());
        }
        return true;
    }
}

bool Simulation::funcHLT(const Instruction &inst) {
    return true;
}

bool Simulation::funcSYS(const Instruction &inst) {
    cerr << "This instruction is not implemented as it should not be(Reserved for next homework)" << endl;
    return false;
}
