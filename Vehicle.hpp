#pragma once

#include "Graph.hpp"

// Class for vehicles in the simulation
class Vehicle
{
public:
    Vehicle(int id, Graph* map, Node* current, Node* goal, int preferredSpeed):
        id(id), map(map), current(current), goal(goal),
        preferredSpeed(preferredSpeed), coveredPath(0) {}
    int getId() {return id;}
    int getPrefferedSpeed() {return preferredSpeed;}
    Node* getCurrent() {return current;}
    Node* getGoal() {return goal;}
    void tick(int step, std::list<Vehicle*> vehicles);
    static int numberOfVehiclesInNode(Node* node, std::list<Vehicle*> vehicles);

private:
    int id;
    Graph* map;
    int preferredSpeed;
    int coveredPath;
    Node* current;
    Node* goal;
};