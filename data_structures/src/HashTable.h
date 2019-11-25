//
// Created by Alex on 08/05/2019.
//

#ifndef DATA_STRUCTURES_HASHTABLE_H
#define DATA_STRUCTURES_HASHTABLE_H

#include "DataStructInterface.h"

/**
 * Basic Node class for storing a value and a pointer to the next node in the list.
 * Has HashTable and LinkedList declared as friend classes to allow access to them
 * and avoid use of HashNode in other files.
 *
 * No methods are implemented for this class.
 */
class HashNode {
private:
    int i;
    HashNode *next;

    friend class HashTable;

    friend class LinkedList;

};

/**
 * Linked List class with basic methods for insertion and search.
 * Stores pointer to first node in list and list size.
 * Has HashTable declared as friend class.
 */
class LinkedList {
private:
    HashNode *head;
    int size;

    LinkedList();

    ~LinkedList();

    void insertNode(HashNode *hashNode);

    bool getNode(int key);

    friend class HashTable;
};

/**
 * The Hash Table class uses a modulo hash function
 * and an array of linked lists to implement chaining, in order to resolve conflicts.
 * Uses the DataStruct Interface to ensure compatibility with other data structures.
 */
class HashTable : public DataStructInterface {
private:
    LinkedList *hashTable;

    int numOfBuckets;
public:

    HashTable() : hashTable(nullptr), numOfBuckets(0) {};

    ~HashTable() { delete[] hashTable; }

    void init(int size) final;

    void insertFromFile(int fileData) final;

    void insert(int newData);

    int hashFunction(int number);

    int getSize();

    bool searchHash(int element);
};

#endif //DATA_STRUCTURES_HASHTABLE_H
