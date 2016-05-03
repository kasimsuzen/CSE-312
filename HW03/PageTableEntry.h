//
// Created by kasim on 30.04.2016.
//

#pragma once

class PageTableEntry {
public:
    bool getIsModified() const;
    void setIsModified(bool isModified);

    bool getIsReferenced() const;
    void setIsReferenced(bool isReferenced);

    bool getIsPresent() const;
    void setIsPresent(bool isPresent);

    int getPageFrameNumber() const;
    void setPageFrameNumber(int pageFrameNumber);

    int getPhysicalAddressNumber() const;
    void setPhysicalAddressNumber(int physicalAddressNumber);

    PageTableEntry();

    PageTableEntry(int physicalAddressNumber, int pageFrameNumber);

private:
    bool isModified,isReferenced,isPresent;
    int pageFrameNumber,physicalAddressNumber;
};

