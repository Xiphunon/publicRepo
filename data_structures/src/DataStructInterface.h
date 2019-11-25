//
// Created by xiphunon on 02/04/19.
//

#ifndef DATA_STRUCTURES_DATASTRUCTINTERFACE_H
#define DATA_STRUCTURES_DATASTRUCTINTERFACE_H

/**
 * Interface class used in all Data Structures to ensure class compatibility with functions used in main.
 */
class DataStructInterface {
public:
    virtual void init(int size) = 0;

    virtual void insertFromFile(int value) = 0;
};

#endif //DATA_STRUCTURES_DATASTRUCTINTERFACE_H
