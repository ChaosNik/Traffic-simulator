#include "Vehicle.hpp"
#include <iostream>

// Method that simulates one step of vehicle movement
void Vehicle::tick(int step)
{
    if(current->getId() == goal->getId())
        return;

    int maxSpeed = current->getMaxSpeed();
    int currentSpeed = maxSpeed < preferredSpeed ? maxSpeed : preferredSpeed;
    coveredPath += currentSpeed * step;
    if(coveredPath > current->getLength())
    {
        current = map->bestNextNode(current, goal);
        coveredPath = 0;
    }
    // std::cout << current->getId() << " " << coveredPath << std::endl;
}
