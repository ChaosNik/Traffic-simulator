#include <fstream>
#include "Simulation.hpp"

int main()
{
    // Everything will be on stack so we don't have to implicitly delete it
    
    // Generating map graph
    Graph map;

    // Creating locations
    NodeLocation A(1, "A");
    NodeLocation B(2, "B");
    NodeLocation C(3, "C");
    NodeLocation D(4, "D");

    // Adding locations to the graph
    map.addLocation(&A);
    map.addLocation(&B);
    map.addLocation(&C);
    map.addLocation(&D);

    // Creating intersection
    NodeIntersection X(5, 3);
    NodeIntersection Y(6, 3);

    // Adding intersections to the graph
    map.addIntersection(&X);
    map.addIntersection(&Y);

    // Creating paths
    NodePath AX(15, 100, 3, 5, &A, &X);
    NodePath XA(51, 100, 3, 5, &X, &A);
    NodePath XB(52, 100, 3, 5, &X, &B);
    NodePath BY(26, 100, 3, 5, &B, &Y);
    NodePath CX(35, 100, 3, 5, &C, &X);
    NodePath XC(53, 100, 3, 5, &X, &C);
    NodePath XD(54, 100, 3, 5, &X, &B);
    NodePath DY(46, 100, 3, 5, &B, &Y);
    NodePath YX(65, 100, 3, 5, &X, &B);


    // Adding paths to the graph
    map.addPath(&AX);
    map.addPath(&XA);
    map.addPath(&XB);
    map.addPath(&BY);
    map.addPath(&CX);
    map.addPath(&XC);
    map.addPath(&XD);
    map.addPath(&DY);
    map.addPath(&YX);

    // Creating paths in intersections
    NodePath AXD(154, 100, 3, 5, &AX, &XD);
    NodePath AXB(152, 100, 3, 5, &AX, &XB);
    NodePath AXC(153, 100, 3, 5, &AX, &XC);
    NodePath CXA(351, 100, 3, 5, &CX, &XA);
    NodePath CXB(352, 100, 3, 5, &CX, &XB);
    NodePath CXC(353, 100, 3, 5, &CX, &XC);
    NodePath CXD(354, 100, 3, 5, &CX, &XD);
    NodePath YXA(651, 100, 3, 5, &YX, &XA);
    NodePath YXB(652, 100, 3, 5, &YX, &XB);
    NodePath YXC(653, 100, 3, 5, &YX, &XC);
    NodePath YXD(654, 100, 3, 5, &YX, &XD);

    NodePath DYX(465, 100, 3, 5, &DY, &YX);
    NodePath BYX(265, 100, 3, 5, &BY, &YX);

    // Adding paths to intersections
    X.addNodePath(&AXD);
    X.addNodePath(&AXB);
    X.addNodePath(&AXC);
    X.addNodePath(&CXA);
    X.addNodePath(&CXB);
    X.addNodePath(&CXC);
    X.addNodePath(&CXD);
    X.addNodePath(&YXA);
    X.addNodePath(&YXB);
    X.addNodePath(&YXC);
    X.addNodePath(&YXD);

    Y.addNodePath(&DYX);
    Y.addNodePath(&BYX);

    // Creating simulation
    Simulation sim(&map, 1000);

    // Creating vehicles
    Vehicle v1(1, &map, &A, &B, 3);
    Vehicle v2(2, &map, &B, &D, 3);
    Vehicle v3(3, &map, &C, &C, 3);
    Vehicle v4(4, &map, &C, &D, 3);
    Vehicle v5(5, &map, &A, &D, 3);
    Vehicle v6(6, &map, &D, &A, 3);

    // Adding vehicles to the simulation
    sim.addVehicle(&v1);
    sim.addVehicle(&v2);
    sim.addVehicle(&v3);
    sim.addVehicle(&v4);
    sim.addVehicle(&v5);
    sim.addVehicle(&v6);

    // Running the simulation
    // sim.run();
    sim.runStepByStep();

    std::ofstream out("test.txt", std::ofstream::out);
    map.serialize(out);
    out.close();

    return 0;
}