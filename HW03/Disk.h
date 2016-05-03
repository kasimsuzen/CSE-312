//
// Created by kasim on 30.04.2016.
//

#include <vector>
#include <string>
using namespace std;

#pragma once

#include "MemoryCell.h"

class Disk {
public:
    Disk();
    ~Disk();

    void readFile(string fileName);
    void fillDisk(int *array, int size);

    int getIndex(int index);
    void getRange(int startPoint,int endPoint,int * arrayToFill);

    void setRange(int startPoint,int endPoint,int * arrayToFill);
    void setIndex(int index,int value);

    int size();

private:
    vector<MemoryCell> diskCells;
};

