#include <fstream>
#include "Simulation.hpp"

int main()
{
    // Everything will be on stack so it doesn't have to implicitly deleted
    
    // Generating map graph
    int calculateBestByTime = 1;
    std::cout << "Enter 1 for length simulation or 2 for time simulation: ";
    std::cin >> calculateBestByTime;
    Graph map(calculateBestByTime==2);

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
    NodeIntersection X(5, 1, 3);
    NodeIntersection Y(6, 1, 3);

    // Adding intersections to the graph
    map.addIntersection(&X);
    map.addIntersection(&Y);

    // Creating paths
    NodePath AX(15, 1, 100, 3, 3, &A, &X);
    NodePath XA(51, 1, 100, 3, 3, &X, &A);
    NodePath XB(52, 2, 100, 3, 3, &X, &B);
    NodePath BY(26, 1, 100, 3, 3, &B, &Y);
    NodePath CX(35, 1, 100, 3, 3, &C, &X);
    NodePath XC(53, 1, 100, 3, 3, &X, &C);
    NodePath XD(54, 1, 100, 3, 3, &X, &D);
    NodePath DY(46, 1, 100, 3, 3, &D, &Y);
    NodePath YX(65, 1, 100, 3, 3, &Y, &X);


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
    NodePath AXD(154, 1, 100, 3, 3, &AX, &XD);
    NodePath AXB(152, 1, 100, 3, 3, &AX, &XB);
    NodePath AXC(153, 1, 100, 3, 3, &AX, &XC);
    NodePath CXA(351, 1, 100, 3, 3, &CX, &XA);
    NodePath CXB(352, 1, 100, 3, 3, &CX, &XB);
    NodePath CXC(353, 1, 100, 3, 3, &CX, &XC);
    NodePath CXD(354, 1, 100, 3, 3, &CX, &XD);
    NodePath YXA(651, 1, 100, 3, 3, &YX, &XA);
    NodePath YXB(652, 1, 100, 3, 3, &YX, &XB);
    NodePath YXC(653, 1, 100, 3, 3, &YX, &XC);
    NodePath YXD(654, 1, 100, 3, 3, &YX, &XD);

    NodePath DYX(465, 1, 100, 3, 3, &DY, &YX);
    NodePath BYX(265, 1, 100, 3, 3, &BY, &YX);

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
    Vehicle v1a(11, &map, &A, &B, 3);
    Vehicle v1b(12, &map, &A, &B, 3);
    Vehicle v1c(13, &map, &A, &B, 3);
    Vehicle v1d(14, &map, &A, &B, 3);
    Vehicle v1e(15, &map, &A, &B, 3);
    Vehicle v1f(16, &map, &A, &B, 3);
    Vehicle v1g(17, &map, &A, &B, 3);
    Vehicle v2(2, &map, &B, &D, 3);
    Vehicle v2a(21, &map, &B, &D, 3);
    Vehicle v2b(22, &map, &B, &D, 3);
    Vehicle v2c(22, &map, &B, &D, 3);
    Vehicle v2v(23, &map, &B, &D, 3);
    Vehicle v2d(24, &map, &B, &D, 3);
    Vehicle v2e(25, &map, &B, &D, 3);
    Vehicle v2f(26, &map, &B, &D, 3);
    Vehicle v2g(27, &map, &B, &D, 3);
    Vehicle v3(3, &map, &C, &C, 3);
    Vehicle v4(4, &map, &C, &D, 3);
    Vehicle v5(5, &map, &A, &D, 3);
    Vehicle v6(6, &map, &D, &A, 3);

    // Adding vehicles to the simulation
    sim.addVehicle(&v1);
    sim.addVehicle(&v1a);
    sim.addVehicle(&v1b);
    sim.addVehicle(&v1c);
    sim.addVehicle(&v1d);
    sim.addVehicle(&v1e);
    sim.addVehicle(&v1f);
    sim.addVehicle(&v1g);
    sim.addVehicle(&v2);
    sim.addVehicle(&v2a);
    sim.addVehicle(&v2b);
    sim.addVehicle(&v2c);
    sim.addVehicle(&v2d);
    sim.addVehicle(&v2e);
    sim.addVehicle(&v2f);
    sim.addVehicle(&v2g);
    sim.addVehicle(&v3);
    sim.addVehicle(&v4);
    sim.addVehicle(&v5);
    sim.addVehicle(&v6);

    // Running the simulation
    int select = 1;
    std::cout << "Enter 1 for auto simulation or 2 for step-by-step simulation: ";
    std::cin >> select;
    std::cin.ignore();
    if(select == 1)
        sim.run();
    else
        sim.runStepByStep();

    // Serialization
    std::ofstream out("test.txt", std::ofstream::out);
    map.serialize(out);
    out.close();

    return 0;
}