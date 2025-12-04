// Depot.cpp
#include "Depot.h"
#include "Drone.h"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;


//Constructor
Depot::Depot() {
    stackTop = nullptr;
    queueFront = nullptr;
    queueRear = nullptr;
    head = nullptr;
}

// ====================== NEW STUFFFFFFFFFF ========================
// --- MISSING HELPER ---
Drone* Depot::getDronePtr(int index) {
    if (index >= 0 && index < drones.size()) {
        return &drones[index];
    }
    return nullptr;
}

void Depot::addDroneToLinkedList(Drone* drone) {
    if (head == nullptr) {
        head = drone;
        drone->setNextDrone(nullptr);
        return;
    }
    if (drone->getID() < head->getID()) {
        drone->setNextDrone(head);
        head = drone;
        return;
    }
    Drone* current = head;
    while (current->getNextDrone() != nullptr && 
           current->getNextDrone()->getID() < drone->getID()) {
        current = current->getNextDrone();
    }
    drone->setNextDrone(current->getNextDrone());
    current->setNextDrone(drone);
}

void Depot::removeDroneFromLinkedList(int id) {
    if (head == nullptr){
        return;
    }
    if (head->getID() == id) {
        Drone* temp = head;
        head = head->getNextDrone();
        temp->setNextDrone(nullptr); 
        return;
    }
    Drone* current = head;
    while (current->getNextDrone() != nullptr && current->getNextDrone()->getID() != id) {
        current = current->getNextDrone();
    }
    if (current->getNextDrone() != nullptr) {
        Drone* toDelete = current->getNextDrone();
        current->setNextDrone(toDelete->getNextDrone());
        toDelete->setNextDrone(nullptr);
    }
}

void Depot::printLinkedList() {
    Drone* current = head;
    cout << "Linked List: ";
    while (current != nullptr) {
        cout << "[ID:" << current->getID() << "] -> ";
        current = current->getNextDrone();
    }
    cout << "NULL" << endl;
}

void Depot::insertToTree(Drone* drone) {
    spatialTree.insert(drone);
}

Drone* Depot::searchInTree(int x, int y) {
    return spatialTree.search(x, y);
}


//Drone Stack

//Push
void Depot::pushDrone(Drone* drone) {
    drone->setNextDrone(stackTop);
    stackTop = drone;
}

//Pop
Drone* Depot::popDrone() {
    if (stackTop == nullptr) {
        return nullptr; 
    }
    Drone* temp = stackTop;    
    stackTop = stackTop->getNextDrone();    
    temp->setNextDrone(nullptr);
    
    return temp;
}

//Drone Queue

//Enqueue
void Depot::enqueueDrone(Drone* drone) {
    drone->setNextDrone(nullptr);
    if (queueRear == nullptr) {
        queueFront = drone;
        queueRear = drone;
    } else {
        queueRear->setNextDrone(drone);
        queueRear = drone;
    }
}

//Dequeue
Drone* Depot::dequeueDrone() {
    if (queueFront == nullptr) {
        return nullptr;
    }
    Drone* temp = queueFront;    
    queueFront = queueFront->getNextDrone();    
    if (queueFront == nullptr) {
        queueRear = nullptr;
    }    
    temp->setNextDrone(nullptr);
    return temp;
}

void Depot::addDrone(Drone& d1){
    drones.push_back(d1);   // add drone to the vector
}
Drone& Depot::getDrone(int index){
    return drones.at(index);    // returns the reference to the drone (at the given index)
}
void Depot::sortByName(){
    for (int i = 0; i < drones.size() - 1; i++) {   //selection sort
        int minIndex = i;
        for (int j = i + 1; j < drones.size(); j++) {
            if (drones[j].getName() < drones[minIndex].getName()) {
                minIndex = j;
            }
        }
        //swap
        if (minIndex != i) {
            Drone temp = drones[i];
            drones[i] = drones[minIndex];
            drones[minIndex] = temp;           
        }
    }
}

void Depot::sortByID(){ 
    for (int i = 0; i < drones.size() - 1; i++) {   // selection sort
        int minIndex = i;
        for (int j = i + 1; j < drones.size(); j++) {
            if (drones[j].getID() < drones[minIndex].getID()) {
                minIndex = j;
            }
        }
        //swap
        if (minIndex != i) {
            Drone temp = drones[i];
            drones[i] = drones[minIndex];
            drones[minIndex] = temp;           
        }
    }
}

void Depot::sortByPosition(){
    for (int i = 0; i < drones.size() - 1; i++) {   // selection sort
        int minIndex = i;
        for (int j = i + 1; j < drones.size(); j++) {
            if (sqrt(pow(drones[j].getInitPosition()[0], 2) + pow(drones[j].getInitPosition()[1], 2)) < 
                sqrt(pow(drones[minIndex].getInitPosition()[0], 2) + pow(drones[minIndex].getInitPosition()[1], 2))) {
                minIndex = j;
            }
        }
        //swap 
        if (minIndex != i) {
            Drone temp = drones[i];
            drones[i] = drones[minIndex];
            drones[minIndex] = temp;           
        }
    }
}

int Depot::searchDroneByName(string& name){     // utilizes binary search!
    int left = 0;
    int right = drones.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (drones[mid].getName() == name){
            return mid;
        }
        else if (drones[mid].getName() < name){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
int Depot::searchDroneByID(int id){     // utilizes binary search!
    int left = 0;   
    int right = drones.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (drones[mid].getID() == id){
            return mid;
        }
        else if (drones[mid].getID() < id){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
void Depot::swapDroneData(int index1, int index2){     // uses operator overload (-) to swap data. 
    drones.at(index1) - drones.at(index2);
}

void Depot::copyDrone(int index1, int index2){      // uses operator overload (<<) to copy data.
    drones.at(index2)<<drones.at(index1);
}

void Depot::insertDroneTask(int droneidx, int taskidx, string& task, int task_pos[2]){
    //todo
    drones.at(droneidx).setTaskAtIndex(task, taskidx);
    drones.at(droneidx).setTaskPositionAtIndex(task_pos[0], task_pos[1], taskidx);
}

void Depot::sortDroneDataAscending(int idx){
    drones.at(idx).sortByAscending();
}
void Depot::sortDroneDataDescending(int idx){
    drones.at(idx).sortByDescending();
}
void Depot::randomizeOrder(){ //Unsure
    srand(time(0));
    for (int i = 0; i < drones.size(); i++){
        int newpos = rand() % drones.size();
        swap(drones.at(i), drones.at(newpos));
    }
}
void Depot::printAllNames(){
    for (Drone d : drones){
        cout << d.getName() << endl;
    }
}
void Depot::writeDepotToFile(){
    ofstream fout("Depot.txt");
    for (Drone d : drones){
        fout << d.getName() << " " << d.getID() << endl;

        int* initPos = d.getInitPosition();
        fout << initPos[0] << " " << initPos[1] << endl;

        string* tasks = d.getTasks();
        int (*taskPositions)[2] = d.getTaskPositions();
        
        for (int i = 0; i < 5; i++){
            fout << tasks[i] << " " << taskPositions[i][0] << " " << taskPositions[i][1] << endl;
        }
        fout << endl << endl;
    }
    fout.close();
}
