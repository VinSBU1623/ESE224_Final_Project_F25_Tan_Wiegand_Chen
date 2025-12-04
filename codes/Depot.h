#ifndef DEPOT_H
#define DEPOT_H

#include <vector>
#include <iostream>
#include <string>

#include "Drone.h"
#include "SpatialTree.h" 
#include "DroneManager.h"

using namespace std;

class Depot {
    private:
        vector<Drone> drones;

        // finals new content:
        Drone* head;

        Drone* stackTop;

        Drone* queueFront;
        Drone* queueRear;

        // finals new content end

        // instances of the Tree and Manager classes
        SpatialTree spatialTree;
        DroneManager<Drone> manager;

    public:
        Depot();    // This is a constructor, we need this to initialize pointers to nullptr

        // from Midterm =====
        void addDrone(Drone& d1);
        Drone& getDrone(int index);
        Drone* getDronePtr(int index);  // NEW!!! (Used for Stacks n Queues)

        void sortByName(); //manually, ascending
        void sortByID(); //manually, ascending
        void sortByPosition(); //manually, ascending by distance from origin
        int searchDroneByName(string& name); //Binary search
        int searchDroneByID(int id); //Binary search
        void swapDroneData(int index1, int index2);
        void copyDrone(int index1, int index2);
        //hint swap and copy operations can be one line coding
        
        void insertDroneTask(int droneidx, int taskidx, string& task, int task_pos[2]);
        void sortDroneDataAscending(int idx);
        void sortDroneDataDescending(int idx);
        void randomizeOrder(); //Manual shuffle, dont use preexsisting libs, might use std::swap
        void printAllNames();
        void writeDepotToFile(); //write to depot.txt



        // === NEW ==== Linked List 
        void addDroneToLinkedList(Drone* drone);
        void removeDroneFromLinkedList(int id);
        void printLinkedList(); // Helper to see if it works

        // === NEW ==== Stacks (LIFO)
        void pushDrone(Drone* drone);
        Drone* popDrone();

        // === NEW ==== QUEUE (FIFO)
        void enqueueDrone(Drone* drone);
        Drone* dequeueDrone();

        // === NEW ==== Tree and Template wrappers 
        void insertToTree(Drone* drone); // Calls spatialTree.insert
        Drone* searchInTree(int x, int y); // Calls spatialTree.search
};

#endif