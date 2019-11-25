cmake_minimum_required(VERSION 3.13)
project(data_structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(data_structures src/main.cpp src/DataStructInterface.h src/MinHeap.cpp src/MinHeap.h src/MaxHeap.cpp src/MaxHeap.h src/Heap.cpp src/Heap.h src/HashTable.cpp src/HashTable.h src/AVL_Tree.cpp src/AVL_Tree.h src/Graph.h src/Graph.cpp)