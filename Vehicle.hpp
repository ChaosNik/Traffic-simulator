#pragma once

#include "Graph.hpp"

class Vehicle
{
public:
    Vehicle(int id, Graph* map, Node* current, Node* goal, int preferredSpeed):
        id(id), map(map), current(current), goal(goal),
        preferredSpeed(preferredSpeed), coveredPath(0) {}
    int getId() {return id;}
    int getPrefferedSpeed() {return preferredSpeed;}
    int getTimeAtCurrent() {return preferredSpeed;}
    Node* getCurrent() {return current;}
    Node* getGoal() {return goal;}
    void tick(int step);

private:
    int id;
    Graph* map;
    int preferredSpeed;
    int coveredPath;
    Node* current;
    Node* goal;
};