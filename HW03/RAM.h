//
// Created by kasim on 30.04.2016.
//

#include <vector>
#include "MemoryCell.h"

using namespace std;

#pragma once

#define RAM_SIZE 512

class RAM {
public:
    RAM();
    void fillRAM(int *array, int size);

    int getIndex(int index);
    void getRange(int startPoint,int endPoint,int * arrayToFill);

    void setRange(int startPoint,int endPoint,int * arrayToFill);
    void setIndex(int index,int value);

private:
    vector<MemoryCell> ramCells;
};

