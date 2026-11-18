
#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <mutex>
#include <thread>

using namespace std;

class TripException : public runtime_error {
public:
    TripException(string message) : runtime_error(message) {}
};

class TripValidationException : public TripException {
public:
    TripValidationException(string message)
        : TripException(message) {}
};

class TripProcessingException : public TripValidationException {
public:
    TripProcessingException(string message)
        : TripValidationException(message) {}
};

class TripInterface {
public:
    virtual void displayTrip() const = 0;
    virtual ~TripInterface() = default;
};

class TripInfo : virtual public TripInterface {
public:
    virtual ~TripInfo() = default;
};

class TripAudit : virtual public TripInterface {
public:
    virtual ~TripAudit() = default;
};

class TripSummary {
public:
    int tripId;
    int busId;
    int routeId;
    int scheduleId;
    int operatorId;
    int availableSeats;
    string status;

    TripSummary()
        : tripId(0), busId(0), routeId(0),
          scheduleId(0), operatorId(0),
          availableSeats(0), status("Scheduled") {}

    TripSummary(int tId, int bId, int rId, int sId,
                int oId, int seats, string tripStatus)
        : tripId(tId), busId(bId), routeId(rId),
          scheduleId(sId), operatorId(oId),
          availableSeats(seats), status(tripStatus) {}
};

class Trip : public TripInfo, public TripAudit {
private:
    int tripId;
    int busId;
    int routeId;
    int scheduleId;
    int operatorId;
    int totalSeats;
    int bookedSeats;
    string status;

    static int tripCount;
    static mutex tripMutex;

public:
    class TripDetails {
    private:
        string description;

    public:
        TripDetails(string description = "No details")
            : description(description) {}

        void displayDetails() const {
            cout << "Trip details: " << description << '\n';
        }
    };

    Trip();
    Trip(int tripId, int busId, int routeId,
         int scheduleId, int operatorId, int totalSeats);
    Trip(int tripId);
    Trip(const Trip& other);
    virtual ~Trip() override;

    void setTrip(string status);
    void setTrip(int totalSeats, string status);

    bool bookSeats(int seats);
    bool cancelSeats(int seats);

    void displayTrip() const override;
    void displayAvailableSeats() const;

    int getTripId() const;
    int getBusId() const;
    int getRouteId() const;
    int getScheduleId() const;
    int getOperatorId() const;
    int getTotalSeats() const;
    int getBookedSeats() const;
    int getAvailableSeats() const;
    string getStatus() const;

    static int getTripCount();

    Trip& operator=(const Trip& other);

    operator int() const;
    operator TripSummary() const;

    friend ostream& operator<<(ostream& out, const Trip& trip);
    friend bool operator==(const Trip& t1, const Trip& t2);
    friend bool isSameOperator(const Trip& t1, const Trip& t2);

    friend class TripAdmin;
};

class TripAdmin {
public:
    static void displayTripInfo(const Trip& trip);
};

template <typename T>
T getLargerTrip(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
class TripStorage {
private:
    T data;

public:
    TripStorage(T value) : data(value) {}

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

class TripRecord {
public:
    int recordId;

    TripRecord(int id = 0) : recordId(id) {}

    virtual void displayRecord() const {
        cout << "Trip record ID: " << recordId << '\n';
    }

    virtual ~TripRecord() = default;
};

class SpecialTripRecord : public TripRecord {
public:
    string category;

    SpecialTripRecord(int id, string category)
        : TripRecord(id), category(category) {}

    void displayRecord() const override {
        cout << "Special trip ID: " << recordId << '\n';
        cout << "Category: " << category << '\n';
    }
};

void demonstrateTripThreads(Trip& trip);

#endif
