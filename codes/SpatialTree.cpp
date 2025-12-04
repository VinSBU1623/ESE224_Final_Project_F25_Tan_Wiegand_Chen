// SpatialTree.cpp

#include "SpatialTree.h"
#include <iostream>
using namespace std;

SpatialTree::SpatialTree() {
    root = nullptr;
}

// Page 4: "insert(Drone* drone): Inserts a drone into the tree based on its x-coordinate." 
void SpatialTree::insert(Drone* drone) {
    insertRec(root, drone);
}

void SpatialTree::insertRec(SpatialNode*& node, Drone* drone) {
    if (node == nullptr) {
        node = new SpatialNode(drone);
        return;
    }

    int droneX = drone->getInitPosition()[0];
    int droneY = drone->getInitPosition()[1];
    
    int nodeX = node->drone->getInitPosition()[0];
    int nodeY = node->drone->getInitPosition()[1];

    // Page 4: "If two drones have the same x-coordinate, the insertion can then be determined by the y-coordinate." [cite: 132]
    if (droneX < nodeX) {
        insertRec(node->left, drone);
    } else if (droneX > nodeX) {
        insertRec(node->right, drone);
    } else {
        // Tie-breaker using Y coordinate
        if (droneY < nodeY) {
            insertRec(node->left, drone);
        } else {
            insertRec(node->right, drone);
        }
    }
}

// Page 4: "search(int x, int y): Searches for a drone within the tree based on the given coordinates" [cite: 133]
Drone* SpatialTree::search(int x, int y) {
    return searchRec(root, x, y);
}

Drone* SpatialTree::searchRec(SpatialNode* node, int x, int y) {
    if (node == nullptr) {
        return nullptr; // Not found
    }

    int nodeX = node->drone->getInitPosition()[0];
    int nodeY = node->drone->getInitPosition()[1];

    // Exact match found
    if (nodeX == x && nodeY == y) {
        return node->drone;
    }

    // Logic must match insertion logic to find the node
    if (x < nodeX) {
        return searchRec(node->left, x, y);
    } else if (x > nodeX) {
        return searchRec(node->right, x, y);
    } else {
        // x is equal, check y tie-breaker
        if (y < nodeY) {
            return searchRec(node->left, x, y);
        } else {
            return searchRec(node->right, x, y);
        }
    }
}

// Page 4: "traverseInOrder() allows visualization" [cite: 109, 149]
void SpatialTree::traverseInOrder() {
    inOrderRec(root);
    cout << endl;
}

void SpatialTree::inOrderRec(SpatialNode* node) {
    if (node != nullptr) {
        inOrderRec(node->left);
        // Displaying basic info to prove traversal works
        cout << node->drone->getName() << " (" 
             << node->drone->getInitPosition()[0] << "," 
             << node->drone->getInitPosition()[1] << ") ";
        inOrderRec(node->right);
    }
}

// Page 4: "traversePreOrder()" [cite: 150]
void SpatialTree::traversePreOrder() {
    preOrderRec(root);
    cout << endl;
}

void SpatialTree::preOrderRec(SpatialNode* node) {
    if (node != nullptr) {
        cout << node->drone->getName() << " ";
        preOrderRec(node->left);
        preOrderRec(node->right);
    }
}

// Page 4: "traversePostOrder()" [cite: 151]
void SpatialTree::traversePostOrder() {
    postOrderRec(root);
    cout << endl;
}

void SpatialTree::postOrderRec(SpatialNode* node) {
    if (node != nullptr) {
        postOrderRec(node->left);
        postOrderRec(node->right);
        cout << node->drone->getName() << " ";
    }
}