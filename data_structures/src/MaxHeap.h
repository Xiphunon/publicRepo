//
// Created by xiphunon on 12/04/19.
//

#ifndef DATA_STRUCTURES_MAXHEAP_H
#define DATA_STRUCTURES_MAXHEAP_H

#include <vector>

#include "Heap.h"

/**
 * Implementation of the Max Heap data structure, inheriting Heap class.
 */
class MaxHeap : public Heap {
private:
    void maxHeapify(int pos);

public:
    MaxHeap() = default;

    ~MaxHeap() = default;

    void insert(int key) final;

    void eof();

    int getMax();

    void deleteMax();
};

#endif //DATA_STRUCTURES_MAXHEAP_H
