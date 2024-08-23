#include "Vehicle.hpp"
#include <iostream>

// Method that simulates one step of vehicle movement
void Vehicle::tick(int step, std::list<Vehicle*> vehicles)
{
    if(current->getId() == goal->getId())
        return;

    Node* nextNode = map->bestNextNode(current, goal);
    int numberOfVehiclesInNode = 0;
    for(Vehicle* x : vehicles)
        if(nextNode->getId() == x->current->getId())
            numberOfVehiclesInNode++;

    int currentSpeed = current->getMaxSpeed() < preferredSpeed ? current->getMaxSpeed() : preferredSpeed;
    coveredPath += currentSpeed * step * current->getSlowdownFactor(numberOfVehiclesInNode);
    if(coveredPath > current->getLength())
    { 
        if(numberOfVehiclesInNode < nextNode->getCapacity())
        {
            current = map->bestNextNode(current, goal);
            coveredPath = 0;
        }
    }
}

//// popunjen kapacitet puteva i raskrsnica
// proracun najboljeg puta u zavisnosti od vremena ili udaljenosti
//// faktor usporenja, lambda funkcija za svaki put
// nastimati da vozilo promijeni putanju
