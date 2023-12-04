
#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList() : sizeList(0), sizeArray(200) {
    aList = new objPos[sizeArray];

    int i = 0;
    while (i < sizeArray) {
        aList[i] = objPos();
        ++i;
    }
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos) {
    if (sizeList >= sizeArray) {
    resizeArray(sizeArray * 2);
    }

    objPos* newList = new objPos[sizeArray];

    newList[0] = thisPos;

    int i = 0;
    while (i < sizeList) {
        newList[i + 1] = aList[i];
        ++i;
    }

    delete[] aList;

    aList = newList;

    sizeList++;

}

void objPosArrayList::insertTail(objPos thisPos) {
    if (sizeList >= sizeArray) {
        resizeArray(sizeArray * 2); 

    }
    aList[sizeList] = thisPos;
    sizeList++;
}


void objPosArrayList::removeHead() {
    if (sizeList > 0) {
        int i = 0;
        while (i < sizeList - 1) {
            aList[i] = aList[i + 1];
            ++i;
        }
        sizeList--;
    }
}

void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        sizeList--;
    }
}




void objPosArrayList::getHeadElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1];
    }
}


void objPosArrayList::getElement(objPos &returnPos, int index) {
    if (index >= 0 && index < sizeList) {
        returnPos = aList[index];
    } else {
        returnPos = objPos(); 
    }
}

void objPosArrayList::resizeArray(int newCapacity) {
    // Function to resize the array to a new capacity limit

    if (newCapacity <= sizeList) {
    newCapacity = sizeList + 1;
    }

    objPos* newList = new objPos[newCapacity];

    int i = 0;
    while (i < sizeList) {
        newList[i] = aList[i];
        ++i;
    }

    delete[] aList;
    aList = newList;
    sizeArray = newCapacity;
}

