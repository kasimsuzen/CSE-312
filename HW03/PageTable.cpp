//
// Created by kasim on 01.05.2016.
//

#include <iostream>
#include "PageTable.h"
#include "Disk.h"
#include "RAM.h"

extern RAM myRAM;
extern Disk myDisk;

PageTable::PageTable() {
    currentNode =0;
}

PageTable::PageTable(vector<PageTableEntry> &obj) {
    for(int i=0; i < obj.size();++i){
        data.push_back(PageTableEntry(obj[i].getPhysicalAddressNumber(),obj[i].getPageFrameNumber()));
    }
    currentNode =0;
}


int PageTable::getMemory(int index) {
    for(int i=0; i < data.size(); ++i){
        if(data[i].getPageFrameNumber() == index){
            if(data[i].getIsPresent()){
                return myRAM.getIndex(data[i].getPhysicalAddressNumber());
            }
        }
    }
    pageReplace(index);

    for(int i=0; i < data.size(); ++i){
        if(data[i].getPageFrameNumber() == index){
            if(data[i].getIsPresent()){
                return myRAM.getIndex(data[i].getPhysicalAddressNumber());
            }
        }
    }
}

void PageTable::setMemory(int index, int value) {
    bool flag = false;
    for(int i=0; i < data.size(); ++i){
        if(data[i].getPageFrameNumber() == index){
            if(data[i].getIsPresent()){
                myRAM.setIndex(data[i].getPhysicalAddressNumber(),value);
                data[i].setIsModified(true);
                data[i].setIsPresent(true);
                flag = true;
                break;
            }
        }
    }

    if(!flag) {
        pageReplace(index);

        for (int i = 0; i < data.size(); ++i) {
            if (data[i].getPageFrameNumber() == index) {
                if (data[i].getIsPresent()) {
                    myRAM.setIndex(data[i].getPhysicalAddressNumber(), value);
                    data[i].setIsModified(true);
                    data[i].setIsPresent(true);
                    break;
                }
            }
        }
    }
}

void PageTable::pageReplace(int newIndex) {
    int lastPoint = currentNode;
    bool isReplaced = false;
    for(int i=currentNode; i < data.size(); ++i){
        if(!data[i].getIsReferenced()){
            if(!data[i].getIsModified()){
                myRAM.setIndex(data[i].getPhysicalAddressNumber(),myRAM.getIndex(data[i].getPageFrameNumber()));
                isReplaced = true;
                currentNode = i;
                break;
            }
            else{
                myDisk.setIndex(data[i].getPageFrameNumber(),myRAM.getIndex(data[i].getPhysicalAddressNumber()));
            }
        }
    }

    if (!isReplaced){
        for (int i = 0; i < lastPoint; ++i) {
            if(!data[i].getIsReferenced()){
                if(!data[i].getIsModified()){
                    myRAM.setIndex(data[i].getPhysicalAddressNumber(),myRAM.getIndex(data[i].getPageFrameNumber()));
                    isReplaced = true;
                    currentNode = i;
                    break;
                }
                else{
                    myDisk.setIndex(data[i].getPageFrameNumber(),myRAM.getIndex(data[i].getPhysicalAddressNumber()));
                }
            }
        }
    }

    if(!isReplaced){
        for(int i=currentNode; i < data.size(); ++i){
            if(!data[i].getIsReferenced()){
                if(!data[i].getIsModified()){
                    myRAM.setIndex(data[i].getPhysicalAddressNumber(),myRAM.getIndex(data[i].getPageFrameNumber()));
                    isReplaced = true;
                    break;
                }
                else{
                    myDisk.setIndex(data[i].getPageFrameNumber(),myRAM.getIndex(data[i].getPhysicalAddressNumber()));
                }
            }
        }
    }

    if (!isReplaced){
        for (int i = 0; i < lastPoint; ++i) {
            if(!data[i].getIsReferenced()){
                if(!data[i].getIsModified()){
                    myRAM.setIndex(data[i].getPhysicalAddressNumber(),myRAM.getIndex(data[i].getPageFrameNumber()));
                    isReplaced = true;
                    currentNode = i;
                    break;
                }
                else{
                    myDisk.setIndex(data[i].getPageFrameNumber(),myRAM.getIndex(data[i].getPhysicalAddressNumber()));
                }
            }
        }
    }
}

int PageTable::size() {
    return data.size();
}

void PageTable::init() {
    for(int i=0; i < size();++i){
        data.push_back(PageTableEntry(i,myDisk.getIndex(i)));
        cout << "page " << i << " val " << myDisk.getIndex(i) << endl;
    }
}









