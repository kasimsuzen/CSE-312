//
// Created by kasim on 01.05.2016.
//
#include <vector>
#include "PageTableEntry.h"
#include "Disk.h"
#include "RAM.h"

using namespace std;

#pragma once

#define PAGESIZE

class PageTable {
public:
    PageTable();
    PageTable(vector<PageTableEntry> & obj);

    void init();
    int getMemory(int index);
    void setMemory(int index, int value);

    void pageReplace(int newIndex);
    int  size();

private:
    vector<PageTableEntry> data;
    int currentNode;
};



