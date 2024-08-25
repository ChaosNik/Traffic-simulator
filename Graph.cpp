#include "Graph.hpp"
#include <iostream>
#include <fstream>

// Calculates the shortest path between two location nodes
int Graph::calculateLocation(NodeLocation* from, NodeLocation* to,
    std::set<Node*> visited, Node** next)
{
    if(from->getId() == to->getId())
        return 0;

    if(visited.count(from))
        return 10000;

    visited.insert(from);

    int minMeasure = 10000;
    for(NodePath* x : paths)
    {
        if(!visited.count(x) && // If not already visited
            x->getInNode()->getId() == from->getId()) // If path connects to location
        {
            Node* tempNext;
            int measure = calculatePath(x, to, visited, &tempNext);
            if(measure < minMeasure)
            {
                minMeasure = measure;
                *next = x;
            }
        }
    }
    return minMeasure;
}

// Calculates the shortest path through a path node
int Graph::calculatePath(NodePath* from, NodeLocation* to,
    std::set<Node *> visited, Node** next)
{
    if(visited.count(from))
        return 10000;

    visited.insert(from);

    int minMeasure = 10000;
    for(NodeLocation* x : locations)
    {
        if(from->getOutNode()->getId() == x->getId()) // If path connects to location
        {
            Node* tempNext;
            if(calculateBestByTime)
            {
                int time = (from->getLength() / from->getMaxSpeed()) + calculateLocation(x, to, visited, &tempNext);
                if(time < minMeasure)
                {
                    minMeasure = time;
                    *next = x;
                }
            }
            else
            {
                int length = from->getLength() + calculateLocation(x, to, visited, &tempNext);
                if(length < minMeasure)
                {
                    minMeasure = length;
                    *next = x;
                }
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
                    if(calculateBestByTime)
                    {
                        int time = from->getLength() / from->getMaxSpeed() + 
                            calculateIntersection((NodePath*)x, intersection, to, visited, &tempNext);
                            if(time < minMeasure)
                            {
                                minMeasure = time;
                                *next = x;
                            }
                    }
                    else
                    {
                        int length = from->getLength() +
                            calculateIntersection((NodePath*)x, intersection, to, visited, &tempNext);
                        if(length < minMeasure)
                        {
                            minMeasure = length;
                            *next = x;
                        }
                    }
                }
            }
        }
    }
    return minMeasure;
}

// Calculates the shortest path through an intersection
int Graph::calculateIntersection(NodePath* from, NodeIntersection* intersection, NodeLocation* to,
    std::set<Node *> visited, Node** next)
{
    if(visited.count(from))
        return 10000;

    visited.insert(from);

    int minMeasure = 10000;
    for(NodePath* x : paths)
    {
        if(!visited.count(x) && // If not already visited
            from->getOutNode()->getId() == x->getId() &&
            x->getInNode()->getId() == intersection->getId()) // If path connects to intersection
        {
            Node* tempNext;
            if(calculateBestByTime)
            {
                int time = from->getLength() / from->getMaxSpeed() + calculatePath(x, to, visited, &tempNext);
                if(time < minMeasure)
                {
                    minMeasure = time;
                    *next = x;
                }
            }
            else
            {
                int length = from->getLength() + calculatePath(x, to, visited, &tempNext);
                if(length < minMeasure)
                {
                    minMeasure = length;
                    *next = x;
                }  
            } 
        }
    }
    return minMeasure;
}

// Finds the best next node on the path
Node* Graph::bestNextNode(Node* from, Node* to)
{
    Node* next = to;
    std::set<Node*> visited;

    if (NodeLocation* locFrom = dynamic_cast<NodeLocation*>(from))
    {
        if (NodeLocation* locTo = dynamic_cast<NodeLocation*>(to))
        {
            calculateLocation(locFrom, locTo, visited, &next);
        }
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

// Serialize the graph to a file
void Graph::serialize(std::ofstream& out)
{
    out << locations.size() << "\n";
    for (auto& loc : locations)
        out << loc->getId() << "\n" << loc->getName() << "\n";
    
    out << paths.size() << "\n";
    for (auto& path : paths)
        out << path->getId() << "\n" << path->getSlowdownFactorValue() << "\n" << path->getLength() << "\n" << path->getMaxSpeed() << "\n"
            << path->getCapacity() << "\n" << path->getInNode()->getId() << "\n" << path->getOutNode()->getId() << "\n";

    out << intersections.size() << "\n";
    for (auto& intersection : intersections) {
        out << intersection->getId() << intersection->getSlowdownFactorValue() << "\n" << "\n" << intersection->getMaxSpeed() << "\n";
        out << intersection->getPaths().size() << "\n";
        for (auto& path : intersection->getPaths())
            out << path->getId() << "\n";
    }
}

// Deserialize the graph from a file
Graph Graph::deserialize(std::ifstream &in)
{
    Graph graph;
    size_t size;
    std::string line;

    // Deserialize NodeLocations
    in >> size;
    std::getline(in, line); // consume newline
    for (size_t i = 0; i < size; ++i) {
        int id;
        std::string name;
        in >> id;
        in.ignore(); // Ignore the newline after the id
        std::getline(in, name);
        NodeLocation* loc = new NodeLocation(id, name);
        graph.locations.insert(loc);
    }

    // Create a set of all nodes for reference
    std::set<Node*> nodes(graph.locations.begin(), graph.locations.end());

    // Deserialize NodePaths
    in >> size;
    std::getline(in, line); // consume newline
    for (size_t i = 0; i < size; ++i) {
        int id, length, maxSpeed, maxCapacity, inNodeId, outNodeId;
        float slowdownFactor;
        in >> id >> slowdownFactor >> length >> maxSpeed >> maxCapacity >> inNodeId >> outNodeId;
        in.ignore(); // Ignore the newline after the last integer

        Node* inNode = nullptr;
        Node* outNode = nullptr;
        for (auto node : nodes) {
            if (node->getId() == inNodeId) inNode = node;
            if (node->getId() == outNodeId) outNode = node;
        }

        if (inNode && outNode) {
            NodePath* path = new NodePath(id, slowdownFactor, length, maxSpeed, maxCapacity, inNode, outNode);
            graph.paths.insert(path);
            nodes.insert(path);
        }
    }

    // Deserialize NodeIntersections
    in >> size;
    std::getline(in, line); // consume newline
    for (size_t i = 0; i < size; ++i) {
        int id, maxCapacity, pathCount, pathId;
        float slowdownFactor;
        in >> id >> slowdownFactor >> maxCapacity >> pathCount;
        in.ignore(); // Ignore the newline after the last integer

        auto* intersection = new NodeIntersection(id, slowdownFactor, maxCapacity);
        for (int j = 0; j < pathCount; ++j) {
            in >> pathId;
            in.ignore(); // Ignore the newline after the integer
            for (auto path : graph.paths) {
                if (path->getId() == pathId) {
                    intersection->addNodePath(path);
                    break;
                }
            }
        }
        graph.intersections.insert(intersection);
    }

    return graph;
}

int Node::getSlowdownFactor(int numberOfVehiclesInNode)
{
    if(getCapacity() > 0 && getCapacity() < 10000 )
    {
        return 1 + slowdownFactor * (getCapacity() - numberOfVehiclesInNode) / getCapacity();
    }
    return slowdownFactor;
}
