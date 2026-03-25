#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include "Weapon.h"
#include "Enemy.h"
#include "Hero.h"
#include "LinkedList.h"

using namespace std;

void introduction() {
    cout << "==========================================\n";
    cout << "Welcome to the Castle Adventure!\n";
    cout << "Navigate the rooms, collect items, and survive.\n";
    cout << "==========================================\n\n";
}

int main() {
    // 1. Initialize the Hero
    Hero player("Arthur", "A brave knight", 100, {"Shield"});

    LinkedList castleRooms;
    ifstream file("rooms.csv");
    string line;

    // 2. Loading data from CSV
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string name, description, actionsStr, item;

            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, actionsStr, ',');
            getline(ss, item);

            vector<string> actions;
            stringstream actionStream(actionsStr);
            string action;
            while (getline(actionStream, action, ';')) {
                actions.push_back(action);
            }

            Room newRoom(name, description, actions, item);
            
            // Example: Add a specific enemy to the Dungeon
            if (name == "Dungeon") {
                auto skeleton = make_shared<Enemy>("Skeleton", "A rattling bag of bones.", 30, vector<string>{"Bone Toss"}, 4);
                newRoom.setEnemy(skeleton);
            }

            castleRooms.addRoom(newRoom);
        }
        file.close();
    } else {
        cout << "Error: Could not open rooms.csv" << endl;
        return 1;
    }

    introduction();

    // 3. Game Loop
    auto current = castleRooms.getHead();
    while (current != nullptr && player.isAlive()) {
        Room& room = current->room;
        
        // Show status and room info
        player.displayStatus();
        cout << room.toString();

        // Check for enemy and trigger a simple "encounter"
        if (room.hasEnemy()) {
            cout << "\n[!] A " << room.getEnemy()->getName() << " blocks the way!" << endl;
            // For now, the enemy deals 10 damage automatically to show mechanics
            player.takeDamage(10);
            if (!player.isAlive()) break;
        }

        // Display Menu
        const auto& roomActions = room.getActions();
        for (size_t i = 0; i < roomActions.size(); ++i) {
            cout << i + 1 << ". " << roomActions[i] << endl;
        }

        int choice;
        cout << "\nWhat is your choice? ";
        cin >> choice;

        if (choice < 1 || choice > (int)roomActions.size()) {
            cout << "Invalid choice. Try again.\n";
            continue; 
        }

        string selectedAction = roomActions[choice - 1];
        cout << "\nYou: " << selectedAction << endl;

        // 4. Logic for specific actions
        if (selectedAction == "Leave the room") {
            // Check if player has the specific item needed or if the enemy is dead
            if (room.hasEnemy() && room.getEnemy()->isAlive()) {
                cout << "The enemy is too dangerous to slip past!\n";
            } else {
                cout << "You advance to the next room...\n";
                current = current->next;
            }
        } 
        else if (selectedAction.find("Search") != string::npos || 
                 selectedAction.find("Inspect") != string::npos ||
                 selectedAction.find("Observe") != string::npos) {
            
            if (!room.getItem().empty()) {
                player.addItem(room.getItem());
                room.setItem(""); // Item is now in inventory, remove from room
            } else {
                cout << "You don't find anything useful here.\n";
            }
        }
        else if (selectedAction == "Scream for help") {
            cout << "Your echoes fade into the darkness. No one answers.\n";
        }
    }

    // 5. End Game Result
    if (!player.isAlive()) {
        cout << "\nGAME OVER: " << player.getName() << " has perished in the castle.\n";
    } else {
        cout << "\nVICTORY: You have successfully navigated the castle!\n";
    }

    return 0;
}