#include "Reservation.h"
#include <thread>
#include <sstream>

int Reservation::reservationCount = 0;
mutex Reservation::reservationMutex;

ReservationException::ReservationException(const string& message)
    : runtime_error(message) {}

ReservationValidationException::ReservationValidationException(
    const string& message
) : ReservationException(message) {}

InvalidReservationId::InvalidReservationId(const string& message)
    : ReservationValidationException(message) {}

ReservationProcessingException::ReservationProcessingException(
    const string& message
) : ReservationException(message) {}

Reservation::ReservationDetails::ReservationDetails()
    : reservationId(0),
      bookingReference("N/A"),
      description("No details") {}

Reservation::ReservationDetails::ReservationDetails(
    int id,
    string reference,
    string description
) : reservationId(id),
    bookingReference(reference),
    description(description) {}

void Reservation::ReservationDetails::display() const {
    cout << "Reservation ID: " << reservationId << '\n';
    cout << "Booking Reference: " << bookingReference << '\n';
    cout << "Description: " << description << '\n';
}

Reservation::Reservation()
    : reservationId(0),
      passengerId(0),
      tripId(0),
      seatId(0),
      paymentId(0),
      refundId(0),
      status("Not Created"),
      totalFare(0.0) {

    lock_guard<mutex> lock(reservationMutex);
    ++reservationCount;
}

Reservation::Reservation(
    int id,
    int passenger,
    int trip,
    int seat,
    string date,
    double fare
) : reservationId(id),
    passengerId(passenger),
    tripId(trip),
    seatId(seat),
    paymentId(0),
    refundId(0),
    bookingDate(date),
    status("Pending"),
    totalFare(fare) {

    if (id <= 0 || passenger <= 0 || trip <= 0 || seat <= 0) {
        throw InvalidReservationId(
            "Reservation, passenger, trip and seat IDs must be positive."
        );
    }

    if (date.empty() || fare <= 0) {
        throw ReservationValidationException(
            "Booking date and fare must be valid."
        );
    }

    bookingReference = generateBookingReference();

    lock_guard<mutex> lock(reservationMutex);
    ++reservationCount;
}

Reservation::Reservation(int id)
    : reservationId(id),
      passengerId(0),
      tripId(0),
      seatId(0),
      paymentId(0),
      refundId(0),
      status("Pending"),
      totalFare(0.0) {

    if (id <= 0) {
        throw InvalidReservationId("Reservation ID must be positive.");
    }

    bookingReference = generateBookingReference();

    lock_guard<mutex> lock(reservationMutex);
    ++reservationCount;
}

Reservation::Reservation(const Reservation& other) {
    lock_guard<mutex> lock(reservationMutex);

    reservationId = other.reservationId;
    passengerId = other.passengerId;
    tripId = other.tripId;
    seatId = other.seatId;
    paymentId = other.paymentId;
    refundId = other.refundId;
    bookingReference = other.bookingReference;
    bookingDate = other.bookingDate;
    status = other.status;
    totalFare = other.totalFare;

    ++reservationCount;
}

Reservation::~Reservation() {
    lock_guard<mutex> lock(reservationMutex);
    --reservationCount;
}

string Reservation::generateBookingReference() const {
    return "BUS-" + to_string(reservationId) + "-" +
           to_string(passengerId);
}

void Reservation::createReservation() {
    lock_guard<mutex> lock(reservationMutex);

    if (reservationId <= 0 || passengerId <= 0 ||
        tripId <= 0 || seatId <= 0) {
        throw ReservationValidationException(
            "Reservation details are incomplete."
        );
    }

    if (totalFare <= 0 || bookingDate.empty()) {
        throw ReservationValidationException(
            "Invalid booking date or fare."
        );
    }

    bookingReference = generateBookingReference();
    status = "Pending";
}

void Reservation::confirm() {
    lock_guard<mutex> lock(reservationMutex);

    if (status == "Confirmed") {
        throw ReservationProcessingException(
            "Reservation is already confirmed."
        );
    }

    if (status == "Cancelled") {
        throw ReservationProcessingException(
            "Cancelled reservation cannot be confirmed."
        );
    }

    status = "Confirmed";
}

void Reservation::cancel() {
    lock_guard<mutex> lock(reservationMutex);

    if (status == "Cancelled") {
        throw ReservationProcessingException(
            "Reservation is already cancelled."
        );
    }

    status = "Cancelled";
}

double Reservation::calculateFare(double baseFare) const {
    if (baseFare <= 0) {
        throw ReservationValidationException(
            "Base fare must be greater than zero."
        );
    }

    return baseFare;
}

double Reservation::calculateFare(
    double baseFare,
    int numberOfSeats
) const {
    if (baseFare <= 0 || numberOfSeats <= 0) {
        throw ReservationValidationException(
            "Invalid fare or number of seats."
        );
    }

    return baseFare * numberOfSeats;
}

void Reservation::setPaymentId(int id) {
    if (id <= 0) {
        throw ReservationValidationException("Invalid payment ID.");
    }

    lock_guard<mutex> lock(reservationMutex);
    paymentId = id;
}

void Reservation::setRefundId(int id) {
    if (id <= 0) {
        throw ReservationValidationException("Invalid refund ID.");
    }

    lock_guard<mutex> lock(reservationMutex);
    refundId = id;
}

int Reservation::getReservationId() const {
    lock_guard<mutex> lock(reservationMutex);
    return reservationId;
}

int Reservation::getPassengerId() const {
    lock_guard<mutex> lock(reservationMutex);
    return passengerId;
}

int Reservation::getTripId() const {
    lock_guard<mutex> lock(reservationMutex);
    return tripId;
}

int Reservation::getSeatId() const {
    lock_guard<mutex> lock(reservationMutex);
    return seatId;
}

int Reservation::getPaymentId() const {
    lock_guard<mutex> lock(reservationMutex);
    return paymentId;
}

int Reservation::getRefundId() const {
    lock_guard<mutex> lock(reservationMutex);
    return refundId;
}

string Reservation::getBookingReference() const {
    lock_guard<mutex> lock(reservationMutex);
    return bookingReference;
}

string Reservation::getBookingDate() const {
    lock_guard<mutex> lock(reservationMutex);
    return bookingDate;
}

string Reservation::getStatus() const {
    lock_guard<mutex> lock(reservationMutex);
    return status;
}

double Reservation::getTotalFare() const {
    lock_guard<mutex> lock(reservationMutex);
    return totalFare;
}

void Reservation::displayReservation() const {
    lock_guard<mutex> lock(reservationMutex);

    cout << "\n--- Reservation Details ---\n";
    cout << "Reservation ID: " << reservationId << '\n';
    cout << "Passenger ID: " << passengerId << '\n';
    cout << "Trip ID: " << tripId << '\n';
    cout << "Seat ID: " << seatId << '\n';
    cout << "Booking Reference: " << bookingReference << '\n';
    cout << "Booking Date: " << bookingDate << '\n';
    cout << "Status: " << status << '\n';
    cout << "Total Fare: Rs. " << totalFare << '\n';
    cout << "Payment ID: " << paymentId << '\n';
    cout << "Refund ID: " << refundId << '\n';
}

int Reservation::getReservationCount() {
    lock_guard<mutex> lock(reservationMutex);
    return reservationCount;
}

Reservation& Reservation::operator=(const Reservation& other) {
    if (this != &other) {
        scoped_lock lock(reservationMutex);

        reservationId = other.reservationId;
        passengerId = other.passengerId;
        tripId = other.tripId;
        seatId = other.seatId;
        paymentId = other.paymentId;
        refundId = other.refundId;
        bookingReference = other.bookingReference;
        bookingDate = other.bookingDate;
        status = other.status;
        totalFare = other.totalFare;
    }

    return *this;
}

Reservation::operator int() const {
    return getReservationId();
}

Reservation::operator double() const {
    return getTotalFare();
}

Reservation::operator ReservationSummary() const {
    lock_guard<mutex> lock(reservationMutex);

    return {
        reservationId,
        passengerId,
        tripId,
        seatId,
        bookingReference,
        status,
        totalFare
    };
}

ostream& operator<<(ostream& out, const Reservation& reservation) {
    lock_guard<mutex> lock(Reservation::reservationMutex);

    out << "Reservation ID: " << reservation.reservationId
        << "\nPassenger ID: " << reservation.passengerId
        << "\nTrip ID: " << reservation.tripId
        << "\nSeat ID: " << reservation.seatId
        << "\nBooking Reference: " << reservation.bookingReference
        << "\nStatus: " << reservation.status
        << "\nTotal Fare: Rs. " << reservation.totalFare;

    return out;
}

bool operator==(
    const Reservation& first,
    const Reservation& second
) {
    if (&first == &second) {
        return true;
    }

    scoped_lock lock(Reservation::reservationMutex);

    return first.reservationId == second.reservationId;
}

void ReservationAdmin::displayReservationDetails(
    const Reservation& reservation
) {
    lock_guard<mutex> lock(Reservation::reservationMutex);

    cout << "\n--- Reservation Admin Details ---\n";
    cout << "Reservation ID: " << reservation.reservationId << '\n';
    cout << "Passenger ID: " << reservation.passengerId << '\n';
    cout << "Trip ID: " << reservation.tripId << '\n';
    cout << "Seat ID: " << reservation.seatId << '\n';
    cout << "Payment ID: " << reservation.paymentId << '\n';
    cout << "Refund ID: " << reservation.refundId << '\n';
    cout << "Booking Reference: "
         << reservation.bookingReference << '\n';
    cout << "Status: " << reservation.status << '\n';
}

void ReservationRecord::displayRecord() const {
    cout << "General Reservation Record\n";
}

void ConfirmedReservationRecord::displayRecord() const {
    cout << "Confirmed Reservation Record\n";
}

void demonstrateReservationThreads(Reservation& reservation) {
    thread t1([&reservation]() {
        cout << "\nThread 1 - Reservation ID: "
             << reservation.getReservationId() << '\n';
    });

    thread t2([&reservation]() {
        cout << "Thread 2 - Booking Status: "
             << reservation.getStatus() << '\n';
    });

    t1.join();
    t2.join();
}