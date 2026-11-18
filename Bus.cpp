#include "Bus.h"
#include <thread>

int Bus::busCount = 0;
mutex Bus::busMutex;

BusException::BusException(const string& message)
    : runtime_error(message) {}

BusValidationException::BusValidationException(const string& message)
    : BusException(message) {}

InvalidBusId::InvalidBusId(const string& message)
    : BusValidationException(message) {}

BusProcessingException::BusProcessingException(const string& message)
    : BusException(message) {}

Bus::BusDetails::BusDetails()
    : busId(0), registrationNo("N/A"), description("No details") {}

Bus::BusDetails::BusDetails(int id, string registration, string description)
    : busId(id), registrationNo(registration), description(description) {}

void Bus::BusDetails::display() const {
    cout << "Bus ID: " << busId << '\n';
    cout << "Registration Number: " << registrationNo << '\n';
    cout << "Description: " << description << '\n';
}

Bus::Bus() : busId(0), capacity(0) {
    lock_guard<mutex> lock(busMutex);
    ++busCount;
}

Bus::Bus(int id, string registration, string type, int capacity)
    : busId(id), registrationNo(registration), busType(type),
      capacity(capacity) {

    if (id <= 0) {
        throw InvalidBusId("Bus ID must be positive.");
    }

    if (registration.empty() || type.empty() || capacity <= 0) {
        throw BusValidationException("Invalid bus details.");
    }

    for (int i = 1; i <= capacity; ++i) {
        seats.emplace_back(id * 1000 + i, i);
    }

    lock_guard<mutex> lock(busMutex);
    ++busCount;
}

Bus::Bus(int id) : busId(id), capacity(0) {
    if (id <= 0) {
        throw InvalidBusId("Bus ID must be positive.");
    }

    lock_guard<mutex> lock(busMutex);
    ++busCount;
}

Bus::Bus(const Bus& other) {
    {
        lock_guard<mutex> lock(busMutex);

        busId = other.busId;
        registrationNo = other.registrationNo;
        busType = other.busType;
        capacity = other.capacity;
        seats = other.seats;

        ++busCount;
    }
}

Bus::~Bus() {
    lock_guard<mutex> lock(busMutex);
    --busCount;
}

void Bus::setBus(string registration, string type) {
    if (registration.empty() || type.empty()) {
        throw BusValidationException("Registration and bus type cannot be empty.");
    }

    lock_guard<mutex> lock(busMutex);

    registrationNo = registration;
    busType = type;
}

void Bus::setBus(string registration, string type, int newCapacity) {
    if (registration.empty() || type.empty() || newCapacity <= 0) {
        throw BusValidationException("Invalid bus details or capacity.");
    }

    lock_guard<mutex> lock(busMutex);

    if (!seats.empty()) {
        throw BusProcessingException(
            "Cannot change capacity after seats have been added."
        );
    }

    registrationNo = registration;
    busType = type;
    capacity = newCapacity;

    for (int i = 1; i <= capacity; ++i) {
        seats.emplace_back(busId * 1000 + i, i);
    }
}

void Bus::addSeat(const Seat& seat) {
    lock_guard<mutex> lock(busMutex);

    if (static_cast<int>(seats.size()) >= capacity) {
        throw BusProcessingException("Bus capacity is already full.");
    }

    for (const Seat& existing : seats) {
        if (existing.getSeatNumber() == seat.getSeatNumber()) {
            throw BusProcessingException("Seat number already exists.");
        }
    }

    seats.push_back(seat);
}

bool Bus::checkAvailability(int seatNumber) const {
    lock_guard<mutex> lock(busMutex);

    for (const Seat& seat : seats) {
        if (seat.getSeatNumber() == seatNumber) {
            return seat.isAvailable();
        }
    }

    throw BusProcessingException("Seat number not found in this bus.");
}

void Bus::reserveSeat(int seatNumber) {
    lock_guard<mutex> lock(busMutex);

    for (Seat& seat : seats) {
        if (seat.getSeatNumber() == seatNumber) {
            seat.reserve();
            return;
        }
    }

    throw BusProcessingException("Seat number not found in this bus.");
}

void Bus::releaseSeat(int seatNumber) {
    lock_guard<mutex> lock(busMutex);

    for (Seat& seat : seats) {
        if (seat.getSeatNumber() == seatNumber) {
            seat.release();
            return;
        }
    }

    throw BusProcessingException("Seat number not found in this bus.");
}

int Bus::getAvailableSeats() const {
    lock_guard<mutex> lock(busMutex);

    int available = 0;

    for (const Seat& seat : seats) {
        if (seat.isAvailable()) {
            ++available;
        }
    }

    return available;
}

int Bus::getBusId() const {
    lock_guard<mutex> lock(busMutex);
    return busId;
}

string Bus::getRegistrationNo() const {
    lock_guard<mutex> lock(busMutex);
    return registrationNo;
}

string Bus::getBusType() const {
    lock_guard<mutex> lock(busMutex);
    return busType;
}

int Bus::getCapacity() const {
    lock_guard<mutex> lock(busMutex);
    return capacity;
}

void Bus::displayBus() const {
    displayDetails();
}

void Bus::displayDetails() const {
    lock_guard<mutex> lock(busMutex);

    cout << "\n--- Bus Details ---\n";
    cout << "Bus ID: " << busId << '\n';
    cout << "Registration Number: " << registrationNo << '\n';
    cout << "Bus Type: " << busType << '\n';
    cout << "Capacity: " << capacity << '\n';

    int available = 0;

    for (const Seat& seat : seats) {
        if (seat.isAvailable()) {
            ++available;
        }
    }

    cout << "Available Seats: " << available << '\n';
}

int Bus::getBusCount() {
    lock_guard<mutex> lock(busMutex);
    return busCount;
}

Bus& Bus::operator=(const Bus& other) {
    if (this != &other) {
        scoped_lock lock(busMutex);

        busId = other.busId;
        registrationNo = other.registrationNo;
        busType = other.busType;
        capacity = other.capacity;
        seats = other.seats;
    }

    return *this;
}

Bus::operator int() const {
    return getBusId();
}

Bus::operator BusSummary() const {
    lock_guard<mutex> lock(busMutex);

    return {busId, registrationNo, busType, capacity};
}

ostream& operator<<(ostream& out, const Bus& bus) {
    lock_guard<mutex> lock(Bus::busMutex);

    out << "Bus ID: " << bus.busId
        << "\nRegistration Number: " << bus.registrationNo
        << "\nBus Type: " << bus.busType
        << "\nCapacity: " << bus.capacity;

    return out;
}

bool operator==(const Bus& first, const Bus& second) {
    if (&first == &second) {
        return true;
    }

    scoped_lock lock(Bus::busMutex);

    return first.busId == second.busId;
}

void BusAdmin::displayBusDetails(const Bus& bus) {
    lock_guard<mutex> lock(Bus::busMutex);

    cout << "\n--- Bus Admin Details ---\n";
    cout << "Bus ID: " << bus.busId << '\n';
    cout << "Registration Number: " << bus.registrationNo << '\n';
    cout << "Bus Type: " << bus.busType << '\n';
    cout << "Capacity: " << bus.capacity << '\n';
    cout << "Total Seat Objects: " << bus.seats.size() << '\n';
}

void BusRecord::displayRecord() const {
    cout << "General Bus Record\n";
}

void LuxuryBusRecord::displayRecord() const {
    cout << "Luxury Bus Record\n";
}

void demonstrateBusThreads(Bus& bus) {
    thread t1([&bus]() {
        cout << "\nThread 1 - Available seats: "
             << bus.getAvailableSeats() << '\n';
    });

    thread t2([&bus]() {
        cout << "Thread 2 - Bus ID: "
             << bus.getBusId() << '\n';
    });

    t1.join();
    t2.join();
}