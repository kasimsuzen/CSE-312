//
// Created by Kasım Süzen on 07.03.2016.
//

#include "Instruction.h"

Instruction::Instruction(int i, string &s, int a, int b) {
    index=i;
    command=s;
    A=a;
    B=b;
}

Instruction::~Instruction() {

}

Instruction::Instruction() {

}

int Instruction::getIndex() const {
    return index;
}

void Instruction::setIndex(int index) {
    Instruction::index = index;
}

const string &Instruction::getInstruction() const {
    return command;
}

void Instruction::setInstruction(const string &command) {
    Instruction::command = command;
}

int Instruction::getFirstOperand() const {
    return A;
}

void Instruction::setFirstOperand(int A) {
    Instruction::A = A;
}

int Instruction::getSecondOperand() const {
    return B;
}

void Instruction::setSecondOperand(int B) {
    Instruction::B = B;
}