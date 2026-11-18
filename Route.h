
#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <mutex>
#include <thread>

using namespace std;

class RouteException : public runtime_error {
public:
    RouteException(string message) : runtime_error(message) {}
};

class RouteValidationException : public RouteException {
public:
    RouteValidationException(string message)
        : RouteException(message) {}
};

class RouteProcessingException : public RouteValidationException {
public:
    RouteProcessingException(string message)
        : RouteValidationException(message) {}
};

class RouteInterface {
public:
    virtual void displayRoute() const = 0;
    virtual ~RouteInterface() = default;
};

class RouteSummary {
public:
    int routeId;
    string source;
    string destination;

    RouteSummary()
        : routeId(0), source(""), destination("") {}

    RouteSummary(int id, string src, string dest)
        : routeId(id), source(src), destination(dest) {}
};

class Route : virtual public RouteInterface {
private:
    int routeId;
    string source;
    string destination;
    double distance;

    static int routeCount;
    static mutex routeMutex;

public:
    class RoutePoint {
    public:
        string location;

        RoutePoint(string location = "")
            : location(location) {}

        void displayPoint() const {
            cout << "Location: " << location << '\n';
        }
    };

    Route();
    Route(int id, string source, string destination, double distance);
    Route(int id);
    Route(const Route& other);
    virtual ~Route() override;

    void setRoute(string source, string destination);
    void setRoute(string source, string destination, double distance);

    int getRouteId() const;
    string getSource() const;
    string getDestination() const;
    double getDistance() const;

    void displayRoute() const override;

    static int getRouteCount();

    Route& operator=(const Route& other);

    operator int() const;
    operator RouteSummary() const;

    friend bool operator==(const Route& r1, const Route& r2);
    friend ostream& operator<<(ostream& out, const Route& route);

    friend class RouteInspector;
};

class RouteInspector {
public:
    static void displayPrivateDetails(const Route& route);
};

class RouteRecord {
protected:
    string description;

public:
    RouteRecord(string description = "Normal route")
        : description(description) {}

    virtual ~RouteRecord() = default;

    virtual void displayRecord() const {
        cout << "Route record: " << description << '\n';
    }
};

class ExpressRouteRecord : public RouteRecord {
private:
    int expressLevel;

public:
    ExpressRouteRecord(string description, int level)
        : RouteRecord(description), expressLevel(level) {}

    void displayRecord() const override {
        cout << "Express route: " << description << '\n';
        cout << "Express level: " << expressLevel << '\n';
    }
};

template <typename T>
T getLargerRoute(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
class RouteStorage {
private:
    T data;

public:
    RouteStorage(T value) : data(value) {}

    T getData() const {
        return data;
    }

    void setData(T value) {
        data = value;
    }

    void displayData() const {
        cout << "Stored data: " << data << '\n';
    }
};

void demonstrateRouteThreads(Route& route);

#endif
