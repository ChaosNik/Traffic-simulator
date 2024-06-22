#include "Simulation.hpp"
#include <iostream>

void Simulation::run()
{
    for(; i < duration; i += step)
        runOneStep();
}

void Simulation::runStepByStep()
{
    for(; i < duration; i += step)
    {
        runOneStep();

        std::string line;
        std::getline(std::cin, line);
    }
}

void Simulation::runOneStep()
{
    for(NodeLocation* loc : graph->getLocations())
    {
        std::cout << loc->getName() << ": ";
        for(Vehicle* v : vehicles)
            if(v->getCurrent()->getId() == loc->getId())
                std::cout << v->getId();
        std::cout << std::endl;
    }
    for(NodePath* path : graph->getPaths())
    {
        std::cout << path->getId() << ": ";
        for(Vehicle* v : vehicles)
            if(v->getCurrent()->getId() == path->getId())
                std::cout << v->getId();
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for(NodeIntersection* inter : graph->getIntersections())
    {
        std::cout << inter->getId() << ":" << std::endl;
        for(NodePath* path : inter->getPaths())
        {
            std::cout << "\t" << path->getId() << ": ";
            for(Vehicle* v : vehicles)
                if(v->getCurrent()->getId() == path->getId())
                    std::cout << v->getId();
            std::cout << std::endl;
        }
    }

    for(Vehicle* v : vehicles)
        v->tick(step);
}

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

int Simulation::getDurration(Node* from, Node* to)
{
    return graph->getDurration(from, to);
}
