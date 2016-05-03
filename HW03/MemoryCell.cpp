//
// Created by Kasım Süzen 111044034 on 07.03.2016
//

#include "MemoryCell.h"

MemoryCell::MemoryCell(int indexData, int valueData){
    index = indexData;
    value = valueData;
}

MemoryCell::~MemoryCell() {

}

void MemoryCell::setIndex(int index) {
    MemoryCell::index = index;
}

void MemoryCell::setValue(int value) {
    MemoryCell::value = value;
}

int MemoryCell::getValue() const {
    return value;
}

int MemoryCell::getIndex() const {
    return index;
}

MemoryCell::MemoryCell() {

}
