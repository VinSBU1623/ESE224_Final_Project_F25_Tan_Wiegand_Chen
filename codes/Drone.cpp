// Drone.cpp
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Drone.h"

#define MAX_TASKS 5

// Constructor
Drone::Drone() {
    nextDrone = nullptr;
    ID = 0;         //initialize standard defaults 
}

// Linked List Methods
void Drone::setNextDrone(Drone* next){
    this->nextDrone = next;
}

Drone* Drone::getNextDrone() const{
    return this->nextDrone;
}

//Getters
string Drone::getName() {
    return name;
}
int Drone::getID() {
    return ID;
}
string* Drone::getTasks() {
    return task;
}
int* Drone::getInitPosition() {
    return init_position;
}
int (*Drone::getTaskPositions())[2] {
    return task_positions;
}

//Setters
void Drone::setName(string name) {
    this->name = name;    //Done::name = name
}
void Drone::setID(int id) {
    ID = id;
}
void Drone::setTaskAtIndex(string taskName, int index) {
    if (index >= 0 && index < MAX_TASKS) { //we don't want index to be out of bounds
        task[index] = taskName;
    }
}
void Drone::setInitPositionAtIndex(int value, int index) {
    if (index == 0 || index == 1) { //we don't want index to be out of bounds
        init_position[index] = value;
    }
}
void Drone::setTaskPositionAtIndex(int x, int y, int index) {
    if (index >= 0 && index < MAX_TASKS) { //we don't want index to be out of bounds
        task_positions[index][0] = x;
        task_positions[index][1] = y;
    }
}

//Sorting methods
void Drone::sortByAscending() { //using selection sort
    for (int i = 0; i < MAX_TASKS - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < MAX_TASKS; j++) {
            if (task[j] < task[minIndex]) {
                minIndex = j;
            }
        }
        //swap
        if (minIndex != i) {
            string tempTask = task[i];
            task[i] = task[minIndex];
            task[minIndex] = tempTask;

            //also swap corresponding task positions
            int tempX = task_positions[i][0];
            int tempY = task_positions[i][1];
            task_positions[i][0] = task_positions[minIndex][0];
            task_positions[i][1] = task_positions[minIndex][1];
            task_positions[minIndex][0] = tempX;
            task_positions[minIndex][1] = tempY;
        }
    }
}

void Drone::sortByDescending() { //using selection sort
    for (int i = 0; i < MAX_TASKS - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < MAX_TASKS; j++) {
            if (task[j] > task[maxIndex]) {
                maxIndex = j;
            }
        }
        //swap
        if (maxIndex != i) {
            string tempTask = task[i];
            task[i] = task[maxIndex];
            task[maxIndex] = tempTask;

            //also swap corresponding task positions
            int tempX = task_positions[i][0];
            int tempY = task_positions[i][1];
            task_positions[i][0] = task_positions[maxIndex][0];
            task_positions[i][1] = task_positions[maxIndex][1];
            task_positions[maxIndex][0] = tempX;
            task_positions[maxIndex][1] = tempY;
        }
    }
}

void Drone::displayDrone() {
    cout << "Drone Name: " << name << endl;
    cout << "Drone ID: " << ID << endl;
    cout << "Initial Position: (" << init_position[0] << ", " << init_position[1] << ")" << endl;
    cout << "Tasks and their Positions:" << endl;
    for (int i = 0; i < MAX_TASKS; i++) {
        cout << "  Task " << (i + 1) << ": " << task[i] 
             << " at Position (" << task_positions[i][0] << ", " << task_positions[i][1] << ")" << endl;
    }
}

//Operator overloads
void Drone::operator<<(Drone& d2) { //copy all attributes of d2 into this object
    name = d2.name;
    ID = d2.ID;
    for (int i = 0; i < MAX_TASKS; i++) {
        task[i] = d2.task[i];
        task_positions[i][0] = d2.task_positions[i][0];
        task_positions[i][1] = d2.task_positions[i][1];
    }
    init_position[0] = d2.init_position[0];
    init_position[1] = d2.init_position[1];
}

void Drone::operator-(Drone& d2) {  //swap task and task position between objects (init position is excluded)
    for (int i = 0; i < MAX_TASKS; i++) {
        //swap tasks
        string tempTask = task[i];
        task[i] = d2.task[i];
        d2.task[i] = tempTask;

        //swap task positions
        int tempX = task_positions[i][0];
        int tempY = task_positions[i][1];
        task_positions[i][0] = d2.task_positions[i][0];
        task_positions[i][1] = d2.task_positions[i][1];
        d2.task_positions[i][0] = tempX;
        d2.task_positions[i][1] = tempY;
    }
}