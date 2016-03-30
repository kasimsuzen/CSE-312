//
// Created by Kasım Süzen 111044034 on 07.03.2016
//

#include <iostream>
#include <cstdlib>
#include "Memory.h"
#include "CPU.h"


Memory::Memory(int indexData, int valueData){
    index = indexData;
    value = valueData;
}

Memory::~Memory() {

}

void Memory::setIndex(int index) {
    Memory::index = index;
}

void Memory::setValue(int value) {
    Memory::value = value;
}

int Memory::getValue() const {
    return value;
}

int Memory::getIndex() const {
    return index;
}

Memory::Memory() {

}

bool setMemory(int index, int value, int base, int limit) {
    if(limit < index || index < 0 || limit >= CPU::memoryData.size()) {
        cerr << "Segmentation fault" << limit << " " << index << " " << CPU::memoryData.size() << endl;
        exit(-1);
    }
    CPU::memoryData[base+index].setValue(value);
    CPU::memoryData[base+index].setIndex(base+index);
    return true;
}

int getMemory(int index, int base, int limit) {
    if(limit < index || index < 0 || limit >= CPU::memoryData.size()) {
        cerr << "Segmentation fault" << endl;
        exit(-1);
    }
    return CPU::memoryData[base+index].getValue();
}

void printMemory() {

    for (int i = 0; i < CPU::memoryData.size(); ++i)
    {
        cout << CPU::memoryData[i].getIndex() <<"  "<< CPU::memoryData[i].getValue() <<" , ";
        if(i%10==0 && i != 0){
            cout <<"\n";
        }
    }
}

int sizeOfMemory() {
    return (int) CPU::memoryData.size();
}

bool eraseMemoryCells(int start, int stop) {
    for (int i = start; i < stop; ++i) {
        CPU::memoryData[i] = Memory(i,0);
    }
    return true;
}