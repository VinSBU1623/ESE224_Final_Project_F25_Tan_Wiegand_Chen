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
        
        Drone* head;
        Drone* stackTop;
        Drone* queueFront;
        Drone* queueRear;

        SpatialTree spatialTree;
        DroneManager<Drone> manager;

    public:
        Depot();    // Constructor

        // from midterm
        void addDrone(Drone& d1);
        Drone& getDrone(int index);
        Drone* getDronePtr(int index);  // Stacks n queues

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
        void randomizeOrder(); //Manual shuffle, dont use preexsisting libs, might use swap
        void printAllNames();
        void writeDepotToFile(); //write to depot.txt



        //Linked List 
        void addDroneToLinkedList(Drone* drone);
        void removeDroneFromLinkedList(int id);
        void printLinkedList(); 

        //Stack
        void pushDrone(Drone* drone);
        Drone* popDrone();

        //Queue
        void enqueueDrone(Drone* drone);
        Drone* dequeueDrone();

        //Tree and template wrappers 
        void insertToTree(Drone* drone); 
        Drone* searchInTree(int x, int y);
};

#endif