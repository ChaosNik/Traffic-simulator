#include "Vehicle.hpp"
#include <iostream>

// Method that simulates one step of vehicle movement
void Vehicle::tick(int step, std::list<Vehicle*> vehicles)
{
    if(current->getId() == goal->getId())
        return;

    Node* nextNode = map->bestNextNode(current, goal);
    int currentSpeed = current->getMaxSpeed() < preferredSpeed ? current->getMaxSpeed() : preferredSpeed;
    coveredPath += currentSpeed * step * current->getSlowdownFactor(numberOfVehiclesInNode(current, vehicles));
    if(coveredPath > current->getLength() && numberOfVehiclesInNode(nextNode, vehicles) < nextNode->getCapacity())
    { 
        current = nextNode;
        coveredPath = 0;
    }
}

int Vehicle::numberOfVehiclesInNode(Node *node, std::list<Vehicle*> vehicles)
{
    int numberOfVehiclesInNode = 0;
    for(Vehicle* x : vehicles)
    {
        if(node->getId() == x->current->getId())
            numberOfVehiclesInNode++;
    }
    return numberOfVehiclesInNode;
}
