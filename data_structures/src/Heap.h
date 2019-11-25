//
// Created by xiphunon on 12/04/19.
//

#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

#include <vector>

#include "DataStructInterface.h"

/**
 * Base class inherited by MinHeap and MaxHeap classes.
 * Since MinHeap and MaxHeap have many methods in common,
 * parent class Heap implements these here efficiently.
 * Uses the DataStruct Interface to ensure compatibility with other data structures.
 */
class Heap : public DataStructInterface {
protected:
    std::vector<int> vec;
    int size{};

    void swap(int i, int j);

    int getLeftIndex(int pos);

    int getRightIndex(int pos);

public:
    void init(int size) final;

    void insertFromFile(int value) final;

    virtual void insert(int value) = 0;

    int getSize();

    void printArray();
};

#endif //DATA_STRUCTURES_HEAP_H
