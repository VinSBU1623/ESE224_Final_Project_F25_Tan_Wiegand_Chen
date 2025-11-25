// main.cpp
#include "Drone.h"
#include "Depot.h"
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
    { //reads 10 drones
        if (i >= 10) {
            break; //only read first 10 drones
        }

        // Construct a temporary Drone, populate it, then add to depot
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

    int choice = 0;

    int id, id1, id2, idx, idx2, taskpos[2], index1, index2;

    
    i = 0;

    while (choice != 16){
        //user inferface menu options
        cout << "Menu Options:" << endl;
        cout << "1. Sort Drones By Name\n2. Sort Drones By ID\n3. Sort Drones By Position\n4. Randomize Drone Order\n5. Add Drone\n6. Retrieve a drone\n7. Search Drone By name\n8. Search Drone by ID\n9. Write Depot to file\n10. Swap Drone Data\n11. Insert Drone Task\n12. Copy-Paste Drone\n13. Display All Drones' names\n14. Sort Drone Data Ascending\n15. Sort Drone Data Descending\n16. Exit" << endl;
        cout << "Enter a number value choice: ";
        cin >> choice;
        if (cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 20; //Any non int input can be handled as an out of bounds
        }
        switch (choice){
            case 1: // Sort Drones By Name
                depot.sortByName();
                cout << "Drones sorted by name." << endl;
                depot.printAllNames();
                break;
            case 2: // Sort Drones By ID
                depot.sortByID();
                cout << "Drones sorted by ID." << endl;
                depot.printAllNames();
                break;
            case 3: // Sort Drones By Position
                depot.sortByPosition();
                cout << "Drones sorted by position." << endl;
                depot.printAllNames();
                break;
            case 4: // Randomize Drone Order
                depot.randomizeOrder();
                cout << "Drones order randomized." << endl;
                depot.printAllNames();
                break;
            case 5:{ // Add Drone
                Drone newDrone;
                int id, x, y;
                string name;
                cout << "New Name: ";
                cin >> name;
                cout << "New ID: ";
                cin >> id;
                cout << "Enter initial position in format x y: ";
                cin >> x >> y;

                for (int index = 0; index < MAX_TASKS; ++index) { //we don't want index to be out of bounds
                    cout << "Enter task " << index + 1 << " name: ";
                    cin >> tasks[index];
                    cout << "Enter task " << index + 1 << " position (x y): ";
                    cin >> task_positions[index][0] >> task_positions[index][1];
                    newDrone.setTaskAtIndex(tasks[index], index);
                    newDrone.setTaskPositionAtIndex(task_positions[index][0], task_positions[index][1], index);
                }

                newDrone.setName(name);
                newDrone.setID(id);
                newDrone.setInitPositionAtIndex(x, 0);
                newDrone.setInitPositionAtIndex(y, 1);
                depot.addDrone(newDrone);

                cout << "Drone added!" << endl;
                }break;
            case 6: // Retrieve a drone
                cout << "Enter index of drone to retrieve: ";
                cin >> idx;
                depot.getDrone(idx).displayDrone();
                break;
            case 7: { // Search Drone By name
                cout << "Enter Drone name to search: ";
                cin >> name;
                // binary search requires the vector to be sorted by name first
                depot.sortByName();

                int foundIndex = depot.searchDroneByName(name);
                if (foundIndex >= 0) {
                    cout << "Drone \"" << name << "\" found." << endl;
                } else {
                    cout << "Drone \"" << name << "\" not found." << endl;
                }
            } break;
            case 8: { // Search Drone by ID
                cout << "Enter Drone ID to search: ";
                cin >> id;
                depot.sortByID();

                int foundIndexID = depot.searchDroneByID(id);
                if (foundIndexID >= 0) {
                    cout << "Drone with ID " << id << " found." << endl;
                } else {
                    cout << "Drone with ID " << id << " not found." << endl;
                }
            } break;
            case 9: // Write Depot to file
                depot.writeDepotToFile();
                cout << "Depot written to file." << endl;
                break;
            case 10: // Swap Drone Data
                cout << "which two drones do you want to swap?\n" << endl;
                cout << "Enter index of first drone: ";
                cin >> index1;
                cout << "Enter index of second drone: ";
                cin >> index2;
                depot.swapDroneData(index1, index2);
                break;
            case 11: // Insert Drone Task
                cout << "Enter drone index: ";
                cin >> idx;
                cout << "Enter task index: ";
                cin >> idx2;
                cout << "Enter task name: ";
                cin >> name;
                cout << "Enter task position (x y): ";
                cin >> taskpos[0] >> taskpos[1];
                depot.insertDroneTask(idx, idx2, name, taskpos);
                break;
            case 12: // Copy-Paste Drone
                cout << "which drone do you want to copy-paste?\n" << endl;
                cout << "Enter index of source drone: ";
                cin >> idx;
                cout << "Enter index of destination drone: ";
                cin >> idx2;
                depot.copyDrone(idx, idx2);
                break;
            case 13: // Display All Drones' names
                depot.printAllNames();
                break;
            case 14: // Sort Drone Data Ascending
                cout << "Enter index of drone to sort: ";
                cin >> idx;
                depot.sortDroneDataAscending(idx);
                depot.getDrone(idx).displayDrone();  // Show the results
                break;
            case 15: // Sort Drone Data Descending
                cout << "Enter index of drone to sort: ";
                cin >> idx;
                depot.sortDroneDataDescending(idx);
                depot.getDrone(idx).displayDrone();  // Show the results
                break;
            case 16: // Exit
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
    infile.close();

    return 0;
}

/*
g++ main.cpp Drone.cpp Depot.cpp -o a 

A real drone control system must be user-friendly for operators. In this project, you will design a
menu-driven interface that mimics the role of a dispatcher, who uses software to issue commands
to drones. Through this interface, you will demonstrate the ability to connect all the system
components—Drone, Depot, and operations—into a coherent application.
Input:
- Your main program should read exactly 10 drones from Drones.txt(for additional drones
in the input file, simply ignore them), create one depot object to hold them, and store
each information into its corresponding place.
- Format: name, ID, init_position, 5 task names and positions, blank lines separate each
drone
*/