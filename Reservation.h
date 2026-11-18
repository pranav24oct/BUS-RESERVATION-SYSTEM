#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <string>
#include <mutex>
#include <stdexcept>

using namespace std;

class ReservationException : public runtime_error {
public:
    explicit ReservationException(const string& message);
};

class ReservationValidationException : public ReservationException {
public:
    explicit ReservationValidationException(const string& message);
};

class InvalidReservationId : public ReservationValidationException {
public:
    explicit InvalidReservationId(const string& message);
};

class ReservationProcessingException : public ReservationException {
public:
    explicit ReservationProcessingException(const string& message);
};

class ReservationInterface {
public:
    virtual void displayReservation() const = 0;
    virtual ~ReservationInterface() = default;
};

struct ReservationSummary {
    int reservationId;
    int passengerId;
    int tripId;
    int seatId;
    string bookingReference;
    string status;
    double totalFare;
};

class Reservation : public virtual ReservationInterface {
private:
    int reservationId;
    int passengerId;
    int tripId;
    int seatId;
    int paymentId;
    int refundId;

    string bookingReference;
    string bookingDate;
    string status;
    double totalFare;

    static int reservationCount;
    static mutex reservationMutex;

    string generateBookingReference() const;

public:
    class ReservationDetails {
    public:
        int reservationId;
        string bookingReference;
        string description;

        ReservationDetails();
        ReservationDetails(int id, string reference, string description);
        void display() const;
    };

    Reservation();
    Reservation(
        int reservationId,
        int passengerId,
        int tripId,
        int seatId,
        string bookingDate,
        double totalFare
    );
    Reservation(int id);
    Reservation(const Reservation& other);
    virtual ~Reservation();

    void createReservation();
    void confirm();
    void cancel();

    double calculateFare(double baseFare) const;
    double calculateFare(double baseFare, int numberOfSeats) const;

    void setPaymentId(int id);
    void setRefundId(int id);

    int getReservationId() const;
    int getPassengerId() const;
    int getTripId() const;
    int getSeatId() const;
    int getPaymentId() const;
    int getRefundId() const;

    string getBookingReference() const;
    string getBookingDate() const;
    string getStatus() const;
    double getTotalFare() const;

    void displayReservation() const;
    static int getReservationCount();

    Reservation& operator=(const Reservation& other);
    operator int() const;
    operator double() const;
    operator ReservationSummary() const;

    friend ostream& operator<<(ostream& out, const Reservation& reservation);
    friend bool operator==(const Reservation& first, const Reservation& second);
    friend class ReservationAdmin;
};

class ReservationAdmin {
public:
    static void displayReservationDetails(const Reservation& reservation);
};

class ReservationRecord {
public:
    virtual void displayRecord() const;
    virtual ~ReservationRecord() = default;
};

class ConfirmedReservationRecord : public ReservationRecord {
public:
    void displayRecord() const override;
};

template <typename T>
T getLargerReservation(T first, T second) {
    return (first > second) ? first : second;
}

template <typename T>
class ReservationStorage {
private:
    T data;

public:
    ReservationStorage() : data() {}
    explicit ReservationStorage(T value) : data(value) {}

    void setData(T value) {
        data = value;
    }

    T getData() const {
        return data;
    }

    void displayData() const {
        cout << "Stored Reservation Data: " << data << '\n';
    }
};

void demonstrateReservationThreads(Reservation& reservation);

#endif