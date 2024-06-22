#include "Graph.hpp"
#include <iostream>

int Graph::calculateLocation(NodeLocation* from, NodeLocation* to,
    std::set<Node*> visited, Node** next)
{
    if(from->getId() == to->getId())
        return 0;

    if(visited.count(from))
        return 10000;

    visited.insert(from);

    int minLength = 10000;
    for(NodePath* x : paths)
    {
        if(!visited.count(x) && // If not already visited
            x->getInNode()->getId() == from->getId()) // If path connects to location
        {
            Node* tempNext;
            int length = calculatePath(x, to, visited, &tempNext);
            if(length < minLength)
            {
                minLength = length;
                *next = x;
            }
        }
    }
    return minLength;
}

int Graph::calculatePath(NodePath* from, NodeLocation* to,
    std::set<Node *> visited, Node** next)
{
    if(visited.count(from))
        return 10000;

    visited.insert(from);

    int minLength = 10000;
    for(NodeLocation* x : locations)
    {
        if(from->getOutNode()->getId() == x->getId()) // If path connects to location
        {
            Node* tempNext;
            int length = from->getLength() + calculateLocation(x, to, visited, &tempNext);
            if(length < minLength)
            {
                minLength = length;
                *next = x;
            }
        }
    }
    for(NodeIntersection* intersection : intersections)
    {
        if(from->getOutNode()->getId() == intersection->getId())
        {
            for(NodePath* x : intersection->getPaths())
            {
                if(x->getInNode()->getId() == from->getId()) // If path connects to path
                {
                    Node* tempNext;
                    int length = from->getLength() +
                        calculateIntersection((NodePath*)x, intersection, to, visited, &tempNext);
                    if(length < minLength)
                    {
                        minLength = length;
                        *next = x;
                    }
                }
            }
        }
    }
    return minLength;
}

int Graph::calculateIntersection(NodePath* from, NodeIntersection* intersection, NodeLocation* to,
    std::set<Node *> visited, Node** next)
{
    if(visited.count(from))
        return 10000;

    visited.insert(from);

    int minLength = 10000;
    for(NodePath* x : paths)
    {
        if(!visited.count(x) && // If not already visited
            from->getOutNode()->getId() == x->getId() &&
            x->getInNode()->getId() == intersection->getId()) // If path connects to intersection
        {
            Node* tempNext;
            int length = from->getLength() + calculatePath(x, to, visited, &tempNext);
            if(length < minLength)
            {
                minLength = length;
                *next = x;
            }
        }
    }
    return minLength;
}

Node* Graph::bestNextNode(Node* from, Node* to)
{
    Node* next = to;
    std::set<Node*> visited;

    if (NodeLocation* locFrom = dynamic_cast<NodeLocation*>(from))
    {
        if (NodeLocation* locTo = dynamic_cast<NodeLocation*>(to))
            calculateLocation(locFrom, locTo, visited, &next);
    }
    else if (NodePath* pathFrom = dynamic_cast<NodePath*>(from))
    {
        for (NodeIntersection* intersection : intersections)
        {
            if (intersection->getPaths().count(pathFrom))
            {
                if (NodeLocation* locTo = dynamic_cast<NodeLocation*>(to))
                    calculateIntersection(pathFrom, intersection, locTo, visited, &next);
                return next;
            }
        }
        if (NodeLocation* locTo = dynamic_cast<NodeLocation*>(to))
            calculatePath(pathFrom, locTo, visited, &next);
    }

    return next;
}

int Graph::getDurration(Node *from, Node *to)
{
    Node* next = to;
    std::set<Node*> visited;
    int length = 100000;

    if (NodeLocation* locFrom = dynamic_cast<NodeLocation*>(from))
    {
        if (NodeLocation* locTo = dynamic_cast<NodeLocation*>(to))
            length = calculateLocation(locFrom, locTo, visited, &next);
    }
    else if (NodePath* pathFrom = dynamic_cast<NodePath*>(from))
    {
        for (NodeIntersection* intersection : intersections)
        {
            if (intersection->getPaths().count(pathFrom))
            {
                if (NodeLocation* locTo = dynamic_cast<NodeLocation*>(to))
                    length = calculateIntersection(pathFrom, intersection, locTo, visited, &next);
                return length;
            }
        }
        if (NodeLocation* locTo = dynamic_cast<NodeLocation*>(to))
            length = calculatePath(pathFrom, locTo, visited, &next);
    }

    return length;
}

void Graph::serialize(std::ofstream& out)
{
    for(NodeLocation* x : locations)
        std::cout << x->getId() << " ";
    std::cout << std::endl;
    for(NodePath* x : paths)
        std::cout << x->getId() << " ";
    std::cout << std::endl;
    for(NodeIntersection* x : intersections)
        std::cout << x->getId() << " ";
    std::cout << std::endl;
}
