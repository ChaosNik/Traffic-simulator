#include "Simulation.hpp"
#include <iostream>

// Method to run the simulation until completion
void Simulation::run()
{
    for(; i < duration; i += step)
    {
        std::cout << "Time: " << i << std::endl << std::endl;
        runOneStep();
        bool finished = true;
        for(Vehicle* v : vehicles)
            if(v->getGoal()->getId() != v->getCurrent()->getId())
                finished = false;
        if(finished)
            i = duration;
    }
    runOneStep();
    std::cout << "The simulation has finished!!!" << std::endl;
}

// Method to run the simulation step by step
void Simulation::runStepByStep()
{
    for(; i < duration; i += step)
    {
        std::cout << "Time: " << i << std::endl << std::endl;
        runOneStep();
        bool finished = true;
        for(Vehicle* v : vehicles)
            if(v->getGoal()->getId() != v->getCurrent()->getId())
                finished = false;
        if(finished)
            i = duration;
        
        std::string line;
        std::getline(std::cin, line);
    }
    runOneStep();

    std::cout << "The simulation has finished!!!" << std::endl;
}

// Method to run one step of the simulation
void Simulation::runOneStep()
{
    for(Vehicle* v : vehicles)
    {
        if(v->getCurrent()->getId() == v->getGoal()->getId())
            std::cout << "Vehicle " << v->getId() << " has finished and is in it's goal "
                << v->getGoal()->getId() << std::endl;
        else
            std::cout << "Vehicle " << v->getId() << " whose goal is " << v->getGoal()->getId()
                << " is in " << v->getCurrent()->getId() << std::endl;
    }
    std::cout << std::endl;

    for(Vehicle* v : vehicles)
        v->tick(step, vehicles);
}

// Method to print the current state of a vehicle
void Simulation::printState(Vehicle* v)
{
    for(NodeLocation* loc : graph->getLocations())
    {
        if(v->getCurrent()->getId() == loc->getId())
        {
            std::cout << "Vehicle " << v->getId() <<
                "is in location " << loc->getName() << std::endl;
            return;
        }
    }
    for(NodePath* path : graph->getPaths())
    {
        std::cout << path->getId() << ": ";
        if(v->getCurrent()->getId() == path->getId())
            std::cout << v->getId();
        {
            std::cout << "Vehicle " << v->getId() <<
                "is on path " << path->getId() << std::endl;
            return;
        }
    }
    std::cout << std::endl;
    for(NodeIntersection* inter : graph->getIntersections())
    {
        std::cout << inter->getId() << ":" << std::endl;
        for(NodePath* path : inter->getPaths())
        {
            if(v->getCurrent()->getId() == path->getId())
            {
                std::cout << "Vehicle " << v->getId() <<
                    "is in intersection " << inter->getId() << std::endl;
                return;
            }
        }
    }
}

// Method to get the duration of the path between two nodes
int Simulation::getDurration(Node* from, Node* to)
{
    return graph->getDurration(from, to);
}
