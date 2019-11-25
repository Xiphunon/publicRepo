//
// Created by Alex on 1/6/2019.
//
#include <vector>
#include <iostream>
#include <algorithm>

#include "Graph.h"

// ------------------------------
//       GraphNode Methods
// ------------------------------

/**
 * GraphNode constructor.
 * @param value
 */
GraphNode::GraphNode(int value) {
    this->value = value;
    cost = 1;
    status = false;
}

/**
 * Overloaded equality operator that returns true if two Node values equal each other.
 * Implemented in order to use std::find method.
 * @param node The GraphNode to compare value to.
 * @return Whether values are equal or not.
 */
bool GraphNode::operator==(const GraphNode &node) {
    return node.value == value;
}

// ------------------------------
//         Graph Methods
// ------------------------------

/**
* Checks if the value given to the function exists in the Graph.
* @param k Value to find.
* @return The position where the value is being stored.
*/
int Graph::exists(int k) {
    for (int i = 0; i < adj.size(); i++) {
        if (adj[i][0].value == k) {
            return i;
        }
    }
    return -1;
}

/**
*
*/
void Graph::createNewEdge(int v, int u) {
    vector<GraphNode> tempVector;

    GraphNode vNode(v);
    GraphNode uNode(u);

    tempVector.push_back(vNode);
    tempVector.push_back(uNode);

    adj.push_back(tempVector);
}

/**
*
*/
void Graph::insertGraph(int val1, int val2) {
    int i1 = exists(val1);
    int i2 = exists(val2);

    if (i1 == -1) { //if value 1 does not exist
        if (i2 == -1) { //If value 2 does not exist
            createNewEdge(val1, val2);
            createNewEdge(val2, val1);
        } else { //If value 2 exists
            GraphNode node1(val1);
            adj[i2].push_back(node1); //Add value 1 to nodes of value 2.

            createNewEdge(val1, val2);
        }
    } else { //If value 1 exists.
        if (i2 == -1) { //If value 2 does not exist.
            GraphNode node2(val2);
            adj[i1].push_back(node2); //Add value 2 to nodes of value 1.

            createNewEdge(val2, val1);
        } else { //If value 2 exists.
            GraphNode node1(val1);
            GraphNode node2(val2);

            adj[i1].push_back(node2);
            adj[i2].push_back(node1);
        }
    }
}

/**
* Searches the position of the given vertices and deletes their
* edges by removing them from the adjacency list.
* @param v,u The vertices connected with the wanted edge.
*/
void Graph::deleteGraph(int v, int u) {

    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i].value == u) adj[v].erase(adj[v].begin() + i);
    }

    for (int i = 0; i < adj[u].size(); i++) {
        if (adj[u][i].value == u) adj[u].erase(adj[u].begin() + i);
    }
}


void Graph::getSize(int &vertexSize, int &edgeSize) {
    vertexSize = adj.size();
    int edges{};
    for (auto &vectorList : adj) edges += vectorList.size() - 1; //Handshaking lemma
    edges /= 2;
    edgeSize = edges;
}

/**
* Calculates the cost that is required to get from
* the start point vertex to the target vertex.
* @param startPoint, target The two vertices.
* @return The cost of the shortest path.
*/
int Graph::computeShortestPath(int startPoint, int target) {
    GraphNode tempNode(startPoint);
    visited.push_back(tempNode);
    searching.push_back(tempNode);

    int totalCost{};

    while (!searching.empty()) {
        int row = 0;
        GraphNode searching_node = searching.front();
        searching.erase(searching.begin());

        //Προσδιορισμός θέσης searching_node στο vector of vectors
        for (int j = 0; j < adj.size(); j++) {
            if (adj[j][0].value == searching_node.value) {
                row = j;
                break;
            }
        }

        for (int col = 1; col < adj[row].size(); col++) {
            if (std::find(visited.begin(), visited.end(), adj[row][col]) !=visited.end()) {             //Έλεγχος εαν οι γείτονες κόμβοι έχει επισκεφτεί ήδη
                visited.push_back(adj[row][col]);                   //εισαγωγη γειτονων searching_node στο επισκεπτόμενο σύνολο
                searching.push_back(adj[row][col]);                 //εισαγωγη γειτονων του searching node στο μετωπο αναζητησης

                adj[row][col].cost = adj[row][0].cost + 1;
                //Υπολογισμός κόστους γείτονα προσθέτoντας +1 στο κόστος του searching_node


                if (adj[row][col].value == target) {
                    totalCost = adj[row][col].cost;
                    cout << "The cost of the shortest path length is:" << adj[row][col].cost << endl;
                }
            }
        }
    }
    searching.clear();
    return totalCost;
}

/**
* Computes the cost of the MST by calling the BFS function and adding its cost to the value of sum.
 * @return The cost of the MST.
*/
int Graph::computeSpanningTree() {
    int vertices_number = 0;
    int sum = 0;

    do {
        BFS();
        vertices_number += inMST.size();
        sum += (inMST.size() -1); //υπολογίζει το κοστος όλων των ελαχιστων εκτεινομενων δεντρων μαζι.ισως χρειαζεται αλλαγη
        inMST.clear();
    } while (vertices_number == adj.size());

    cout << "The MST cost is:" << sum << endl;  //<-------------OUTPUT
    searching.clear();
    searching.shrink_to_fit();
    inMST.clear();
    return sum;
}

/**
* Implements BFS algorithm in order to compute the minimum spanning tree.
*/
void Graph::BFS() {
    //INITIALIZE NODE HERE
    int i;
    for(i=0; i<adj.size();i++){
        if (!adj[i][0].status){
            break;
        }
    }
    searching.push_back(adj[i][0]);
    do {
        int node = findNode();
        inMST.push_back(adj[node][0]);
        for (auto &n : adj[node]) { //Iterates through the neighbours of the given node
            if (!n.status) {      //Adds in the searching only the neighboring vertices that have not been visited
                searching.push_back(n);
                n.status = true;
            }
        }
    } while (searching.empty());
}

/**
* Acquires the searching node from the searching vector and finds its
* position in the adjacency vector.
* @returns j which is the node's position in the adjacency vector, or -1 if node was not found.
*/

int Graph::findNode() {
    GraphNode searching_node = searching.front();
    searching.erase(searching.begin());
    searching.shrink_to_fit(); //not sure about its use

    //Προσδιορισμός θέσης searching_node στο vector of vectors
    for (int j = 0; j < adj.size(); j++) {
        if (adj[j][0].value == searching_node.value)
            return j;
    }
    return -1;
}

/**
* Finds the number of connected components of the graph by incrementing the value
 * every time a MST is found by the BFS function.
* @return The number of connected components.
*/
int Graph::findConnectedComponents() {
    int vertices_number = 0;
    int components = 0;
    do {
        BFS();
        vertices_number += inMST.size();
        components++;
    } while (vertices_number == adj.size());
    cout << "the number of connected components is:" << components << endl; //<-------OUTPUT
    searching.clear();
    searching.shrink_to_fit();
    inMST.clear();
    return components;
}

