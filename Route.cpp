
#include "Route.h"

int Route::routeCount = 0;
mutex Route::routeMutex;

Route::Route()
    : routeId(0), source(""), destination(""), distance(0) {
    lock_guard<mutex> lock(routeMutex);
    ++routeCount;
}

Route::Route(int id, string source, string destination,
             double distance)
    : routeId(id), source(source), destination(destination),
      distance(distance) {
    lock_guard<mutex> lock(routeMutex);
    ++routeCount;
}

Route::Route(int id)
    : routeId(id), source("Unknown"),
      destination("Unknown"), distance(0) {
    lock_guard<mutex> lock(routeMutex);
    ++routeCount;
}

Route::Route(const Route& other) {
    lock_guard<mutex> lock(routeMutex);

    routeId = other.routeId;
    source = other.source;
    destination = other.destination;
    distance = other.distance;

    ++routeCount;
}

Route::~Route() {
    lock_guard<mutex> lock(routeMutex);
    --routeCount;
}

void Route::setRoute(string source, string destination) {
    lock_guard<mutex> lock(routeMutex);

    if (source.empty() || destination.empty()) {
        throw RouteValidationException("Source and destination cannot be empty.");
    }

    if (source == destination) {
        throw RouteProcessingException("Source and destination cannot be the same.");
    }

    this->source = source;
    this->destination = destination;
}

void Route::setRoute(string source, string destination,
                     double distance) {
    lock_guard<mutex> lock(routeMutex);

    if (source.empty() || destination.empty() || distance <= 0) {
        throw RouteValidationException("Invalid route details.");
    }

    if (source == destination) {
        throw RouteProcessingException("Source and destination cannot be the same.");
    }

    this->source = source;
    this->destination = destination;
    this->distance = distance;
}

int Route::getRouteId() const {
    lock_guard<mutex> lock(routeMutex);
    return routeId;
}

string Route::getSource() const {
    lock_guard<mutex> lock(routeMutex);
    return source;
}

string Route::getDestination() const {
    lock_guard<mutex> lock(routeMutex);
    return destination;
}

double Route::getDistance() const {
    lock_guard<mutex> lock(routeMutex);
    return distance;
}

void Route::displayRoute() const {
    lock_guard<mutex> lock(routeMutex);

    cout << "Route ID: " << routeId << '\n';
    cout << "Source: " << source << '\n';
    cout << "Destination: " << destination << '\n';
    cout << "Distance: " << distance << " km\n";
}

int Route::getRouteCount() {
    lock_guard<mutex> lock(routeMutex);
    return routeCount;
}

Route& Route::operator=(const Route& other) {
    if (this != &other) {
        lock_guard<mutex> lock(routeMutex);

        routeId = other.routeId;
        source = other.source;
        destination = other.destination;
        distance = other.distance;
    }

    return *this;
}

Route::operator int() const {
    lock_guard<mutex> lock(routeMutex);
    return routeId;
}

Route::operator RouteSummary() const {
    lock_guard<mutex> lock(routeMutex);

    return RouteSummary(routeId, source, destination);
}

bool operator==(const Route& r1, const Route& r2) {
    lock_guard<mutex> lock(Route::routeMutex);

    return r1.source == r2.source &&
           r1.destination == r2.destination;
}

ostream& operator<<(ostream& out, const Route& route) {
    lock_guard<mutex> lock(Route::routeMutex);

    out << "Route ID: " << route.routeId << '\n';
    out << "Source: " << route.source << '\n';
    out << "Destination: " << route.destination << '\n';
    out << "Distance: " << route.distance << " km\n";

    return out;
}

void RouteInspector::displayPrivateDetails(const Route& route) {
    lock_guard<mutex> lock(Route::routeMutex);

    cout << "Private Route Details:\n";
    cout << "ID: " << route.routeId << '\n';
    cout << "Source: " << route.source << '\n';
    cout << "Destination: " << route.destination << '\n';
    cout << "Distance: " << route.distance << " km\n";
}

void demonstrateRouteThreads(Route& route) {
    auto task = [&route]() {
        try {
            route.displayRoute();
        }
        catch (const RouteException& e) {
            cout << "Route error: " << e.what() << '\n';
        }
    };

    thread t1(task);
    thread t2(task);

    t1.join();
    t2.join();
}
