#pragma once

#include <string>
#include <iostream>
#include <set>
#include <list>

// Base class for all types of nodes in the graph
class Node
{
public:
    Node(int id, float slowdownFactor = 1): id(id), slowdownFactor(slowdownFactor) {}
    virtual int getId(){return id;}
    virtual int getLength() {return 0;}
    virtual int getMaxSpeed() {return 10000;}
    int getCapacity() {return 10000;}
    int getSlowdownFactor(int numberOfVehiclesInNode);
    float getSlowdownFactorValue() {return slowdownFactor;}

private:
    int id;
    float slowdownFactor;
};

// Class for location nodes (cities, parking, etc.)
class NodeLocation : public Node
{
public:
    NodeLocation(int id, std::string name): Node(id), name(std::move(name)) {}
    std::string getName() {return name;}

private:
    std::string name;
};

// Class for path nodes (road segments)
class NodePath : public Node
{
public:
    NodePath(int id, float slowdownFactor, int length, int maxSpeed, int maxCapacity, Node* inNode, Node* outNode):
        Node(id, slowdownFactor), length(length), maxSpeed(maxSpeed), maxCapacity(maxCapacity),
        inNode(inNode), outNode(outNode) {}
    int getLength() {return length;}
    int getMaxSpeed() {return maxSpeed;}
    int getCapacity() {return maxCapacity;}
    Node* getInNode() {return inNode;}
    Node* getOutNode() {return outNode;}

private:
    int length;
    int maxSpeed;
    int maxCapacity;
    Node* inNode;
    Node* outNode;
};

// Class for intersection nodes
class NodeIntersection : public Node
{
public:
    NodeIntersection(int id, float slowdownFactor, int maxCapacity,
        std::set<NodePath*> paths = {}):
        Node(id, slowdownFactor), paths(paths), maxCapacity(maxCapacity) {}
    std::set<NodePath*> getPaths() {return paths;}
    void addNodePath(NodePath* path) {paths.insert(path);}

private:
    int maxCapacity;
    std::set<NodePath*> paths;
};

// Class for the graph representing the traffic network
class Graph
{
public:
    Graph(bool calculateBestByTime = false) {}
    std::set<NodeLocation*> getLocations() {return locations;}
    std::set<NodePath*> getPaths() {return paths;}
    std::set<NodeIntersection*> getIntersections() {return intersections;}

    void addLocation(NodeLocation* node) {locations.insert(node);}
    void addPath(NodePath* node) {paths.insert(node);}
    void addIntersection(NodeIntersection* node) {intersections.insert(node);}
    int calculateLocation(NodeLocation* from, NodeLocation* to, std::set<Node*> visited, Node** next);
    int calculatePath(NodePath* from, NodeLocation* to, std::set<Node*> visited, Node** next);
    int calculateIntersection(NodePath* from, NodeIntersection* intersection, NodeLocation* to, std::set<Node*> visited, Node** next);
    Node* bestNextNode(Node* from, Node* to);
    int getDurration(Node* from, Node* to);
    bool isLocation(Node* x) {return locations.count((NodeLocation*)x);}
    bool isPath(Node* x) {return paths.count((NodePath*)x);}
    bool isIntersection(Node* x) {return intersections.count((NodeIntersection*)x);}
    void serialize(std::ofstream& out);
    Graph deserialize(std::ifstream& in);

private:
    std::set<NodeLocation*> locations;
    std::set<NodePath*> paths;
    std::set<NodeIntersection*> intersections;
    bool calculateBestByTime;
};
