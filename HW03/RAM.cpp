//
// Created by kasim on 30.04.2016.
//

#include "RAM.h"

void RAM::fillRAM(int *array, int size) {
    for(int i=0; i < size; ++i){
        ramCells.push_back(MemoryCell(i,array[i]));
    }
}

int RAM::getIndex(int index) {
    return ramCells[index].getValue();
}

void RAM::getRange(int startPoint, int endPoint, int *arrayToFill) {
    for(int i=0; i + startPoint < endPoint; ++i){
        arrayToFill[i] = ramCells[i + startPoint].getValue();
    }
}

void RAM::setRange(int startPoint, int endPoint, int *arrayToFill) {
    for(int i = 0; i + startPoint < endPoint; ++i){
        ramCells[i].setValue(arrayToFill[i]);
    }
}

void RAM::setIndex(int index, int value) {
    ramCells[index].setValue(value);
}

RAM::RAM() {
    ramCells.resize(512);
}

