
#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <mutex>
#include <thread>

using namespace std;

class PassengerException : public runtime_error {
public:
    PassengerException(const string& message)
        : runtime_error(message) {}
};

class PassengerValidationException : public PassengerException {
public:
    PassengerValidationException(const string& message)
        : PassengerException(message) {}
};

class InvalidPassengerId : public PassengerValidationException {
public:
    InvalidPassengerId()
        : PassengerValidationException("Passenger ID must be positive.") {}
};

class InvalidPassengerEmail : public PassengerValidationException {
public:
    InvalidPassengerEmail()
        : PassengerValidationException("Email cannot be empty.") {}
};

class PassengerProcessingException : public PassengerException {
public:
    PassengerProcessingException(const string& message)
        : PassengerException(message) {}
};

class PassengerSummary {
public:
    int userId;
    string name;

    PassengerSummary();
    PassengerSummary(int id, string passengerName);
};

class User {
protected:
    int userId;
    string name;
    string phone;

public:
    User();
    User(int userId, string name, string phone);
    virtual ~User();

    int getUserId() const;
    string getName() const;

    void displayUser() const;

    virtual void displayRole() const = 0;
};

class Passenger : public User {
private:
    string email;

    static int passengerCount;
    static mutex passengerMutex;

public:
    class PassengerDetails {
    public:
        string bookingStatus;
        int totalBookings;

        PassengerDetails();
        PassengerDetails(string status, int bookings);
    };

    Passenger();
    Passenger(int userId, string name, string phone, string email);
    Passenger(int userId);

    Passenger(const Passenger& other);

    ~Passenger() override;

    void setEmail(string email);
    string getEmail() const;

    void displayPassenger() const;
    void displayPassenger(bool showPhone) const;

    void displayRole() const override;

    void searchBus() const;
    void viewBookings() const;
    void cancelBooking() const;

    void displayUsingPointer() const;

    operator int() const;
    operator PassengerSummary() const;

    Passenger& operator=(const Passenger& other);

    friend bool operator==(const Passenger& p1, const Passenger& p2);
    friend ostream& operator<<(ostream& out, const Passenger& p);

    static int getPassengerCount();

    void runPassengerTasks();
};

template <typename T>
T getLargerPassenger(T a, T b) {
    return (a > b) ? a : b;
}

template <class T>
class PassengerStorage {
private:
    T data;

public:
    PassengerStorage(T value) : data(value) {}

    void setData(T value) {
        data = value;
    }

    T getData() const {
        return data;
    }
};

void demonstratePassengerThreads(Passenger& passenger);

#endif
