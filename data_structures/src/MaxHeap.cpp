//
// Created by xiphunon on 12/04/19.
//

#include "MaxHeap.h"

/**
 * Heapify for every vector element required; only the first half elements need heapifying.
 */
void MaxHeap::eof() {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        maxHeapify(i);
    }
}

/**
 * Recursively builds a heap from the bottom up by successively sifting downward to establish the heap property.
 * @param pos The index to start the Heapify process from.
 */
void MaxHeap::maxHeapify(int pos) {
    int left = getLeftIndex(pos);
    int right = getRightIndex(pos);
    int largest = pos;

    if (vec[left] > vec[largest] && left != -1) largest = left;
    if (vec[right] > vec[largest] && right != -1) largest = right;
    if (largest != pos) {
        swap(pos, largest);
        maxHeapify(largest);
    }
}

/**
 * Returns the vector max value; the first element.
 * @return The max value of the heap.
 */
int MaxHeap::getMax() {
    return vec[0];
}

/**
 * Deletes the max value; replaces the first element with the last and deletes it from the end. Decreases size by 1.
 * Heapifies the Max Heap.
 */
void MaxHeap::deleteMax() {
    vec[0] = vec.back();
    vec.pop_back();
    size--;
    eof();
}

/**
 * Inserts a given key to the heap, at the last position. Increases size by one and heapifies.
 * @param key The key to be inserted.
 */
void MaxHeap::insert(int key) {
    vec.push_back(key);
    size++;
    eof();
}