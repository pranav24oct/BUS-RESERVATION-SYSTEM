
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <mutex>
#include <thread>

using namespace std;

class ScheduleException : public runtime_error {
public:
    ScheduleException(string message) : runtime_error(message) {}
};

class ScheduleValidationException : public ScheduleException {
public:
    ScheduleValidationException(string message)
        : ScheduleException(message) {}
};

class ScheduleProcessingException : public ScheduleValidationException {
public:
    ScheduleProcessingException(string message)
        : ScheduleValidationException(message) {}
};

class ScheduleInterface {
public:
    virtual void displaySchedule() const = 0;
    virtual ~ScheduleInterface() = default;
};

class ScheduleInfo : virtual public ScheduleInterface {
public:
    virtual ~ScheduleInfo() = default;
};

class ScheduleAudit : virtual public ScheduleInterface {
public:
    virtual ~ScheduleAudit() = default;
};

class ScheduleSummary {
public:
    int scheduleId;
    string date;
    string departureTime;
    string arrivalTime;

    ScheduleSummary()
        : scheduleId(0), date(""), departureTime(""), arrivalTime("") {}

    ScheduleSummary(int id, string d, string departure, string arrival)
        : scheduleId(id), date(d),
          departureTime(departure), arrivalTime(arrival) {}
};

class Schedule : public ScheduleInfo, public ScheduleAudit {
private:
    int scheduleId;
    string departureTime;
    string arrivalTime;
    string date;

    static int scheduleCount;
    static mutex scheduleMutex;

public:
    class TimeRange {
    private:
        string startTime;
        string endTime;

    public:
        TimeRange(string start, string end)
            : startTime(start), endTime(end) {}

        void display() const {
            cout << "Time range: " << startTime
                 << " - " << endTime << '\n';
        }
    };

    Schedule();
    Schedule(int id, string departure, string arrival, string date);
    Schedule(int id);
    Schedule(const Schedule& other);
    virtual ~Schedule() override;

    void setSchedule(string departure, string arrival);
    void setSchedule(string departure, string arrival, string date);

    void displaySchedule() const override;

    int getScheduleId() const;
    string getDepartureTime() const;
    string getArrivalTime() const;
    string getDate() const;

    static int getScheduleCount();

    Schedule& operator=(const Schedule& other);

    operator int() const;
    operator ScheduleSummary() const;

    friend ostream& operator<<(ostream& out, const Schedule& s);

    friend bool isSameScheduleDate(
        const Schedule& s1, const Schedule& s2
    );

    friend class ScheduleInspector;
};

class ScheduleInspector {
public:
    static void showPrivateData(const Schedule& s);
};

template <typename T>
T getLargerSchedule(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
class ScheduleStorage {
private:
    T data;

public:
    ScheduleStorage(T value) : data(value) {}

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

class ScheduleRecord {
public:
    int recordId;

    ScheduleRecord(int id = 0) : recordId(id) {}

    virtual void displayRecord() const {
        cout << "Base ScheduleRecord ID: " << recordId << '\n';
    }

    virtual ~ScheduleRecord() = default;
};

class ExpressScheduleRecord : public ScheduleRecord {
public:
    string expressName;

    ExpressScheduleRecord(int id, string name)
        : ScheduleRecord(id), expressName(name) {}

    void displayRecord() const override {
        cout << "Express Schedule ID: " << recordId << '\n';
        cout << "Express name: " << expressName << '\n';
    }
};

void demonstrateScheduleThreads(Schedule& schedule);

#endif
