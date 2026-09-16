#include "Route.h"

Route::Route()
{
    routeId = 0;
    source = "Unknown";
    destination = "Unknown";
    distance = 0;
}

Route::Route(
    int id,
    string source,
    string destination,
    double distance)
{
    this->routeId = id;
    this->source = source;
    this->destination = destination;
    this->distance = distance;
}


Route::~Route()
{
    cout << "Route object destroyed." << endl;
}

void Route::setRoute(
    string source,
    string destination)
{
    this->source = source;
    this->destination = destination;
}

void Route::setRoute(
    string source,
    string destination,
    double distance)
{
    this->source = source;
    this->destination = destination;
    this->distance = distance;
}

void Route::displayRoute()
{
    cout << "\n========== ROUTE ==========" << endl;
    cout << "Route ID    : " << routeId << endl;
    cout << "Source      : " << source << endl;
    cout << "Destination : " << destination << endl;
    cout << "Distance    : " << distance << " km" << endl;
    cout << "===========================" << endl;
}


Route& Route::operator=(const Route& other)
{
    if (this != &other)
    {
        routeId = other.routeId;
        source = other.source;
        destination = other.destination;
        distance = other.distance;
    }

    return *this;
}


bool operator==(const Route& r1,
                const Route& r2)
{
    return r1.source == r2.source &&
           r1.destination == r2.destination;
}
