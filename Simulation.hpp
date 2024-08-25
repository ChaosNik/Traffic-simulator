#pragma once

#include "Graph.hpp"
#include "Vehicle.hpp"

// Class for traffic simulation
class Simulation
{
public:
    Simulation(Graph* graph, int duration, std::list<Vehicle*> vehicles = {}, int step = 1):
        graph(graph), duration(duration), vehicles(vehicles), step(step), i(0) {}
    void addVehicle(Vehicle* vehicle) {vehicles.push_back(vehicle);}
    void run();
    void runStepByStep();
    void runOneStep();
    bool isOver() {return i == duration;};
    void printState(Vehicle* v);
    int getDurration(Node* from, Node* to);

private:
    void printVehicles();
    int step;
    int i;
    Graph* graph;
    int duration;
    std::list<Vehicle*> vehicles;
};