//
// Created by George on 13/04/2019.
//

#include "AVL_Tree.h"

#include <iostream>

/**
 * Public method that calls the insert method with the root Node and the value to be added.
 * @param value The value to be added to the AVL Tree.
 */
void AVL_Tree::insertFromFile(int value) {
    root = insertNode(root, value);
}

/**
 * Inserts a new Node to the AVL Tree recursively in the right place and balances the tree.
 * @param node A pointer to the current Node of the tree
 * @param value The value to be added.
 * @return A pointer to the root of the tree with the new Node added, or a pointer to a part of the tree.
 */
Node *AVL_Tree::insertNode(Node *node, int value) {
    if (node == nullptr) {
        node = new Node;
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    } else if (value < node->value) { //If value to add smaller than the current Node value.
        node->left = insertNode(node->left, value);
        node = balance(node);
    } else if (value >= node->value) { //If value to add bigger than the current Node value.
        node->right = insertNode(node->right, value);
        node = balance(node);
    }
    return node;
}

/**
 * Checks if balancing is needed and rotates the Nodes according to the balance factor.
 * @param node A pointer to the current Node of the tree
 * @return A pointer to the root or part of the tree.
 */
Node *AVL_Tree::balance(Node *node) {
    int balFactor = getBalanceFactor(node);
    if (balFactor > 1) {
        if (getBalanceFactor(node->left) > 0) node = rotateLeft(node);
        else node = rotateLeftRight(node);
    } else if (balFactor < -1) {
        if (getBalanceFactor(node->right) > 0) node = rotateRightLeft(node);
        else node = rotateRight(node);
    }
    return node;
}

/**
 * Calculates the balance factor for given Node.
 * Returns the difference between the left and right subtree heights.
 * @param node The current node to calculate balance factor.
 * @return The balance factor.
 */
int AVL_Tree::getBalanceFactor(Node *node) {
    return (calculateHeight(node->left) - calculateHeight(node->right));
}

/**
 * Calculate the height of the Node.
 * @param node The node to calculate its height.
 * @return The height of the node.
 */
int AVL_Tree::calculateHeight(Node *node) {
    int height = 0;
    if (node) {
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        height = 1 + getMax(leftHeight, rightHeight);
    }
    return height;
}

/**
 * Public method that calls the delete method with the root Node and the value to be deleted.
 * @param value The value to be deleted from the AVL Tree.
 */
void AVL_Tree::deleteNode(int key) {
    root = deleteNode(root, key);
}

/**
 * Finds the Node with the key to be deleted from the AVL Tree recursively.
 * It deleted it and balances the tree.
 * @param node A pointer to the current Node of the tree/
 * @param value The value to be deleted.
 * @return A pointer to the root of the tree with the Node removed, or a pointer to a part of the tree.
 */
Node *AVL_Tree::deleteNode(Node *node, int key) {
    if (node == nullptr) return node;

    if (key < node->value) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->value) {
        node->right = deleteNode(node->right, key);
    } else { //If key found
        if (!(node->left && node->right)) { //If one or no children
            Node *temp = node->left ? node->left : node->right; //If node left exists, left, else right.

            if (temp == nullptr) { //If no children
                node = nullptr;
            } else { //If one child
                *node = *temp;
                delete temp;
            }
        } else { //If two children
            Node *temp = node->right;
            while (temp->left != nullptr) temp = temp->left;

            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
    }
    if (node == nullptr) return node;
    node = balance(node);
    return node;
}

/**
 * Single left rotation for the AVL Tree.
 * @param node The Node to perform the rotation.
 * @return A pointer to the new AVL Tree.
 */
Node *AVL_Tree::rotateLeft(Node *node) {
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

/**
 * Single right rotation for the AVL Tree.
 * @param node The Node to perform the rotation.
 * @return A pointer to the new AVL Tree.
 */
Node *AVL_Tree::rotateRight(Node *node) {
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

/**
 * A left rotation followed by a right rotation for the AVL Tree.
 * @param node The Node to perform the rotation.
 * @return A pointer to the new AVL Tree.
 */
Node *AVL_Tree::rotateLeftRight(Node *node) {
    Node *temp = node->left;
    node->left = rotateRight(temp);
    return rotateLeft(node);
}

/**
 * A right rotation followed by a left rotation for the AVL Tree.
 * @param node The Node to perform the rotation.
 * @return A pointer to the new AVL Tree.
 */
Node *AVL_Tree::rotateRightLeft(Node *node) {
    Node *temp = node->right;
    node->right = rotateLeft(temp);
    return rotateRight(node);
}

/**
 * Public method that calls the search method with the root Node and the value to be found.
 * @param value The value to search for in the AVL Tree.
 */
bool AVL_Tree::search(int key) {
    return search(root, key);
}

/**
 * Searches for the key in the tree recursively. Returns true if found, false otherwise.
 * @param node A pointer to the current Node of the AVL Tree to search in.
 * @param key The key to search for.
 * @return True if key was found, false otherwise.
 */
bool AVL_Tree::search(Node *node, int key) {
    if (node == nullptr) return false;
    else if (node->value > key) return search(node->left, key);
    else if (node->value < key) return search(node->right, key);
    else return true;
}

/**
 * Returns the value of the smallest node if the tree has a root, else -1.
 * @return The smallest value in the tree.
 */
int AVL_Tree::getSmallestNodeValue() {
    if (root) {
        Node *minNode = root;
        while (minNode->left) {
            minNode = minNode->left;
        }
        return minNode->value;
    } else return -1;
}

/**
 * Public method that calls the getSize method with the root Node.
 * @return The size of the AVL Tree.
 */
int AVL_Tree::getSize() {
    return getSize(root);
}

/**
 * Returns the size of the AVL Tree
 * @param node The root Node of the tree.
 * @return The size of the tree.
 */
int AVL_Tree::getSize(Node *node) {
    if (node == nullptr) return 0;
    return getSize(node->left) + getSize(node->right) + 1;
}

/**
 * Returns the max of two given numbers.
 * @param value1 The first number to compare.
 * @param value2 The second number to compare.
 * @return The biggest of the two given numbers.
 */
static int getMax(int value1, int value2) {
    return value1 > value2 ? value1 : value2;
}
