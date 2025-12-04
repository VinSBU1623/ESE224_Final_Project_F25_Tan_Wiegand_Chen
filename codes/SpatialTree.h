#ifndef SPATIALTREE_H
#define SPATIALTREE_H

#include "Drone.h"
#include <iostream>

// Page 4: Code Example "class SpatialNode" [cite: 136]
// We use a struct for public access simplicity within the tree logic
struct SpatialNode {
    Drone* drone;       // Page 4: "Drone* drone;" [cite: 138]
    SpatialNode* left;  // Page 4: "SpatialNode left;" (Corrected to pointer) 
    SpatialNode* right; // Page 4: "SpatialNode right;" (Corrected to pointer) [cite: 140]

    // Page 4: Constructor logic [cite: 141]
    SpatialNode(Drone* d) : drone(d), left(nullptr), right(nullptr) {}
};

// Page 4: Code Example "class SpatialTree"
class SpatialTree {
private:
    SpatialNode* root; // Page 4: "SpatialNode root;" (Corrected to pointer) 

    // Helper functions for recursion (Standard C++ Tree implementation practice)
    void insertRec(SpatialNode*& node, Drone* drone);
    Drone* searchRec(SpatialNode* node, int x, int y);
    void inOrderRec(SpatialNode* node);
    void preOrderRec(SpatialNode* node);
    void postOrderRec(SpatialNode* node);

public:
    SpatialTree(); // Constructor

    // Page 4: "void insert(Drone* drone);"
    void insert(Drone* drone);

    // Page 4: "Drone* search(int x, int y);"
    Drone* search(int x, int y);

    // Page 4: Traversal methods 
    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();
};

#endif