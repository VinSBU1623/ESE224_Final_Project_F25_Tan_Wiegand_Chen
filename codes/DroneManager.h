#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;


template <typename T>
class DroneManager {
private:
    vector<T*> objects; 

public:
    void addObject(T* obj) { //Add object to vect
        objects.push_back(obj);
    }

    T* getObject(int index) { //Get object from index
        if (index >= 0 && index < objects.size()) {
            return objects[index];
        }
        return nullptr;
    }

    void sortDronesByName() { //Bubble sort drones by name
        if (objects.empty()) return;
        for (size_t i = 0; i < objects.size() - 1; i++) {
            for (size_t j = 0; j < objects.size() - i - 1; j++) {
                if (objects[j]->getName() > objects[j + 1]->getName()) {
                    swap(objects[j], objects[j + 1]);
                }
            }
        }
    }

    void sortDronesByID() { //Bubble sort drones by id (literally same as last j with ids lol)
        if (objects.empty()) return;
        for (size_t i = 0; i < objects.size() - 1; i++) {
            for (size_t j = 0; j < objects.size() - i - 1; j++) {
                if (objects[j]->getID() > objects[j + 1]->getID()) {
                    swap(objects[j], objects[j + 1]);
                }
            }
        }
    }

    void sortDronesByPosition() { //Sort by pos
        if (objects.empty()) return;
        for (size_t i = 0; i < objects.size() - 1; i++) {
            for (size_t j = 0; j < objects.size() - i - 1; j++) { //Distance must be manually calced (calc is short for calculator btw) (elite ball knowledge)
                int x1 = objects[j]->getInitPosition()[0];
                int y1 = objects[j]->getInitPosition()[1];
                double dist1 = sqrt(x1*x1 + y1*y1);

                int x2 = objects[j+1]->getInitPosition()[0];
                int y2 = objects[j+1]->getInitPosition()[1];
                double dist2 = sqrt(x2*x2 + y2*y2);

                if (dist1 > dist2) {
                    swap(objects[j], objects[j + 1]);
                }
            }
        }
    }

    void randomizeDroneOrder() { //Randomize
        for (size_t i = 0; i < objects.size(); i++) {
            int randIndex = rand() % objects.size();
            swap(objects[i], objects[randIndex]);
        }
    }

    T* searchDroneByName(const string& name) { //Linear search by name
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i]->getName() == name) {
                return objects[i];
            }
        }
        return nullptr;
    }

    T* searchDroneByID(int id) { //Linear search by id
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i]->getID() == id) {
                return objects[i];
            }
        }
        return nullptr;
    }

    void printAllDroneNames() { //Print drone names
        cout << "--- Drone List (Manager) ---" << endl;
        for (size_t i = 0; i < objects.size(); i++) {
            cout << objects[i]->getName() << " (ID: " << objects[i]->getID() << ")" << endl;
        }
    }
    
    int getSize() { //Simple helper
        return objects.size();
    }
};

#endif