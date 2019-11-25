//
// Created by xiphunon on 02/04/19.
//

#include "MinHeap.h"

/**
 * Heapify for every vector element required; only the first half elements need heapifying.
 */
void MinHeap::eof() {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        minHeapify(i);
    }
}

/**
 * Recursively builds a heap from the bottom up by successively sifting downward to establish the heap property.
 * @param pos The index to start the Heapify process from.
 */
void MinHeap::minHeapify(int pos) {
    int left = getLeftIndex(pos);
    int right = getRightIndex(pos);
    int smallest = pos;

    if (vec[left] < vec[smallest] && left != -1) smallest = left;
    if (vec[right] < vec[smallest] && right != -1) smallest = right;
    if (smallest != pos) {
        swap(pos, smallest);
        minHeapify(smallest);
    }
}

/**
 * Returns the vector min value; the first element.
 * @return The min value of the heap.
 */
int MinHeap::getMin() {
    return vec[0];
}

/**
 * Deletes the min value; replaces the first element with the last and deletes it from the end. Decreases size by 1.
 * Heapifies the Min Heap.
 */
void MinHeap::deleteMin() {
    vec[0] = vec.back();
    vec.pop_back();
    size--;
    eof();
}

/**
 * Inserts a given key to the heap, at the last position. Increases size by one and heapifies.
 * @param key The key to be inserted.
 */
void MinHeap::insert(int key) {
    vec.push_back(key);
    size++;
    eof();
}