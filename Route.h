#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string>

using namespace std;

class Route
{
private:
    int routeId;
    string source;
    string destination;
    double distance;

public:
    Route();
    Route(int id, string source, string destination, double distance);
    ~Route();

    void setRoute(string source, string destination);
    void setRoute(string source, string destination, double distance);

    void displayRoute();

    // Assignment operator
    Route& operator=(const Route& other);

    // Friend operator
    friend bool operator==(const Route& r1,
                           const Route& r2);
};

#endif
