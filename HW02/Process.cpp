
//
// Created by Kasım Süzen 111044034 on 07.03.2016
//
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <cmath>
#include <string>
#include "Process.h"
#include "Instruction.h"
#include "Memory.h"
#include "CPU.h"
#include <cstdlib>

Process::Process() {
    isFinished = false;
}

Process::Process(string &filename, int md) {
    instructions.clear();
    parseFile(filename);
    mode=md;
    isFinished = false;
    sourceFileName = filename;
}

Process::~Process() {

}

void Process::parseFile(string &fileName) {
    string instructionTemp(INSTR_START);
    string fileContent;
    int i,j,dataStart,dataEnd,instructionStart,instructionEnd,index=0;
    sourceFileName = fileName;
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
    fileStream.close();

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
    int spaceToJump=0,charStart=0;

    for (int k = (int) (temp.length() + 3); k < dataEnd; ) {
        spaceToJump = 0;
        charStart =0;
        j=k;
        index = atoi(&fileContent.c_str()[k]);
        while(fileContent[j] != '\n')
            ++j;

        if(fileContent.substr(k,j-k).find("\"") != string::npos){
            charStart = fileContent.substr(k,j-k).find("\"")+1;
            memTemp.push_back(Memory(index,fileContent.c_str()[charStart]));

        }
        else {
            if (index != 0)
                spaceToJump = (int) log10((double) (index));

            memTemp.push_back(Memory(index, atoi(&fileContent.c_str()[k + spaceToJump + 2])));
        }
        #ifdef DEBUG
            cout << k << " " << fileContent[k] << " " << index << " " << memTemp.getIndex() << " " << memTemp.getValue() << endl;
        #endif

        k=j+1;

    }

    basePointer = CPU::indexOfMem;
    limitPointer = memTemp.size() - 1;
    CPU::indexOfMem += limitPointer;

    for(i =0 ;i < memTemp.size(); ++i) {
        setMemory(memTemp[i].getIndex(), memTemp[i].getValue(), basePointer, limitPointer);
    }

    memTemp.clear();

    #ifdef DEBUG
        cout << "memtest" << endl;
        printMemory();
    #endif

    cout << instructionTemp << endl;
    int firstOperand,secondOperand,secondSpace;
    string operand;
    char tt;
    for (int l = instructionStart + (int) (instructionTemp.length() + 2); l < fileContent.size(); ) {
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
        instructionTemp = fileContent.substr(l,j-l);
        cout << " " << instructionTemp << endl;

        if (instructionTemp.find("SET") != string::npos){
            instructionTemp = "SET";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }
            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace+1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }
        else if (instructionTemp.find("CPYI2") != string::npos){
            instructionTemp = "CPYI2";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }

        else if (instructionTemp.find("CPYI") != string::npos ){
            instructionTemp = "CPYI";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }

        else if (instructionTemp.find("CPY") != string::npos){
            instructionTemp = "CPY";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }

        else if (instructionTemp.find("ADD") != string::npos && instructionTemp.find("ADDI") == string::npos){
            instructionTemp = "ADD";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }

        else if (instructionTemp.find("ADDI") != string::npos){
            instructionTemp = "ADDI";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }

        else if (instructionTemp.find("SUBI") != string::npos){
            instructionTemp = "SUBI";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }

            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }

        else if (instructionTemp.find("JIF") != string::npos){
            instructionTemp = "JIF";
            firstOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3]);
            if (firstOperand != 0) {
                secondSpace = (int) log10(abs(firstOperand));
            }
            if(firstOperand < 0)
                ++secondSpace;
            secondOperand = atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3 + secondSpace + 1]);
            instructions.push_back(Instruction(index,instructionTemp,firstOperand,secondOperand));
        }

        else if(instructionTemp.find("HLT") != string::npos){
            instructionTemp = "HLT";
            instructions.push_back(Instruction(index,instructionTemp));
        }
        else if (instructionTemp.find("CALL PRN") != string::npos){
            instructionTemp = "CALL PRN";
            instructions.push_back(Instruction(index,instructionTemp,atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3])));
        }
        else if(instructionTemp.find("CALL FORK") != string::npos){
            instructionTemp = "CALL FORK";
            instructions.push_back(Instruction(index,instructionTemp));
        }
        else if(instructionTemp.find("CALL EXEC") != string::npos){
            instructionTemp = "CALL EXEC";
            instructions.push_back(Instruction(index,instructionTemp,atoi(&fileContent.c_str()[l + instructionTemp.length() + spaceToJump + 3])));
        }
        else{
            cerr << "Unknown instruction " << instructionTemp << endl;
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

char Process::cpuRun() {
    bool flag = true,isLastJump = false,isBlocked = false;
    int pCounter;

    while(flag){
        ++elapsedTime;
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

            getchar();
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
        else if(instructions[pCounter].getInstruction().find("CALL PRN") != string::npos) {
            funcPRN(instructions[pCounter]);
            isBlocked = true;
            break;
        }
        else if(instructions[pCounter].getInstruction().find("CALL EXEC") != string::npos) {
            funcEXEC(instructions[pCounter]);
            isBlocked = true;
            break;
        }
        else if(instructions[pCounter].getInstruction().find("CALL FORK") != string::npos) {
            funcFORK(instructions[pCounter]);
            isBlocked = true;
            break;
        }
        else if(instructions[pCounter].getInstruction().find("HLT") != string::npos) {
            isFinished = true;
            break;
        }
    }
    if(!isBlocked) {
        cout << "Program has finished memoryData looks like this "<< endl;
        printMemory();
    }
    if(isBlocked)
        return 'b';
    if (isFinished)
        return 'f';
}

Instruction &Process::getInstruction(int index) {
    return instructions[index];
}

void Process::printInstructionList() {
    cout << instructions.size() << endl;
    for (int i = 0; i < instructions.size(); ++i) {
        cout << i << " ";
        cout << instructions[i].getIndex() << " " << instructions[i].getInstruction() << " " << instructions[i].getFirstOperand() << " " << instructions[i].getSecondOperand() << endl;
    }
    cout << "end";
}

bool Process::funcSET(const Instruction &inst) {
    setMemory(inst.getSecondOperand() + basePointer,inst.getFirstOperand(),basePointer,limitPointer);
    //cout << "second op" << getMemory(inst.getSecondOperand(),basePointer,limitPointer) << " " << endl;
    return true;

}

bool Process::funcCPY(const Instruction &inst) {
    setMemory(inst.getSecondOperand() + basePointer,getMemory(inst.getFirstOperand(),basePointer,limitPointer),basePointer,limitPointer);
    return true;
}

bool Process::funcCPYI(const Instruction &inst) {
    int tempAddress = getMemory(inst.getFirstOperand(),basePointer,limitPointer);
    setMemory(inst.getSecondOperand()+basePointer,getMemory(tempAddress,basePointer,limitPointer),basePointer,limitPointer);
    return true;
}

bool Process::funcCPYI2(const Instruction &inst) {
    int tempAddress = getMemory(inst.getSecondOperand(),basePointer,limitPointer);
    setMemory(tempAddress+basePointer,getMemory(inst.getFirstOperand(),basePointer,limitPointer),basePointer,limitPointer);
    return true;

}

bool Process::funcADD(const Instruction &inst) {
    setMemory(inst.getSecondOperand() + basePointer,getMemory(inst.getSecondOperand(),basePointer,limitPointer) + inst.getFirstOperand(),basePointer,limitPointer);
    return true;
}

bool Process::funcADDI(const Instruction &inst) {
    setMemory(inst.getSecondOperand() + basePointer,getMemory(inst.getFirstOperand(),basePointer,limitPointer)
                                                                          + getMemory(inst.getSecondOperand(),basePointer,limitPointer),basePointer,limitPointer);
    return true;
}

bool Process::funcSUBI(const Instruction &inst) {
    setMemory(inst.getSecondOperand() + basePointer,getMemory(inst.getFirstOperand(),basePointer,limitPointer)
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

bool Process::isHalted() {
    return isFinished;
}

bool Process::
funcFORK(const Instruction &inst) {
    int control = CPU::addProcess(sourceFileName, mode, getMemory(0,basePointer,limitPointer)+2);
    if(control != 0)
        setMemory(4,control,basePointer,limitPointer);

    return true;
}

bool Process::funcEXEC(const Instruction &inst) {
    string temp = "";
    for(int i= inst.getFirstOperand(); i < limitPointer; ++i){
        if(getMemory(i,basePointer,limitPointer) != '0')
            temp += getMemory(i,basePointer,limitPointer);
        else
            break;
    }
    cout << temp << " temp" <<endl;
    return true;
}

bool Process::funcPRN(const Instruction &inst) {
    cout << "Result of prn "<< getMemory(inst.getFirstOperand(),basePointer,limitPointer) << endl;
    return false;
}

