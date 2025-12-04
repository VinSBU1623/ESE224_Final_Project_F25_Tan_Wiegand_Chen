#ifndef DRONE_H
#define DRONE_H
#include <string>
using namespace std;

class Drone { 
    private:
        string name;    
        int ID;
        string task[5];             
        int init_position[2];       
        int task_positions[5][2];   

        Drone* nextDrone;

    public:
        // constructor
        Drone();    

        // getters
        string getName();
        int getID();
        string* getTasks();         
        int* getInitPosition();     
        int (*getTaskPositions())[2]; 


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

        
        virtual void displayDrone();

        // operator overloads
        void operator<<(Drone& d2); 
        void operator-(Drone& d2);
};
#endif
