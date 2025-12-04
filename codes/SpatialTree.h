#ifndef SPATIALTREE_H
#define SPATIALTREE_H

#include "Drone.h"
#include <iostream>


struct SpatialNode {
    Drone* drone;       
    SpatialNode* left;  
    SpatialNode* right;

    SpatialNode(Drone* d) : drone(d), left(nullptr), right(nullptr) {}
};

class SpatialTree {
private:
    SpatialNode* root; 

    // Helper functions for recursion
    void insertRec(SpatialNode*& node, Drone* drone);
    Drone* searchRec(SpatialNode* node, int x, int y);
    void inOrderRec(SpatialNode* node);
    void preOrderRec(SpatialNode* node);
    void postOrderRec(SpatialNode* node);

public:
    SpatialTree();

    void insert(Drone* drone);
    Drone* search(int x, int y);

    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();
};

#endif