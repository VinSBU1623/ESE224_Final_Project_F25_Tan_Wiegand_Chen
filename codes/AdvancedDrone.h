#ifndef ADVANCEDDRONE_H
#define ADVANCEDDRONE_H

#include "Drone.h"
#include <iostream>
using namespace std;

class AdvancedDrone : public Drone { //Advanced drone inherits drone
private:
    float batteryLevel;
    bool autopilotEnabled;

public:
    //Constructor
    AdvancedDrone() : Drone(), batteryLevel(100.0), autopilotEnabled(false) {}

    void enableAutopilot() { //Enable
        autopilotEnabled = true;
        cout << "Autopilot engaged." << endl;
    }

    void updateBattery(float delta) { //Battery - delta
        batteryLevel -= delta;
        if (batteryLevel < 0) {
            batteryLevel = 0;
        }
    }

    void displayDrone() override {
        Drone::displayDrone(); 
        cout << " [Advanced Features] Battery: " << batteryLevel << "% | Autopilot: " << (autopilotEnabled ? "ON" : "OFF") << endl;
    }

    void autoReorderTasks() { //reorder if below 30% bat
        if (batteryLevel < 30.0) {
            cout << "ALARM: Low Battery (" << batteryLevel << "%)! Reversing task order..." << endl;
            
            string* tasks = this->getTasks();
            int (*positions)[2] = this->getTaskPositions();
            int start = 0;
            int end = 4;
            
            while (start < end) { //swap swap
                string tempName = tasks[start];
                tasks[start] = tasks[end];
                tasks[end] = tempName;   

                int tempX = positions[start][0];
                int tempY = positions[start][1];
                
                positions[start][0] = positions[end][0];
                positions[start][1] = positions[end][1];
                
                positions[end][0] = tempX;
                positions[end][1] = tempY;
                
                // Move indices
                start++;
                end--;
            }
            
            cout << "Route successfully reversed to prioritize return trip." << endl;
        } else {
            cout << "Battery level normal. No reorder needed." << endl;
        }
    }
};

#endif