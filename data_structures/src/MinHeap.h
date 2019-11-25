//
// Created by xiphunon on 02/04/19.
//

#ifndef DATA_STRUCTURES_MINHEAP_H
#define DATA_STRUCTURES_MINHEAP_H

#include <vector>

#include "Heap.h"

/**
 * Implementation of the Min Heap data structure, inheriting Heap class.
 */
class MinHeap : public Heap {
private:
    void minHeapify(int pos);

public:
    MinHeap() = default;

    ~MinHeap() = default;

    void insert(int key) final;

    void eof();

    int getMin();

    void deleteMin();
};

#endif //DATA_STRUCTURES_MINHEAP_H
