//
// Created by Kasım Süzen 111044034 on 07.03.2016
//

#ifndef HW01_MEMORY_H
#define HW01_MEMORY_H


class MemoryCell {
public:
    MemoryCell();

    MemoryCell(int indexData, int valueData);
    ~MemoryCell();

    int getIndex() const;
    void setIndex(int index);
    int getValue() const;
    void setValue(int value);

private:
    int index;
    int value;
};


#endif //HW01_MEMORY_H
