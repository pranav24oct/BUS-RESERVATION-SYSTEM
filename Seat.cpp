#include "Seat.h"
#include <thread>

int Seat::seatCount = 0;
mutex Seat::seatMutex;

SeatException::SeatException(const string& message)
    : runtime_error(message) {}

SeatValidationException::SeatValidationException(const string& message)
    : SeatException(message) {}

InvalidSeatId::InvalidSeatId(const string& message)
    : SeatValidationException(message) {}

SeatProcessingException::SeatProcessingException(const string& message)
    : SeatException(message) {}

Seat::SeatDetails::SeatDetails()
    : seatId(0), seatNumber(0), description("No details") {}

Seat::SeatDetails::SeatDetails(int id, int number, string description)
    : seatId(id), seatNumber(number), description(description) {}

void Seat::SeatDetails::display() const {
    cout << "Seat ID: " << seatId << '\n';
    cout << "Seat Number: " << seatNumber << '\n';
    cout << "Description: " << description << '\n';
}

Seat::Seat() : seatId(0), seatNumber(0), status(SeatStatus::Available) {
    lock_guard<mutex> lock(seatMutex);
    ++seatCount;
}

Seat::Seat(int id, int number)
    : seatId(id), seatNumber(number), status(SeatStatus::Available) {
    if (id <= 0 || number <= 0) {
        throw InvalidSeatId("Seat ID and seat number must be positive.");
    }

    lock_guard<mutex> lock(seatMutex);
    ++seatCount;
}

Seat::Seat(int id)
    : seatId(id), seatNumber(id), status(SeatStatus::Available) {
    if (id <= 0) {
        throw InvalidSeatId("Seat ID must be positive.");
    }

    lock_guard<mutex> lock(seatMutex);
    ++seatCount;
}

Seat::Seat(const Seat& other) {
    lock_guard<mutex> lock(seatMutex);

    seatId = other.seatId;
    seatNumber = other.seatNumber;
    status = other.status;

    ++seatCount;
}

Seat::~Seat() {
    lock_guard<mutex> lock(seatMutex);
    --seatCount;
}

void Seat::hold() {
    lock_guard<mutex> lock(seatMutex);

    if (status != SeatStatus::Available) {
        throw SeatProcessingException("Seat is not available for holding.");
    }

    status = SeatStatus::Held;
}

void Seat::reserve() {
    lock_guard<mutex> lock(seatMutex);

    if (status == SeatStatus::Reserved) {
        throw SeatProcessingException("Seat is already reserved.");
    }

    if (status == SeatStatus::Available || status == SeatStatus::Held) {
        status = SeatStatus::Reserved;
    }
}

void Seat::release() {
    lock_guard<mutex> lock(seatMutex);

    if (status == SeatStatus::Available) {
        throw SeatProcessingException("Seat is already available.");
    }

    status = SeatStatus::Available;
}

bool Seat::isAvailable() const {
    lock_guard<mutex> lock(seatMutex);
    return status == SeatStatus::Available;
}

void Seat::setStatus(SeatStatus newStatus) {
    lock_guard<mutex> lock(seatMutex);
    status = newStatus;
}

int Seat::getSeatId() const {
    lock_guard<mutex> lock(seatMutex);
    return seatId;
}

int Seat::getSeatNumber() const {
    lock_guard<mutex> lock(seatMutex);
    return seatNumber;
}

SeatStatus Seat::getStatus() const {
    lock_guard<mutex> lock(seatMutex);
    return status;
}

void Seat::displaySeat() const {
    lock_guard<mutex> lock(seatMutex);

    cout << "\nSeat ID: " << seatId;
    cout << "\nSeat Number: " << seatNumber;
    cout << "\nStatus: ";

    switch (status) {
        case SeatStatus::Available:
            cout << "Available";
            break;
        case SeatStatus::Held:
            cout << "Held";
            break;
        case SeatStatus::Reserved:
            cout << "Reserved";
            break;
    }

    cout << '\n';
}

int Seat::getSeatCount() {
    lock_guard<mutex> lock(seatMutex);
    return seatCount;
}

Seat& Seat::operator=(const Seat& other) {
    if (this != &other) {
        scoped_lock lock(seatMutex);

        seatId = other.seatId;
        seatNumber = other.seatNumber;
        status = other.status;
    }

    return *this;
}

Seat::operator int() const {
    return getSeatNumber();
}

Seat::operator SeatSummary() const {
    lock_guard<mutex> lock(seatMutex);
    return {seatId, seatNumber, status};
}

ostream& operator<<(ostream& out, const Seat& seat) {
    lock_guard<mutex> lock(Seat::seatMutex);

    out << "Seat ID: " << seat.seatId
        << "\nSeat Number: " << seat.seatNumber
        << "\nStatus: ";

    switch (seat.status) {
        case SeatStatus::Available:
            out << "Available";
            break;
        case SeatStatus::Held:
            out << "Held";
            break;
        case SeatStatus::Reserved:
            out << "Reserved";
            break;
    }

    return out;
}

bool operator==(const Seat& first, const Seat& second) {
    if (&first == &second) {
        return true;
    }

    scoped_lock lock(Seat::seatMutex);

    return first.seatId == second.seatId;
}

void SeatAdmin::displaySeatDetails(const Seat& seat) {
    lock_guard<mutex> lock(Seat::seatMutex);

    cout << "\n--- Seat Admin Details ---\n";
    cout << "Seat ID: " << seat.seatId << '\n';
    cout << "Seat Number: " << seat.seatNumber << '\n';
    cout << "Status: ";

    switch (seat.status) {
        case SeatStatus::Available:
            cout << "Available";
            break;
        case SeatStatus::Held:
            cout << "Held";
            break;
        case SeatStatus::Reserved:
            cout << "Reserved";
            break;
    }

    cout << '\n';
}

void demonstrateSeatThreads(Seat& seat) {
    thread t1([&seat]() {
        cout << "\nThread 1 checking seat availability: "
             << (seat.isAvailable() ? "Available" : "Not Available") << '\n';
    });

    thread t2([&seat]() {
        cout << "Thread 2 checking seat number: "
             << seat.getSeatNumber() << '\n';
    });

    t1.join();
    t2.join();
}