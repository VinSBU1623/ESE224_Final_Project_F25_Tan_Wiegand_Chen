#ifndef DRONE_H
#define DRONE_H
#include <string>
using namespace std;

class Drone { 
    private:
        string name;    //name of the drone
        int ID;
        string task[5];             //last delivery tasks' name
        int init_position[2];       //(x,y) location in the area
        int task_positions[5][2];   //(x,y) location of last delivery tasks

        // NEW - LINKED LIST PTR (see pg 2)
        Drone* nextDrone;

    public:
        // constructor
        Drone();    

        // getters
        string getName();
        int getID();
        string* getTasks();         //  we need a pointer here to return the array
        int* getInitPosition();     //  we need a pointer here to return the array
        int (*getTaskPositions())[2]; //  we need a pointer here to return the 2D array


        // NEW - LINKED LIST METHOD (see pg 2)
        void setNextDrone(Drone* next);
        Drone* getNextDrone() const;

        // setters
        void setName(string name);
        void setID(int id);
        void setTaskAtIndex(string taskName, int index);
        void setInitPositionAtIndex(int value, int index);
        void setTaskPositionAtIndex(int x, int y, int index);

        // sorting methods
        void sortByAscending();
        void sortByDescending();

        // display method
        // void displayDrone();

        // NEW (pg 6) VIRTUAL METHOD (replace void displayDrone from midterm because override will kill it, rip)
        virtual void displayDrone();        // for polymorphism D:

        // operator overloads
        void operator<<(Drone& d2); //copy all attributes of d2 into this object
        void operator-(Drone& d2);  //swap task and task position between objects (init position is excluded)
};
#endif
