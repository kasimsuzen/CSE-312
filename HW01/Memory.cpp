//
// Created by Kasım Süzen on 07.03.2016.
//

#include "Memory.h"

Memory::Memory(int indexData, int valueData){
    index = indexData;
    value = valueData;
}

Memory::~Memory() {

}

void Memory::setIndex(int index) {
    Memory::index = index;
}

void Memory::setValue(int value) {
    Memory::value = value;
}

int Memory::getValue() const {
    return value;
}

int Memory::getIndex() const {
    return index;
}