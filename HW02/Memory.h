//
// Created by Kasım Süzen 111044034 on 07.03.2016
//

#include <vector>

using namespace std;

#pragma once

bool setMemory(int index, int value, int base, int limit);
int getMemory(int index, int base, int limit);
void printMemory();

class Memory {
public:
    Memory();

    Memory(int indexData, int valueData);
    ~Memory();

    int getIndex() const;
    void setIndex(int index);
    int getValue() const;
    void setValue(int value);

private:
    int index;
    int value;
};

namespace {
    vector<Memory> memoryData;
}