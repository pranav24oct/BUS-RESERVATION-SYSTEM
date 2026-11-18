
#include "Schedule.h"

int Schedule::scheduleCount = 0;
mutex Schedule::scheduleMutex;

Schedule::Schedule()
    : scheduleId(0), departureTime(""),
      arrivalTime(""), date("") {

    lock_guard<mutex> lock(scheduleMutex);
    ++scheduleCount;
}

Schedule::Schedule(int id, string departure,
                   string arrival, string date)
    : scheduleId(id), departureTime(departure),
      arrivalTime(arrival), date(date) {

    lock_guard<mutex> lock(scheduleMutex);
    ++scheduleCount;
}

Schedule::Schedule(int id)
    : scheduleId(id), departureTime("Not set"),
      arrivalTime("Not set"), date("Not set") {

    lock_guard<mutex> lock(scheduleMutex);
    ++scheduleCount;
}

Schedule::Schedule(const Schedule& other) {
    lock_guard<mutex> lock(scheduleMutex);

    scheduleId = other.scheduleId;
    departureTime = other.departureTime;
    arrivalTime = other.arrivalTime;
    date = other.date;

    ++scheduleCount;
}

Schedule::~Schedule() {
    lock_guard<mutex> lock(scheduleMutex);
    --scheduleCount;
}

void Schedule::setSchedule(string departure, string arrival) {
    lock_guard<mutex> lock(scheduleMutex);

    if (departure.empty() || arrival.empty()) {
        throw ScheduleValidationException("Departure and arrival cannot be empty.");
    }

    if (departure == arrival) {
        throw ScheduleProcessingException("Departure and arrival cannot be the same.");
    }

    departureTime = departure;
    arrivalTime = arrival;
}

void Schedule::setSchedule(string departure, string arrival,
                           string date) {
    lock_guard<mutex> lock(scheduleMutex);

    if (departure.empty() || arrival.empty() || date.empty()) {
        throw ScheduleValidationException("Invalid schedule details.");
    }

    if (departure == arrival) {
        throw ScheduleProcessingException("Departure and arrival cannot be the same.");
    }

    departureTime = departure;
    arrivalTime = arrival;
    this->date = date;
}

void Schedule::displaySchedule() const {
    lock_guard<mutex> lock(scheduleMutex);

    cout << "Schedule ID: " << scheduleId << '\n';
    cout << "Departure: " << departureTime << '\n';
    cout << "Arrival: " << arrivalTime << '\n';
    cout << "Date: " << date << '\n';
}

int Schedule::getScheduleId() const {
    lock_guard<mutex> lock(scheduleMutex);
    return scheduleId;
}

string Schedule::getDepartureTime() const {
    lock_guard<mutex> lock(scheduleMutex);
    return departureTime;
}

string Schedule::getArrivalTime() const {
    lock_guard<mutex> lock(scheduleMutex);
    return arrivalTime;
}

string Schedule::getDate() const {
    lock_guard<mutex> lock(scheduleMutex);
    return date;
}

int Schedule::getScheduleCount() {
    lock_guard<mutex> lock(scheduleMutex);
    return scheduleCount;
}

Schedule& Schedule::operator=(const Schedule& other) {
    if (this != &other) {
        lock_guard<mutex> lock(scheduleMutex);

        scheduleId = other.scheduleId;
        departureTime = other.departureTime;
        arrivalTime = other.arrivalTime;
        date = other.date;
    }

    return *this;
}

Schedule::operator int() const {
    lock_guard<mutex> lock(scheduleMutex);
    return scheduleId;
}

Schedule::operator ScheduleSummary() const {
    lock_guard<mutex> lock(scheduleMutex);

    return ScheduleSummary(
        scheduleId, date, departureTime, arrivalTime
    );
}

ostream& operator<<(ostream& out, const Schedule& s) {
    lock_guard<mutex> lock(Schedule::scheduleMutex);

    out << "Schedule ID: " << s.scheduleId
        << "\nDeparture: " << s.departureTime
        << "\nArrival: " << s.arrivalTime
        << "\nDate: " << s.date;

    return out;
}

bool isSameScheduleDate(const Schedule& s1, const Schedule& s2) {
    lock_guard<mutex> lock(Schedule::scheduleMutex);
    return s1.date == s2.date;
}

void ScheduleInspector::showPrivateData(const Schedule& s) {
    lock_guard<mutex> lock(Schedule::scheduleMutex);

    cout << "Inspector - Schedule ID: " << s.scheduleId << '\n';
    cout << "Inspector - Date: " << s.date << '\n';
}

void demonstrateScheduleThreads(Schedule& schedule) {
    auto task = [&schedule]() {
        try {
            schedule.displaySchedule();
        }
        catch (const ScheduleException& e) {
            cout << "Schedule error: " << e.what() << '\n';
        }
    };

    thread t1(task);
    thread t2(task);

    t1.join();
    t2.join();
}
