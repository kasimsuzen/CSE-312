//
// Created by siyah on 07.03.2016.
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
