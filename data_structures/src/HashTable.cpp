//
// Created by Alex on 08/05/2019.
//

#include <iostream>

#include "HashTable.h"

// ------------------------------
//      LinkedList Methods
// ------------------------------

/**
 * Simple Constructor initializing the head node of the List and the size to zero.
 */
LinkedList::LinkedList() {
    head = new HashNode;
    head->next = nullptr;
    size = 0;
}

/**
 * Inserts a Hash Node to the end of the list of nodes. If no nodes exist in the list,
 * the given Node is put to the start of the list.
 * @param hashNode
 */
void LinkedList::insertNode(HashNode *hashNode) {
    if (head->next == nullptr) {
        head->next = hashNode;
        size++;
        return;
    } else {
        HashNode *last = head;
        while (last->next != nullptr) last = last->next;
        last->next = hashNode;
        hashNode->next = nullptr;
        size++;
    }
}

/**
 * Returns a boolean value, true if the given key is found in the List, false otherwise.
 * @param key The key to search for.
 * @return Whether the key was found or not.
 */
bool LinkedList::getNode(int key) {
    if (head->next == nullptr) return false;
    HashNode *current = head;
    while (current->next != nullptr) {
        if (current->next->i == key) return true;
        current = current->next;
    }
    return false;
}

/**
 * Linked List destructor; destroys all nodes from first to last.
 */
LinkedList::~LinkedList() {
    HashNode *current = head;
    while (current != nullptr) {
        HashNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

// ------------------------------
//       HashTable Methods
// ------------------------------

/**
 * Allocate memory for an array of Linked Lists of give size.
 * @param size The size of the array.
 */
void HashTable::init(int size) {
    numOfBuckets = size;
    hashTable = new LinkedList[size];
}

/**
 * Insert a new Hash Node to the Table. Get the node index from the hash function
 * and insert a new node to the appropriate list in the Hash Table.
 * @param fileData
 */
void HashTable::insertFromFile(int fileData) {
    int index = hashFunction(fileData);

    auto *newNode = new HashNode;
    newNode->i = fileData;
    newNode->next = nullptr;

    hashTable[index].insertNode(newNode);
}

/**
 * Insert a new Hash Node to the Table, after the input file has been read.
 * Copy old Hash Table to new one with more space and then insert new Hash Node.
 * @param newData
 */
void HashTable::insert(int newData) {
    //Allocate more space for new Data.
    auto *tempHashTable = new LinkedList[numOfBuckets + 1];
    std::copy(hashTable, hashTable + numOfBuckets, tempHashTable);
    delete[] hashTable;
    hashTable = tempHashTable;

    insertFromFile(newData);
}

/**
 * Modulo hash function. Returns an index calculated by the given key
 * modulo the size of the array of linked lists.
 *
 * @param key The key of the Node.
 * @return The index to insert the Node.
 */
int HashTable::hashFunction(int key) {
    return key % numOfBuckets;
}

/**
 * Search for a key in the Hash Table. Get the index for the array of Linked Lists from the hash function
 * and return true if the key was found, false otherwise.
 * @param element The key to find.
 * @return Whether the key was found.
 */
bool HashTable::searchHash(int key) {
    int index = hashFunction(key);
    return hashTable[index].getNode(key);
}

/**
 * Calculates the number of nodes in the Hash Table and returns that.
 * @return The number of nodes.
 */
int HashTable::getSize() {
    int numOfElements = 0;
    for (int i = 0; i < numOfBuckets; ++i) {
        numOfElements += hashTable[i].size;
    }
    return numOfElements;
}
