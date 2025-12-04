#include "Drone.h"
#include "Depot.h"
#include "AdvancedDrone.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define MAX_TASKS 5

int main () {
    ifstream infile("Drone.txt");
    if(!infile){
        cout << "Error opening files!" << endl;
        return 1;
    }

    Depot depot;
    string name;
    int ID;
    int init_position[2];
    string tasks[5];
    int task_positions[5][2];

    int i = 0;
  
    while(infile >> name >> ID >> init_position[0] >> init_position[1] >> 
          tasks[0] >> task_positions[0][0] >> task_positions[0][1] >>
          tasks[1] >> task_positions[1][0] >> task_positions[1][1] >>
          tasks[2] >> task_positions[2][0] >> task_positions[2][1] >>
          tasks[3] >> task_positions[3][0] >> task_positions[3][1] >>
          tasks[4] >> task_positions[4][0] >> task_positions[4][1] >> ws)
    { 
        if (i >= 10) break; 

        Drone d;
        d.setName(name);
        d.setID(ID);
        d.setInitPositionAtIndex(init_position[0], 0);
        d.setInitPositionAtIndex(init_position[1], 1);
        for (int j = 0; j < 5; j++) {
            d.setTaskAtIndex(tasks[j], j);
            d.setTaskPositionAtIndex(task_positions[j][0], task_positions[j][1], j);
        }

        depot.addDrone(d);
        i++;
    }
    infile.close();

    
    for(int k=0; k<i; k++) {
        Drone* dPtr = depot.getDronePtr(k);
        if(dPtr != nullptr) {
            depot.addDroneToLinkedList(dPtr);
            depot.insertToTree(dPtr);
        }
    }

    int choice = 0;
    int inputID, x, y;
    string inputName;

    while (true){
        cout << "\n--- SkyRoute-II Drone Management Menu ---\n";
        cout << "1. Add Drone (to Linked List)\n2. Remove Drone (from Linked List)\n3. Show Drones (Vector)\n";
        cout << "4. Use Linked List (Display)\n5. Use Queue (Demo)\n6. Use Stack (Demo)\n7. Spatial Management (Search)\n";
        cout << "8. Sort Drones by Name\n9. Sort Drones by ID\n";
        cout << "10. Sort Drones by Position\n11. Randomize Drone Order\n";
        cout << "12. Print All Drone Names\n13. Search Drone by Name\n";
        cout << "14. Search Drone by ID\n15. Quit\n";
        cout << "16. TEST POLYMORPHISM (Rubric Req)\n"; 
        
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1; 
        }

        if (choice == 15) {
            cout << "Exiting program." << endl;
            break;
        }

        switch (choice){
            case 1: // Add Drone
                cout << "Enter existing ID from Depot to add/link: ";
                cin >> inputID;
                depot.sortByID(); // Ensure sorted for binary search
                if(depot.searchDroneByID(inputID) != -1) {
                    int idx = depot.searchDroneByID(inputID);
                    depot.addDroneToLinkedList(depot.getDronePtr(idx));
                    cout << "Drone " << inputID << " added to Linked List." << endl;
                } else {
                    cout << "ID not found in basic depot storage." << endl;
                }
                break;

            case 2: // Remove Drone
                cout << "Enter ID to remove from Linked List: ";
                cin >> inputID;
                depot.removeDroneFromLinkedList(inputID);
                cout << "Operation complete." << endl;
                break;

            case 3: // Show Drones
                for(int k=0; k<i; k++) {
                    depot.getDrone(k).displayDrone();
                    cout << "----------------" << endl;
                }
                break;

            case 4: // Use Linked List
                depot.printLinkedList();
                break;

            case 5: // Use Queue
                cout << "Enqueuing first 3 drones from vector..." << endl;
                if (depot.getDronePtr(0)) depot.enqueueDrone(depot.getDronePtr(0));
                if (depot.getDronePtr(1)) depot.enqueueDrone(depot.getDronePtr(1));
                if (depot.getDronePtr(2)) depot.enqueueDrone(depot.getDronePtr(2));
                
                cout << "Dequeuing one drone: ";
                if(Drone* d = depot.dequeueDrone()) {
                    cout << d->getName() << endl;
                } else {
                    cout << "Queue empty." << endl;
                }
                break;

            case 6: // Use Stack
                cout << "Pushing first 3 drones from vector..." << endl;
                if (depot.getDronePtr(0)) depot.pushDrone(depot.getDronePtr(0));
                if (depot.getDronePtr(1)) depot.pushDrone(depot.getDronePtr(1));
                if (depot.getDronePtr(2)) depot.pushDrone(depot.getDronePtr(2));
                
                cout << "Popping one drone: ";
                if(Drone* d = depot.popDrone()) {
                    cout << d->getName() << endl;
                } else {
                    cout << "Stack empty." << endl;
                }
                break;

            case 7: // Spatial Management
                cout << "Enter X Y coordinates to search: ";
                cin >> x >> y;
                if(Drone* d = depot.searchInTree(x, y)) {
                    cout << "Found in Tree: " << d->getName() << " at (" << x << "," << y << ")" << endl;
                } else {
                    cout << "No drone found at exact location." << endl;
                }
                break;

            case 8:         // Sorting by name
                depot.sortByName();
                cout << "Sorted by Name." << endl;
                break;

            case 9:     // Sorting by ID
                depot.sortByID();
                cout << "Sorted by ID." << endl;
                break;

            case 10:    // Sorting by pos.
                depot.sortByPosition();
                cout << "Sorted by Position." << endl;
                break;

            case 11:    // Randomizer
                depot.randomizeOrder();
                cout << "Order randomized." << endl;
                break;

            case 12:    // Print Names
                depot.printAllNames();
                break;

            case 13:    // Binary Search
                cout << "Enter name: ";
                cin >> inputName;
                depot.sortByName(); // Required for binary search
                if(depot.searchDroneByName(inputName) != -1) {
                    cout << "Found." << endl;
                }
                else {
                    cout << "Not found." << endl;
                }
                break;

            case 14: 
                cout << "Enter ID: ";
                cin >> inputID;
                depot.sortByID(); // Required for binary search
                if(depot.searchDroneByID(inputID) != -1){
                    cout << "Found." << endl;
                }
                else {
                    cout << "Not found." << endl;
                }
                break;

            case 16: {  // AdvancedDrone implementation (this is extra but we need to show polymorph.)
                AdvancedDrone ad;
                int enableAuto;
                cout << "Enable Autopilot? YES(1) or NO(0)" << endl;
                cin >> enableAuto;
                if(enableAuto == 1){
                    ad.enableAutopilot();
                }
                cout << "Creating an AdvancedDrone for testing..." << endl;
                ad.setName("Advanced-X1");
                ad.setTaskAtIndex("Task_A", 0); 
                ad.setTaskAtIndex("Task_B", 1);
                ad.setTaskAtIndex("Task_C", 2);
                ad.setTaskAtIndex("Task_D", 3);
                ad.setTaskAtIndex("Task_E", 4); 
                
                // Drain battery
                ad.updateBattery(80.0);
                
                ad.autoReorderTasks();
                
                ad.displayDrone(); 

                break;
            }

            default:
                cout << "Invalid choice." << endl;
        }
    }
    return 0;
}

/*

g++ main.cpp Drone.cpp Depot.cpp SpatialTree.cpp -o a

*/
