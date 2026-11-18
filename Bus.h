#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <stdexcept>
#include "Seat.h"

using namespace std;

class BusException : public runtime_error {
public:
    explicit BusException(const string& message);
};

class BusValidationException : public BusException {
public:
    explicit BusValidationException(const string& message);
};

class InvalidBusId : public BusValidationException {
public:
    explicit InvalidBusId(const string& message);
};

class BusProcessingException : public BusException {
public:
    explicit BusProcessingException(const string& message);
};

class BusInterface {
public:
    virtual void displayBus() const = 0;
    virtual ~BusInterface() = default;
};

struct BusSummary {
    int busId;
    string registrationNo;
    string busType;
    int capacity;
};

class Bus : public virtual BusInterface {
private:
    int busId;
    string registrationNo;
    string busType;
    int capacity;
    vector<Seat> seats;

    static int busCount;
    static mutex busMutex;

public:
    class BusDetails {
    public:
        int busId;
        string registrationNo;
        string description;

        BusDetails();
        BusDetails(int id, string registration, string description);
        void display() const;
    };

    Bus();
    Bus(int id, string registration, string type, int capacity);
    Bus(int id);
    Bus(const Bus& other);
    virtual ~Bus();

    void setBus(string registration, string type);
    void setBus(string registration, string type, int capacity);

    void addSeat(const Seat& seat);
    bool checkAvailability(int seatNumber) const;
    void reserveSeat(int seatNumber);
    void releaseSeat(int seatNumber);

    int getAvailableSeats() const;
    int getBusId() const;
    string getRegistrationNo() const;
    string getBusType() const;
    int getCapacity() const;

    void displayBus() const override;
    void displayDetails() const;

    static int getBusCount();

    Bus& operator=(const Bus& other);
    operator int() const;
    operator BusSummary() const;

    friend ostream& operator<<(ostream& out, const Bus& bus);
    friend bool operator==(const Bus& first, const Bus& second);
    friend class BusAdmin;
};

class BusAdmin {
public:
    static void displayBusDetails(const Bus& bus);
};

class BusRecord {
public:
    virtual void displayRecord() const;
    virtual ~BusRecord() = default;
};

class LuxuryBusRecord : public BusRecord {
public:
    void displayRecord() const override;
};

template <typename T>
T getLargerBus(T first, T second) {
    return (first > second) ? first : second;
}

template <typename T>
class BusStorage {
private:
    T data;

public:
    BusStorage() : data() {}
    explicit BusStorage(T value) : data(value) {}

    void setData(T value) {
        data = value;
    }

    T getData() const {
        return data;
    }

    void displayData() const {
        cout << "Stored Bus Data: " << data << '\n';
    }
};

void demonstrateBusThreads(Bus& bus);

#endif