//
// Created by Kasım Süzen on 07.03.2016.
//

#ifndef HW01_MEMORY_H
#define HW01_MEMORY_H


class Memory {
public:
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


#endif //HW01_MEMORY_H
