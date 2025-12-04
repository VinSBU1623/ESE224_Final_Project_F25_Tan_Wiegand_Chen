#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath> // For position calculation
#include <algorithm> // For swap
#include <cstdlib> // For rand
#include <ctime>   // For time

using namespace std;

// Page 5: "template <typename T>" 
template <typename T>
class DroneManager {
private:
    // Page 5: "std::vector<T*> objects;" 
    vector<T*> objects; 

public:
    // Page 5: "addObject(T* obj): Adds an object to the collection." [cite: 162]
    void addObject(T* obj) {
        objects.push_back(obj);
    }

    // Page 5: "getObject(int index): Returns an object at a specific index." [cite: 163]
    T* getObject(int index) {
        if (index >= 0 && index < objects.size()) {
            return objects[index];
        }
        return nullptr;
    }

    // Page 5: "sortDronesByName(): Sorts drones by name." [cite: 164]
    // Implementation: using manual Bubble Sort to match your coding style
    void sortDronesByName() {
        if (objects.empty()) return;
        for (size_t i = 0; i < objects.size() - 1; i++) {
            for (size_t j = 0; j < objects.size() - i - 1; j++) {
                // Assumes T has getName() method
                if (objects[j]->getName() > objects[j + 1]->getName()) {
                    swap(objects[j], objects[j + 1]);
                }
            }
        }
    }

    // Page 5: "sortDronesByID(): Sorts drones by ID." [cite: 165]
    void sortDronesByID() {
        if (objects.empty()) return;
        for (size_t i = 0; i < objects.size() - 1; i++) {
            for (size_t j = 0; j < objects.size() - i - 1; j++) {
                // Assumes T has getID() method
                if (objects[j]->getID() > objects[j + 1]->getID()) {
                    swap(objects[j], objects[j + 1]);
                }
            }
        }
    }

    // Page 5: "sortDronesByPosition(): Sorts drones by position." [cite: 166]
    void sortDronesByPosition() {
        if (objects.empty()) return;
        for (size_t i = 0; i < objects.size() - 1; i++) {
            for (size_t j = 0; j < objects.size() - i - 1; j++) {
                // Calculate distances
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

    // Page 5: "randomizeDroneOrder(): Randomizes the order of drones." [cite: 167]
    void randomizeDroneOrder() {
        // Simple manual shuffle
        for (size_t i = 0; i < objects.size(); i++) {
            int randIndex = rand() % objects.size();
            swap(objects[i], objects[randIndex]);
        }
    }

    // Page 5: "searchDroneByName(const std::string& name)" [cite: 168]
    T* searchDroneByName(const string& name) {
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i]->getName() == name) {
                return objects[i];
            }
        }
        return nullptr;
    }

    // Page 5: "searchDroneByID(int id)" [cite: 169]
    T* searchDroneByID(int id) {
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i]->getID() == id) {
                return objects[i];
            }
        }
        return nullptr;
    }

    // Page 5: "printAllDroneNames()" [cite: 170]
    void printAllDroneNames() {
        cout << "--- Drone List (Manager) ---" << endl;
        for (size_t i = 0; i < objects.size(); i++) {
            cout << objects[i]->getName() << " (ID: " << objects[i]->getID() << ")" << endl;
        }
    }
    
    // Helper to get size (not strictly in manual but needed for loops in main)
    int getSize() {
        return objects.size();
    }
};

#endif