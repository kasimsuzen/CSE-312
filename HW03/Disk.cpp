//
// Created by kasim on 30.04.2016.
//

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "Disk.h"
#include "Simulation.h"

Disk::Disk() {

}

Disk::~Disk() {

}

void Disk::readFile(string fileName) {
    string fileContent;
    int i,j,dataStart,dataEnd,instructionStart,instructionEnd,index=0;
    ifstream fileStream;
    fileStream.open(fileName.c_str());
    stringstream strStream;

    // Allocates memory space needed for this file before hand
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
    MemoryCell memTemp;
    int spaceToJump=0;

    for (int k = (int) (temp.length() + 3); k < dataEnd; ) {
        spaceToJump = 0;
        j=k;
        while(fileContent[j] != '\n')
            ++j;

        index = atoi(&fileContent.c_str()[k]);
        if(index != 0)
            spaceToJump = (int) log10((double)(index));

        memTemp = MemoryCell(index,atoi(&fileContent.c_str()[k + spaceToJump +2]));
#ifdef DEBUG
        cout << k << " " << fileContent[k] << " " << index << " " << memTemp.getIndex() << " " << memTemp.getValue() << endl;
#endif
        diskCells.push_back(memTemp);
        k=j+1;

    }

#ifdef DEBUG
    cout << "memtest" << endl;
        printMemory();
#endif
    cout << "disk out put";
    for (int i = 0; i < diskCells.size(); ++i)
    {
        cout << i <<"  "<< diskCells[i].getValue() <<" , ";
        if(i%10==0 && i != 0){
            cout <<"\n";
        }
    }

    fileStream.close();
}

void Disk::fillDisk(int *array, int size) {
    for(int i=0; i < size; ++i){
        diskCells.push_back(MemoryCell(i,array[i]));
    }
}

int Disk::getIndex(int index) {
    return diskCells[index].getValue();
}

void Disk::getRange(int startPoint, int endPoint, int *arrayToFill) {
    for(int i=0; i + startPoint < endPoint; ++i){
        arrayToFill[i] = diskCells[i + startPoint].getValue();
    }
}

void Disk::setRange(int startPoint, int endPoint, int *arrayToFill) {
    for(int i = 0; i + startPoint < endPoint; ++i){
        diskCells[i].setValue(arrayToFill[i]);
    }
}

void Disk::setIndex(int index, int value) {
    diskCells[index].setValue(value);
}

int Disk::size() {
    return (int) diskCells.size();
}















