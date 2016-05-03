//
// Created by Kasım Süzen 111044034 on 07.03.2016
//
#include <string>

using namespace std;

#pragma once

class Instruction {
public:
    int getIndex() const;
    void setIndex(int index);
    const string &getInstruction() const;
    void setInstruction(const string &command);
    int getFirstOperand() const;
    void setFirstOperand(int A);
    int getSecondOperand() const;
    void setSecondOperand(int B);

    Instruction();

    Instruction(int i, string &s, int a=0, int b=0);
    ~Instruction();
private:
    int index;
    string command;                  //like "ADD" ,"SET" ...
    int A;
    int B;
};
