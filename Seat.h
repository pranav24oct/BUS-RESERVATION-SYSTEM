#ifndef SEAT_H
#define SEAT_H

#include <iostream>
#include <string>
#include <mutex>
#include <stdexcept>

using namespace std;

enum class SeatStatus {
    Available,
    Held,
    Reserved
};

class SeatException : public runtime_error {
public:
    explicit SeatException(const string& message);
};

class SeatValidationException : public SeatException {
public:
    explicit SeatValidationException(const string& message);
};

class InvalidSeatId : public SeatValidationException {
public:
    explicit InvalidSeatId(const string& message);
};

class SeatProcessingException : public SeatException {
public:
    explicit SeatProcessingException(const string& message);
};

class SeatInterface {
public:
    virtual void displaySeat() const = 0;
    virtual ~SeatInterface() = default;
};

struct SeatSummary {
    int seatId;
    int seatNumber;
    SeatStatus status;
};

class Seat : public virtual SeatInterface {
private:
    int seatId;
    int seatNumber;
    SeatStatus status;

    static int seatCount;
    static mutex seatMutex;

public:
    class SeatDetails {
    public:
        int seatId;
        int seatNumber;
        string description;

        SeatDetails();
        SeatDetails(int id, int number, string description);
        void display() const;
    };

    Seat();
    Seat(int id, int number);
    Seat(int id);
    Seat(const Seat& other);
    virtual ~Seat();

    void hold();
    void reserve();
    void release();

    bool isAvailable() const;
    void setStatus(SeatStatus newStatus);

    int getSeatId() const;
    int getSeatNumber() const;
    SeatStatus getStatus() const;

    void displaySeat() const override;
    static int getSeatCount();

    Seat& operator=(const Seat& other);
    operator int() const;
    operator SeatSummary() const;

    friend ostream& operator<<(ostream& out, const Seat& seat);
    friend bool operator==(const Seat& first, const Seat& second);
    friend class SeatAdmin;
};

class SeatAdmin {
public:
    static void displaySeatDetails(const Seat& seat);
};

template <typename T>
T getLargerSeat(T first, T second) {
    return (first > second) ? first : second;
}

template <typename T>
class SeatStorage {
private:
    T data;

public:
    SeatStorage() : data() {}
    explicit SeatStorage(T value) : data(value) {}

    void setData(T value) {
        data = value;
    }

    T getData() const {
        return data;
    }

    void displayData() const {
        cout << "Stored Seat Data: " << data << '\n';
    }
};

void demonstrateSeatThreads(Seat& seat);

#endif