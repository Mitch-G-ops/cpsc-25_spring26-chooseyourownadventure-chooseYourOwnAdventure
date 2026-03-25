#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <memory>

// Remove #include "Enemy.h" here to prevent circular dependency
// Use a Forward Declaration instead:
class Enemy; 

using namespace std;

class Room {
private:
    string name;
    string description;
    vector<string> actions;
    string item;
    shared_ptr<Enemy> roomEnemy; // Smart pointers work with forward declarations

public:
    Room(string name, string description, vector<string> actions, string item);
    
    void setName(const string& newName);
    void setDescription(const string& newDescription);
    void setActions(const vector<string>& newActions);
    void setItem(const string& newItem);
    void setEnemy(shared_ptr<Enemy> enemy);

    string getName() const;
    string getDescription() const;
    vector<string> getActions() const;
    string getItem() const;
    string toString() const;
    
    shared_ptr<Enemy> getEnemy() const;
    bool hasEnemy() const;
};

#endif