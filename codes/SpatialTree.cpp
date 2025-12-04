#include "SpatialTree.h"
#include <iostream>
using namespace std;

SpatialTree::SpatialTree() {
    root = nullptr;
}

void SpatialTree::insert(Drone* drone) { //insert
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

    if (droneX < nodeX) {
        insertRec(node->left, drone);
    } else if (droneX > nodeX) {
        insertRec(node->right, drone);
    } else {
        if (droneY < nodeY) {
            insertRec(node->left, drone);
        } else {
            insertRec(node->right, drone);
        }
    }
}

Drone* SpatialTree::search(int x, int y) { //search drone in tree
    return searchRec(root, x, y);
}

Drone* SpatialTree::searchRec(SpatialNode* node, int x, int y) {
    if (node == nullptr) {
        return nullptr;
    }

    int nodeX = node->drone->getInitPosition()[0];
    int nodeY = node->drone->getInitPosition()[1];

    if (nodeX == x && nodeY == y) {
        return node->drone;
    }

    if (x < nodeX) {
        return searchRec(node->left, x, y);
    } else if (x > nodeX) {
        return searchRec(node->right, x, y);
    } else {
        if (y < nodeY) {
            return searchRec(node->left, x, y);
        } else {
            return searchRec(node->right, x, y);
        }
    }
}

void SpatialTree::traverseInOrder() { //traverse
    inOrderRec(root);
    cout << endl;
}

void SpatialTree::inOrderRec(SpatialNode* node) {
    if (node != nullptr) {
        inOrderRec(node->left);
        cout << node->drone->getName() << " (" 
             << node->drone->getInitPosition()[0] << "," 
             << node->drone->getInitPosition()[1] << ") ";
        inOrderRec(node->right);
    }
}

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