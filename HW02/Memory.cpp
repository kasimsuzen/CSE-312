//
// Created by Kasım Süzen 111044034 on 07.03.2016
//

#include <iostream>
#include <cstdlib>
#include "Memory.h"

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
    if(limit > base + index || index < 0 || limit >= memoryData.size()) {
        cerr << "Segmentation fault" << endl;
        exit(-1);
    }
    memoryData[base+index].setValue(value);
}

int getMemory(int index, int base, int limit) {
    if(limit > base + index || index < 0 || limit >= memoryData.size()) {
        cerr << "Segmentation fault" << endl;
        exit(-1);
    }
    return  memoryData[base+index].getValue();
}

void printMemory() {

    for (int i = 0; i < memoryData.size(); ++i)
    {
        cout << memoryData[i].getIndex() <<"  "<< memoryData[i].getValue() <<" , ";
        if(i%10==0 && i != 0){
            cout <<"\n";
        }
    }
}
