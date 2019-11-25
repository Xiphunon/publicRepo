//
// Created by xiphunon on 01/04/19.
//

#include <fstream>
#include <iostream>
#include <chrono>
#include <functional>

#include "commandsDefinition.h"

#include "MinHeap.h"
#include "MaxHeap.h"
#include "HashTable.h"
#include "AVL_Tree.h"
#include "Graph.h"

#define commandFile "commands.txt"
#define outputFile "output.txt"

/**
 * A template function that tries to open a file and returns true if given file was opened, otherwise false.
 * @tparam fileStream A file stream template parameter, either input or output stream.
 * @param fs A file stream object.
 * @param filename The name of the file corresponding to the give file stream object.
 * @return A boolean value depending on whether or not a file has opened.
 */
template<typename fileStream>
bool checkOpenFile(fileStream &fs, const std::string &filename) {
    fs.open("../" + filename);
    return fs.is_open();
}

/**
 * Returns the number of elements in the filename file.
 * @param ifs An input file stream object.
 * @return The number of elements in the filename file.
 */
static int numOfElements(std::ifstream &ifs) {
    std::string element;
    int numOfElements = 0;
    while (ifs >> element) numOfElements++;
    return numOfElements;
}

/**
 * Initialises the appropriate data structure with the number of elements
 * returned by the `numOfElements` function if needed.
 * Reads elements from the input file and inserts them to that data structure.
 * @tparam dataStruct A data structure template parameter, whichever of the implemented data structs.
 * @param ds A data struct object.
 * @param ifs The input file stream to read elements from.
 * @param needsInit Whether or not the data structure needs spacial initialization.
 */
template<class dataStruct>
static void insertAll(dataStruct &ds, std::ifstream &ifs, bool needsInit) {
    std::string num;

    //Initialise the data structure.
    if (needsInit) ds.init(numOfElements(ifs));

    //Clear flags and go to beginning of input file.
    ifs.clear();
    ifs.seekg(0, std::ios::beg);

    //Read numbers from input file and insert them to the data structure.
    while (ifs >> num) ds.insertFromFile(stoi(num));
}

/**
 * Initialises the Graph data structure.
 * Reads elements from the input file and inserts them to that data structure.
 * @param graph A Graph data struct object.
 * @param ifs The input file stream to read elements from.
 */
static void insertAllGraph(Graph &graph, std::ifstream &ifs) {
    std::string num1, num2;

    //Clear flags and go to beginning of input file.
    ifs.clear();
    ifs.seekg(0, std::ios::beg);

    //Read numbers from input file and insert them to the data structure.
    while (ifs >> num1) {
        ifs >> num2;
        graph.insertGraph(stoi(num1), stoi(num2));
    }
}

/**
 * Main is responsible for reading commands from the command file by
 * correctly calling methods of the data structures corresponding to these commands as well as
 * printing the appropriate results returned by the requested methods to the file output.
 * In conjunction with the results of the methods,
 * the output file and the execution times of the commands are listed.
 */
int main() {

    std::ifstream inputCommandsStream, inputFileStream;
    std::ofstream outputStream;

    MinHeap minHeap;
    MaxHeap maxHeap;
    AVL_Tree avlTree;
    Graph graph;
    HashTable hashTable;

    if (checkOpenFile(inputCommandsStream, commandFile)) {
        std::clog << "OPENED COMMANDS FILE" << std::endl;

        if (checkOpenFile(outputStream, outputFile)) {
            std::clog << "CREATED OUTPUT FILE" << std::endl;

            std::string command;
            //Check for first command of line
            while (inputCommandsStream >> command) {

                // ------------------------------
                //        BUILD COMMANDS
                // ------------------------------
                if (command == BUILD) {
                    inputCommandsStream >> command;

                    if (command == MINHEAP) {
                        inputCommandsStream >> command;

                        if (checkOpenFile(inputFileStream, command)) {
                            //Init Min Heap and insert all elements of input file to it.
                            auto start = std::chrono::steady_clock::now();

                            insertAll(minHeap, inputFileStream, true);
                            minHeap.eof();

                            auto end = std::chrono::steady_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                            outputStream << BUILD << " " << MINHEAP << "\n";
                            outputStream << TIMEPRINT << duration.count() << "ns\n";

                        } else std::cerr << ERROROPENFILE << command << std::endl;
                    } else if (command == MAXHEAP) {
                        inputCommandsStream >> command;

                        if (checkOpenFile(inputFileStream, command)) {
                            //Init Max Heap and insert all elements of input file to it.
                            auto start = std::chrono::steady_clock::now();

                            insertAll(maxHeap, inputFileStream, true);
                            maxHeap.eof();

                            auto end = std::chrono::steady_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                            outputStream << BUILD << " " << MAXHEAP << "\n";
                            outputStream << TIMEPRINT << duration.count() << "ns\n";

                        } else std::cerr << ERROROPENFILE << command << std::endl;
                    } else if (command == AVLTREE) {
                        inputCommandsStream >> command;

                        if (checkOpenFile(inputFileStream, command)) {
                            //Init AVL Tree and insert all elements of input file to it.
                            auto start = std::chrono::steady_clock::now();

                            insertAll(avlTree, inputFileStream, false);

                            auto end = std::chrono::steady_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                            outputStream << BUILD << " " << AVLTREE << "\n";
                            outputStream << TIMEPRINT << duration.count() << "ns\n";

                        } else std::cerr << ERROROPENFILE << command << std::endl;

                    } else if (command == GRAPH) {
                        inputCommandsStream >> command;

                        if (checkOpenFile(inputFileStream, command)) {
                            //Init Graph and insert all elements of input file to it.
                            auto start = std::chrono::steady_clock::now();

                            insertAllGraph(graph, inputFileStream);

                            auto end = std::chrono::steady_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                            outputStream << BUILD << " " << GRAPH << "\n";
                            outputStream << TIMEPRINT << duration.count() << "ns\n";

                        } else std::cerr << ERROROPENFILE << command << std::endl;

                    } else if (command == HASHTABLE) {
                        inputCommandsStream >> command;

                        if (checkOpenFile(inputFileStream, command)) {
                            //Init Hash Table and insert all elements of input file to it.
                            auto start = std::chrono::steady_clock::now();

                            insertAll(hashTable, inputFileStream, true);

                            auto end = std::chrono::steady_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                            outputStream << BUILD << " " << HASHTABLE << "\n";
                            outputStream << TIMEPRINT << duration.count() << "ns\n";

                        } else std::cerr << ERROROPENFILE << command << std::endl;
                    }
                }

                // ------------------------------
                //        GETSIZE COMMANDS
                // ------------------------------
                if (command == GETSIZE) {
                    inputCommandsStream >> command;
                    if (command == MINHEAP) {
                        outputStream << GETSIZE << " " << MINHEAP << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << minHeap.getSize() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == MAXHEAP) {
                        outputStream << GETSIZE << " " << MAXHEAP << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << maxHeap.getSize() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == AVLTREE) {
                        outputStream << GETSIZE << " " << AVLTREE << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << avlTree.getSize() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == GRAPH) {
                        int vertices{};
                        int edges{};

                        outputStream << GETSIZE << " " << GRAPH << ": ";
                        auto start = std::chrono::steady_clock::now();

                        graph.getSize(vertices, edges);
                        outputStream << "V: " << vertices << " E: " << edges << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == HASHTABLE) {
                        outputStream << GETSIZE << " " << HASHTABLE << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << hashTable.getSize() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }

                // ------------------------------
                //    FINDMIN/FINDMAX COMMANDS
                // ------------------------------
                if (command == FINDMIN) {
                    inputCommandsStream >> command;
                    if (command == MINHEAP) {
                        outputStream << FINDMIN << " " << MINHEAP << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << minHeap.getMin() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == AVLTREE) {
                        outputStream << FINDMIN << " " << AVLTREE << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << avlTree.getSmallestNodeValue() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }
                if (command == FINDMAX) {
                    inputCommandsStream >> command;
                    if (command == MAXHEAP) {
                        outputStream << FINDMAX << " " << MAXHEAP << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << maxHeap.getMax() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }

                // ------------------------------
                //        SEARCH COMMANDS
                // ------------------------------
                if (command == SEARCH) {
                    inputCommandsStream >> command;
                    if (command == AVLTREE) {
                        outputStream << SEARCH << " " << AVLTREE << ": ";
                        inputCommandsStream >> command;

                        auto start = std::chrono::steady_clock::now();

                        if (avlTree.search(stoi(command))) {
                            outputStream << SUCCESS << "\n";
                        } else {
                            outputStream << FAILURE << "\n";
                        }

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == HASHTABLE) {
                        outputStream << SEARCH << " " << HASHTABLE << ": ";
                        inputCommandsStream >> command;

                        auto start = std::chrono::steady_clock::now();

                        if (hashTable.searchHash(stoi(command))) {
                            outputStream << SUCCESS << "\n";
                        } else {
                            outputStream << FAILURE << "\n";
                        }

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }

                // ------------------------------
                //     GRAPH SPECIFIC COMMANDS
                // ------------------------------
                if (command == COMPUTESHORTESTPATH) {
                    inputCommandsStream >> command;
                    if (command == GRAPH) {
                        std::string tempNumber;
                        inputCommandsStream >> tempNumber;
                        inputCommandsStream >> command;

                        outputStream << COMPUTESHORTESTPATH << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << graph.computeShortestPath(stoi(tempNumber), stoi(command)) << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }
                if (command == COMPUTESPANNINGTREE) {
                    inputCommandsStream >> command;
                    if (command == GRAPH) {
                        outputStream << COMPUTESPANNINGTREE << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << graph.computeSpanningTree() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }
                if (command == FINDCONNECTEDCOMPONENTS) {
                    inputCommandsStream >> command;
                    if (command == GRAPH) {
                        outputStream << FINDCONNECTEDCOMPONENTS << ": ";
                        auto start = std::chrono::steady_clock::now();

                        outputStream << graph.findConnectedComponents() << "\n";

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }

                // ------------------------------
                //        INSERT COMMANDS
                // ------------------------------
                if (command == INSERT) {
                    inputCommandsStream >> command;
                    if (command == MINHEAP) {
                        inputCommandsStream >> command;

                        outputStream << INSERT << " " << MINHEAP << "\n";
                        auto start = std::chrono::steady_clock::now();

                        minHeap.insert(stoi(command));

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == MAXHEAP) {
                        inputCommandsStream >> command;

                        outputStream << INSERT << " " << MAXHEAP << "\n";
                        auto start = std::chrono::steady_clock::now();

                        maxHeap.insert(stoi(command));

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == AVLTREE) {
                        inputCommandsStream >> command;
                        
                        outputStream << INSERT << " " << AVLTREE << "\n";
                        auto start = std::chrono::steady_clock::now();

                        avlTree.insertFromFile(stoi(command));

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == GRAPH) {
                        std::string tempNumber;
                        inputCommandsStream >> tempNumber;
                        inputCommandsStream >> command;

                        outputStream << INSERT << " " << GRAPH << "\n";
                        auto start = std::chrono::steady_clock::now();

                        graph.insertGraph(stoi(tempNumber), stoi(command));

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == HASHTABLE) {
                        inputCommandsStream >> command;

                        outputStream << INSERT << " " << HASHTABLE << "\n";
                        auto start = std::chrono::steady_clock::now();

                        hashTable.insertFromFile(stoi(command));

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }

                // ------------------------------
                //        DELETE COMMANDS
                // ------------------------------
                if (command == DELETEMIN) {
                    inputCommandsStream >> command;
                    if (command == MINHEAP) {
                        outputStream << DELETEMIN << " " << MINHEAP << "\n";
                        auto start = std::chrono::steady_clock::now();

                        minHeap.deleteMin();

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }
                if (command == DELETEMAX) {
                    inputCommandsStream >> command;
                    if (command == MAXHEAP) {
                        outputStream << DELETEMAX << " " << MAXHEAP << "\n";
                        auto start = std::chrono::steady_clock::now();

                        maxHeap.deleteMax();

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }
                if (command == DELETE) {
                    inputCommandsStream >> command;
                    if (command == AVLTREE) {
                        inputCommandsStream >> command;
                        outputStream << DELETE << " " << AVLTREE << "\n";
                        auto start = std::chrono::steady_clock::now();

                        avlTree.deleteNode(stoi(command));

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    } else if (command == GRAPH) {
                        std::string tempNumber;
                        inputCommandsStream >> tempNumber;
                        inputCommandsStream >> command;

                        outputStream << DELETE << " " << GRAPH << "\n";
                        auto start = std::chrono::steady_clock::now();

                        graph.deleteGraph(stoi(tempNumber), stoi(command));

                        auto end = std::chrono::steady_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                        outputStream << TIMEPRINT << duration.count() << "ns\n";

                    }
                }
            } //End of while
            std::clog << "END OF COMMANDS FILE" << std::endl;
            inputCommandsStream.close();
            inputFileStream.close();
            outputStream.close();
        } else { //if outputFile
            std::cerr << "ERROR CREATING OUTPUT FILE" << std::endl;
        }
    } else { //if inputFile
        std::cerr << ERROROPENFILE << commandFile << std::endl;
    }
    return 0;
}
