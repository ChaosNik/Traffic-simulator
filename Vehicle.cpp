#include "Vehicle.hpp"
#include <iostream>

// Method that simulates one step of vehicle movement
void Vehicle::tick(int step, std::list<Vehicle*> vehicles)
{
    if(current->getId() == goal->getId())
        return;

    Node* nextNode = map->bestNextNode(current, goal);
    int numberOfVehiclesInCurrentNode = 0;
    int numberOfVehiclesInNextNode = 0;
    for(Vehicle* x : vehicles)
    {
        if(current->getId() == x->current->getId())
            numberOfVehiclesInCurrentNode++;
        if(nextNode->getId() == x->current->getId())
            numberOfVehiclesInNextNode++;
    }

    int currentSpeed = current->getMaxSpeed() < preferredSpeed ? current->getMaxSpeed() : preferredSpeed;
    coveredPath += currentSpeed * step * current->getSlowdownFactor(numberOfVehiclesInCurrentNode);
    if(coveredPath > current->getLength() && numberOfVehiclesInNextNode < nextNode->getCapacity())
    { 
        current = nextNode;
        coveredPath = 0;
    }
}

