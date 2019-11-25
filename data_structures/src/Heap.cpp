//
// Created by xiphunon on 12/04/19.
//

#include <iostream>

#include "Heap.h"

/**
 * Insert a given value at the back of the vector without heapifing. Used to insert values to the vector from
 * the file given in main.
 * @param value The value to be inserted.
 */
void Heap::insertFromFile(int value) {
    vec.push_back(value);
    size++;
}

/**
 * Constructor reserving a vector of given size and testing if allocated properly.
 * @param s Size of vector to be reserved.
 */
void Heap::init(int s) {
    try {
        vec.reserve(s);
    } catch (std::bad_alloc &badAlloc) {
        std::cerr << "bad_alloc caught: " << badAlloc.what() << std::endl;
    }
}

/**
 * Swaps the elements corresponding to the given indices.
 * @param i The index of the first element.
 * @param j  The index of the second element.
 */
void Heap::swap(int i, int j) {
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
}

/**
 * Returns the left child index of the given index. If index is out of bounds, returns -1.
 * @param pos The index of the element to get their left child index.
 * @return The left child index.
 */
int Heap::getLeftIndex(int pos) {
    int index = 2 * pos + 1;
    if (index < size) return index;
    else return -1;
}

/**
 * Returns the right child index of the given index. If index is out of bounds, returns -1.
 * @param pos The index of the element to get their right child index.
 * @return The right child index.
 */
int Heap::getRightIndex(int pos) {
    int index = 2 * pos + 2;
    if (index < size) return index;
    else return -1;
}

/**
 * Returns the size of the heap.
 * @return Size of heap.
 */
int Heap::getSize() {
    return size;
}

/**
 * //FIXME ONLY FOR DEBUGGING. Prints all vector elements. REMOVE IOSTREAM
 */
void Heap::printArray() {
    for (int i{}; i < size; i++) std::cout << vec[i] << " ";
    std::cout << std::endl;
}
