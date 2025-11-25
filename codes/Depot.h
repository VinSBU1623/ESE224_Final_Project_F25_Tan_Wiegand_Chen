#ifndef DEPOT_H
#define DEPOT_H
#include <vector>
#include "Drone.h"
#include <iostream>
#include <string>
using namespace std;

class Depot {
    private:
        vector<Drone> drones;
    public:
        void addDrone(Drone& d1);
        Drone& getDrone(int index);
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
};
#endif