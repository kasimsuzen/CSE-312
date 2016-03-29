
//
// Created by Kasım Süzen 111044034 on 07.03.2016
//
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <cmath>
#include "Process.h"
#include "Instruction.h"
#include "Memory.h"
#include <cstdlib>

Process::Process(string &filename, int md) {
    instructions.clear();
    parseFile(filename);
    mode=md;
}

Process::~Process() {

}

void Process::parseFile(string &fileName) {
    string fileContent;
    int i,j,dataStart,dataEnd,instructionStart,instructionEnd,index=0;
    ifstream fileStream;
    fileStream.open(fileName.c_str());
    stringstream strStream;

    // Allocates memoryData space needed for this file before hand
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
    //fileContent.erase(0,3);

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
    vector<Memory> memTemp;
    int spaceToJump=0;

    for (int k = (int) (temp.length() + 3); k < dataEnd; ) {
        spaceToJump = 0;
        j=k;
        while(fileContent[j] != '\n')
            ++j;

        index = atoi(&fileContent.c_str()[k]);
        if(index != 0)
            spaceToJump = (int) log10((double)(index));

        memTemp.push_back(Memory(index,atoi(&fileContent.c_str()[k + spaceToJump +2])));
        #ifdef DEBUG
            cout << k << " " << fileContent[k] << " " << index << " " << memTemp.getIndex() << " " << memTemp.getValue() << endl;
        #endif

        k=j+1;

    }

    basePointer = memTemp[2].getValue();
    limitPointer = memTemp[3].getValue();

    vector<Memory>::iterator it = memTemp.begin();

    for( ;it != memTemp.end(); ++it)
        setMemory(it->getIndex(), it->getValue(), basePointer, limitPointer);

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

        else if (temp.find("ADD") != string::npos && temp.find("ADDI") == string::npos){
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
            cerr << "Unknown instruction " << temp << endl;
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

void Process::cpuRun() {
    bool flag = true,isLastJump = false;
    int pCounter;
    while(flag){

        pCounter = getMemory(0,basePointer,limitPointer);
        if(!isLastJump) {
            setMemory(0,getMemory(0,basePointer,limitPointer)+ 1,basePointer,limitPointer);
        }
        if(isLastJump) {
            isLastJump = false;
        }

        if(mode == 2){
            cout << endl << "Memory last condition" << endl;
            printMemory();
            cout << endl << "Print a key to continue" << endl;
            cout << pCounter << endl;
            cout << instructions[pCounter].getInstruction() << " " << instructions[pCounter].getFirstOperand() << " " << instructions[pCounter].getSecondOperand() << " " << instructions[pCounter].getIndex() << endl;

            system("read");

        }

        if(mode == 1) {
            cout << endl << "Memory last condition" << endl;
            printMemory();
            cout << pCounter << endl;
            cout << instructions[pCounter].getInstruction() << " " << instructions[pCounter].getFirstOperand() << " " << instructions[pCounter].getSecondOperand() << " " << instructions[pCounter].getIndex() << endl;
        }

        if (instructions[pCounter].getInstruction().find("SET") != string::npos) {
            funcSET(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("CPYI2") != string::npos) {
            funcCPYI2(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("CPYI") != string::npos) {
            funcCPYI(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("CPY") != string::npos) {
            funcCPY(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("ADDI") != string::npos) {
            funcADDI(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("ADD") != string::npos) {
            funcADD(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("SUBI") != string::npos) {
            funcSUBI(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("JIF") != string::npos){
            isLastJump = funcJIF(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("SYS PARAMS") != string::npos) {
            funcSYS(instructions[pCounter]);
        }
        else if(instructions[pCounter].getInstruction().find("HLT") != string::npos) {

            break;
        }

    }
    cout << "Program has finished memoryData looks like this "<< endl;
    printMemory();
}

Instruction &Process::getInstruction(int index) {
    return instructions[index];
}

void Process::printInstructionList() {
    for (int i = 0; i < instructions.size(); ++i) {
        cout << instructions[i].getIndex() << " " << instructions[i].getInstruction() << " " << instructions[i].getFirstOperand() << " " << instructions[i].getSecondOperand() << endl;
    }
}

bool Process::funcSET(const Instruction &inst) {
    setMemory(getMemory(inst.getSecondOperand(),basePointer,limitPointer),inst.getFirstOperand(),basePointer,limitPointer);
    return true;

}

bool Process::funcCPY(const Instruction &inst) {
    setMemory(inst.getSecondOperand(),getMemory(inst.getFirstOperand(),basePointer,limitPointer),basePointer,limitPointer);
    return true;
}

bool Process::funcCPYI(const Instruction &inst) {
    int tempAddress = getMemory(inst.getFirstOperand(),basePointer,limitPointer);
    setMemory(getMemory(inst.getSecondOperand(),basePointer,limitPointer),getMemory(tempAddress,basePointer,limitPointer),basePointer,limitPointer);
    return true;
}

bool Process::funcCPYI2(const Instruction &inst) {
    int tempAddress = getMemory(inst.getSecondOperand(),basePointer,limitPointer);
    setMemory(getMemory(tempAddress,basePointer,limitPointer),getMemory(inst.getFirstOperand(),basePointer,limitPointer),basePointer,limitPointer);
    return true;

}

bool Process::funcADD(const Instruction &inst) {
    setMemory(getMemory(inst.getSecondOperand(),basePointer,limitPointer),getMemory(inst.getSecondOperand(),basePointer,limitPointer) + inst.getFirstOperand(),basePointer,limitPointer);
    return true;
}

bool Process::funcADDI(const Instruction &inst) {
    setMemory(getMemory(inst.getSecondOperand(),basePointer,limitPointer),getMemory(inst.getFirstOperand(),basePointer,limitPointer)
                                                                          + getMemory(inst.getSecondOperand(),basePointer,limitPointer),basePointer,limitPointer);
    return true;
}

bool Process::funcSUBI(const Instruction &inst) {
    setMemory(getMemory(inst.getSecondOperand(),basePointer,limitPointer),getMemory(inst.getFirstOperand(),basePointer,limitPointer)
                                                                          - getMemory(inst.getSecondOperand(),basePointer,limitPointer),basePointer,limitPointer);
    return true;
}

bool Process::funcJIF(const Instruction &inst) {

    if(getMemory(inst.getFirstOperand(),basePointer,limitPointer) <= 0){
        setMemory(0,inst.getSecondOperand(),basePointer,limitPointer);
        return true;
    }
    else
        return false;
}

bool Process::funcHLT(const Instruction &inst) {
    return true;
}

bool Process::funcSYS(const Instruction &inst) {
    cerr << "This instruction is not implemented as it should not be(Reserved for next homework)" << endl;
    return false;
}
