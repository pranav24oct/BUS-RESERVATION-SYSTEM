#include "Schedule.h"

Schedule::Schedule()
{
    scheduleId = 0;
    departureTime = "Unknown";
    arrivalTime = "Unknown";
    date = "Unknown";
}

Schedule::Schedule(int id, string departure, string arrival, string date)
{
    scheduleId = id;
    departureTime = departure;
    arrivalTime = arrival;
    this->date = date;
}

Schedule::~Schedule()
{
    cout << "Schedule object destroyed." << endl;
}

void Schedule::setSchedule(string departure, string arrival)
{
    departureTime = departure;
    arrivalTime = arrival;
}

void Schedule::setSchedule(string departure, string arrival, string date)
{
    departureTime = departure;
    arrivalTime = arrival;
    this->date = date;
}

void Schedule::displaySchedule()
{
    cout << "\n========== SCHEDULE ==========" << endl;
    cout << "Schedule ID : " << scheduleId << endl;
    cout << "Date        : " << date << endl;
    cout << "Departure   : " << departureTime << endl;
    cout << "Arrival     : " << arrivalTime << endl;
    cout << "==============================" << endl;
}

Schedule& Schedule::operator=(const Schedule& other)
{
    if (this != &other)
    {
        scheduleId = other.scheduleId;
        departureTime = other.departureTime;
        arrivalTime = other.arrivalTime;
        date = other.date;
    }

    return *this;
}
