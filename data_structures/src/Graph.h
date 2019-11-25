//
// Created by Alex on 1/6/2019.
//

#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H

#include <vector>

#include "DataStructInterface.h"

using namespace std;

/**
 * Graph Node class used
 */
class GraphNode {
private:
    friend class Graph;

    int value, cost;
    bool status;

public:

    explicit GraphNode(int value);

    ~GraphNode() = default;

    bool operator==(const GraphNode &node);
};

class Graph : public DataStructInterface {
public:
    Graph() = default;

    void insertGraph(int v, int u);

    void deleteGraph(int v, int u);

    void getSize(int &v, int &e);

    int findNode();

    int exists(int k);

    int findConnectedComponents();

    void BFS();

    int computeSpanningTree();

    int computeShortestPath(int v, int u);

    void createNewEdge(int v, int u);

    void init(int size) final {};

private:
    void insertFromFile(int value) final {};

    vector<vector<GraphNode>> adj;                //Vector of vectors
    vector<GraphNode> searching;
    vector<GraphNode> visited;
    vector<GraphNode> inMST;
};


#endif //DATA_STRUCTURES_GRAPH_H
