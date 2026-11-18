
#include "Trip.h"

int Trip::tripCount = 0;
mutex Trip::tripMutex;

Trip::Trip()
    : tripId(0), busId(0), routeId(0),
      scheduleId(0), operatorId(0),
      totalSeats(0), bookedSeats(0),
      status("Scheduled") {

    lock_guard<mutex> lock(tripMutex);
    ++tripCount;
}

Trip::Trip(int tripId, int busId, int routeId,
           int scheduleId, int operatorId, int totalSeats)
    : tripId(tripId), busId(busId), routeId(routeId),
      scheduleId(scheduleId), operatorId(operatorId),
      totalSeats(totalSeats > 0 ? totalSeats : 0),
      bookedSeats(0), status("Scheduled") {

    lock_guard<mutex> lock(tripMutex);
    ++tripCount;
}

Trip::Trip(int tripId)
    : tripId(tripId), busId(0), routeId(0),
      scheduleId(0), operatorId(0),
      totalSeats(0), bookedSeats(0),
      status("Scheduled") {

    lock_guard<mutex> lock(tripMutex);
    ++tripCount;
}

Trip::Trip(const Trip& other) {
    lock_guard<mutex> lock(tripMutex);

    tripId = other.tripId;
    busId = other.busId;
    routeId = other.routeId;
    scheduleId = other.scheduleId;
    operatorId = other.operatorId;
    totalSeats = other.totalSeats;
    bookedSeats = other.bookedSeats;
    status = other.status;

    ++tripCount;
}

Trip::~Trip() {
    lock_guard<mutex> lock(tripMutex);
    --tripCount;
}

void Trip::setTrip(string status) {
    lock_guard<mutex> lock(tripMutex);

    if (status.empty()) {
        throw TripValidationException("Trip status cannot be empty.");
    }

    this->status = status;
}

void Trip::setTrip(int totalSeats, string status) {
    lock_guard<mutex> lock(tripMutex);

    if (totalSeats <= 0) {
        throw TripValidationException("Total seats must be positive.");
    }

    if (totalSeats < bookedSeats) {
        throw TripProcessingException(
            "Total seats cannot be less than booked seats."
        );
    }

    if (status.empty()) {
        throw TripValidationException("Trip status cannot be empty.");
    }

    this->totalSeats = totalSeats;
    this->status = status;
}

bool Trip::bookSeats(int seats) {
    lock_guard<mutex> lock(tripMutex);

    if (status != "Scheduled") {
        throw TripProcessingException(
            "Seats cannot be booked because trip is not scheduled."
        );
    }

    if (seats <= 0) {
        throw TripValidationException(
            "Number of seats must be positive."
        );
    }

    if (seats > totalSeats - bookedSeats) {
        throw TripProcessingException("Not enough seats available.");
    }

    bookedSeats += seats;

    cout << seats << " seat(s) booked successfully.\n";
    return true;
}

bool Trip::cancelSeats(int seats) {
    lock_guard<mutex> lock(tripMutex);

    if (seats <= 0 || seats > bookedSeats) {
        throw TripValidationException(
            "Invalid number of seats to cancel."
        );
    }

    bookedSeats -= seats;

    cout << seats << " seat(s) cancelled successfully.\n";
    return true;
}

void Trip::displayTrip() const {
    lock_guard<mutex> lock(tripMutex);

    cout << "\n--- Trip Details ---\n";
    cout << "Trip ID: " << tripId << '\n';
    cout << "Bus ID: " << busId << '\n';
    cout << "Route ID: " << routeId << '\n';
    cout << "Schedule ID: " << scheduleId << '\n';
    cout << "Operator ID: " << operatorId << '\n';
    cout << "Total seats: " << totalSeats << '\n';
    cout << "Booked seats: " << bookedSeats << '\n';
    cout << "Available seats: " << totalSeats - bookedSeats << '\n';
    cout << "Status: " << status << '\n';
}

void Trip::displayAvailableSeats() const {
    lock_guard<mutex> lock(tripMutex);
    cout << "Available seats: " << totalSeats - bookedSeats << '\n';
}

int Trip::getTripId() const {
    lock_guard<mutex> lock(tripMutex);
    return tripId;
}

int Trip::getBusId() const {
    lock_guard<mutex> lock(tripMutex);
    return busId;
}

int Trip::getRouteId() const {
    lock_guard<mutex> lock(tripMutex);
    return routeId;
}

int Trip::getScheduleId() const {
    lock_guard<mutex> lock(tripMutex);
    return scheduleId;
}

int Trip::getOperatorId() const {
    lock_guard<mutex> lock(tripMutex);
    return operatorId;
}

int Trip::getTotalSeats() const {
    lock_guard<mutex> lock(tripMutex);
    return totalSeats;
}

int Trip::getBookedSeats() const {
    lock_guard<mutex> lock(tripMutex);
    return bookedSeats;
}

int Trip::getAvailableSeats() const {
    lock_guard<mutex> lock(tripMutex);
    return totalSeats - bookedSeats;
}

string Trip::getStatus() const {
    lock_guard<mutex> lock(tripMutex);
    return status;
}

int Trip::getTripCount() {
    lock_guard<mutex> lock(tripMutex);
    return tripCount;
}

Trip& Trip::operator=(const Trip& other) {
    if (this != &other) {
        lock_guard<mutex> lock(tripMutex);

        tripId = other.tripId;
        busId = other.busId;
        routeId = other.routeId;
        scheduleId = other.scheduleId;
        operatorId = other.operatorId;
        totalSeats = other.totalSeats;
        bookedSeats = other.bookedSeats;
        status = other.status;
    }

    return *this;
}

Trip::operator int() const {
    lock_guard<mutex> lock(tripMutex);
    return tripId;
}

Trip::operator TripSummary() const {
    lock_guard<mutex> lock(tripMutex);

    return TripSummary(
        tripId, busId, routeId, scheduleId,
        operatorId, totalSeats - bookedSeats, status
    );
}

ostream& operator<<(ostream& out, const Trip& trip) {
    lock_guard<mutex> lock(Trip::tripMutex);

    out << "Trip ID: " << trip.tripId
        << "\nBus ID: " << trip.busId
        << "\nRoute ID: " << trip.routeId
        << "\nSchedule ID: " << trip.scheduleId
        << "\nOperator ID: " << trip.operatorId
        << "\nAvailable seats: " << trip.totalSeats - trip.bookedSeats
        << "\nStatus: " << trip.status;

    return out;
}

bool operator==(const Trip& t1, const Trip& t2) {
    lock_guard<mutex> lock(Trip::tripMutex);
    return t1.tripId == t2.tripId;
}

bool isSameOperator(const Trip& t1, const Trip& t2) {
    lock_guard<mutex> lock(Trip::tripMutex);
    return t1.operatorId == t2.operatorId;
}

void TripAdmin::displayTripInfo(const Trip& trip) {
    lock_guard<mutex> lock(Trip::tripMutex);

    cout << "\n--- Trip Admin View ---\n";
    cout << "Trip ID: " << trip.tripId << '\n';
    cout << "Bus ID: " << trip.busId << '\n';
    cout << "Operator ID: " << trip.operatorId << '\n';
    cout << "Status: " << trip.status << '\n';
}

void demonstrateTripThreads(Trip& trip) {
    auto task = [&trip]() {
        try {
            trip.displayAvailableSeats();
        }
        catch (const TripException& e) {
            cout << "Trip error: " << e.what() << '\n';
        }
    };

    thread t1(task);
    thread t2(task);

    t1.join();
    t2.join();
}
