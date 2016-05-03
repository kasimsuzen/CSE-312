//
// Created by kasim on 30.04.2016.
//

#include "PageTableEntry.h"

PageTableEntry::PageTableEntry() {
    isPresent = false;
    isModified = false;
    isReferenced = false;
}

PageTableEntry::PageTableEntry(int physicalAddressNumber, int pageFrameNumber)
        : physicalAddressNumber(physicalAddressNumber),
          pageFrameNumber(pageFrameNumber) {
    isModified = false;
    isReferenced = false;
    isPresent = true;
}

void PageTableEntry::setPhysicalAddressNumber(int physicalAddressNumber) {
    PageTableEntry::physicalAddressNumber = physicalAddressNumber;
}

int PageTableEntry::getPhysicalAddressNumber() const {
    return physicalAddressNumber;
}

void PageTableEntry::setPageFrameNumber(int pageFrameNumber) {
    PageTableEntry::pageFrameNumber = pageFrameNumber;
}

int PageTableEntry::getPageFrameNumber() const {
    return pageFrameNumber;
}

void PageTableEntry::setIsPresent(bool isPresent) {
    PageTableEntry::isPresent = isPresent;
}

bool PageTableEntry::getIsPresent() const {
    return isPresent;
}

void PageTableEntry::setIsReferenced(bool isReferenced) {
    PageTableEntry::isReferenced = isReferenced;
}

bool PageTableEntry::getIsModified() const {
    return isModified;
}

void PageTableEntry::setIsModified(bool isModified) {
    PageTableEntry::isModified = isModified;
}

bool PageTableEntry::getIsReferenced() const {
    return isReferenced;
}