#include "Room.h"
#include "Enemy.h" // Full definition needed here to call Enemy methods
#include <iostream>

// Constructor - Initialize roomEnemy to nullptr by default
Room::Room(string name, string description, vector<string> actions, string item)
    : name(name), description(description), actions(actions), item(item), roomEnemy(nullptr) {}

// Setters
void Room::setName(const string& newName) { name = newName; }
void Room::setDescription(const string& newDescription) { description = newDescription; }
void Room::setActions(const vector<string>& newActions) { actions = newActions; }
void Room::setItem(const string& newItem) { item = newItem; }

// New Setter for Enemy
void Room::setEnemy(shared_ptr<Enemy> enemy) { 
    roomEnemy = enemy; 
}

// Getters
string Room::getName() const { return name; }
string Room::getDescription() const { return description; }
vector<string> Room::getActions() const { return actions; }
string Room::getItem() const { return item; }

// New Getters for Enemy
shared_ptr<Enemy> Room::getEnemy() const { 
    return roomEnemy; 
}

bool Room::hasEnemy() const { 
    // Returns true only if the pointer is not null AND the enemy is alive
    return (roomEnemy != nullptr && roomEnemy->isAlive()); 
}

// Fixed toString method
string Room::toString() const {
    string info = "Room: " + name + "\nDescription: " + description + "\nActions:\n";
    
    for (const auto& action : actions) {
        info += "- " + action + "\n";
    }
    
    info += "Item present: " + (item.empty() ? "None" : item) + "\n";

    // Add dynamic enemy info to the string
    if (hasEnemy()) {
        info += "!!! ENEMY ALERT: " + roomEnemy->getName() + " is here! !!!\n";
    }

    return info;
}