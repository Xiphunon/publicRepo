//
// Created by George on 13/04/2019.
//

#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include "DataStructInterface.h"

/**
 * Basic Node structure for storing a value and two pointers,
 * one to the left child node and one to right child.
 * Has AVL_Tree declared as friend classes to allow access
 * and avoid use of Node in other files.
 *
 * No methods are implemented for this class.
 */
class Node {
private:
    friend class AVL_Tree;

    int value;
    Node *left, *right;

    Node() = default;

    ~Node() = default;
};

/**
 * The AVL_Tree class implements a self-balancing binary search tree
 * using objects from the Node Class as nodes, starting with the root Node
 * and adding pointers to children Nodes to it accordingly.
 *
 * Most methods have both a public and a private implementation.
 * The public implementation is used in main to pass the root Node to the static private method.
 *
 * Uses the DataStruct Interface to ensure compatibility with other data structures.
 */
class AVL_Tree : public DataStructInterface {
private:
    Node *root;

    static Node *insertNode(Node *node, int key);

    static Node *deleteNode(Node *node, int key);

    static bool search(Node *node, int key);

    static Node *balance(Node *node);

    static int getBalanceFactor(Node *node);

    static int calculateHeight(Node *node);

    static int getSize(Node *node);

    static Node *rotateLeft(Node *node);

    static Node *rotateRight(Node *node);

    static Node *rotateLeftRight(Node *node);

    static Node *rotateRightLeft(Node *node);

public:
    AVL_Tree() : root(nullptr) {};

    ~AVL_Tree() = default;

    void init(int size) final {};

    void insertFromFile(int value) final;

    void deleteNode(int key);

    int getSize();

    int getSmallestNodeValue();

    bool search(int key);
};

static int getMax(int val1, int val2);

#endif //DATA_STRUCTURES_AVL_TREE_H
