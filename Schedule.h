#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <string>

using namespace std;

class Schedule
{
private:
    int scheduleId;
    string departureTime;
    string arrivalTime;
    string date;

public:
    Schedule();
    Schedule(int id, string departure, string arrival, string date);
    ~Schedule();

    void displaySchedule();

    // Function overloading
    void setSchedule(string departure, string arrival);
    void setSchedule(string departure, string arrival, string date);

    Schedule& operator=(const Schedule& other);
};

#endif
