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

    
    Route()
    {
        routeId = 0;
        source = "Unknown";
        destination = "Unknown";
        distance = 0;
    }

    
    Route(int id, string source, string destination, double distance)
    {
        this->routeId = id;
        this->source = source;
        this->destination = destination;
        this->distance = distance;
    }


    ~Route()
    {
        cout << "Route object destroyed." << endl;
    }


    void setRoute(string source, string destination)
    {
        this->source = source;
        this->destination = destination;
    }

    void setRoute(string source, string destination, double distance)
    {
        this->source = source;
        this->destination = destination;
        this->distance = distance;
    }

    
    void displayRoute()
    {
        cout << "\n========== ROUTE ==========" << endl;
        cout << "Route ID    : " << routeId << endl;
        cout << "Source      : " << source << endl;
        cout << "Destination : " << destination << endl;
        cout << "Distance    : " << distance << " km" << endl;
        cout << "===========================" << endl;
    }


    friend bool operator==(const Route& r1, const Route& r2);
};


bool operator==(const Route& r1, const Route& r2)
{
    return r1.source == r2.source &&
           r1.destination == r2.destination;
}
