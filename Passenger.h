#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
using namespace std;

class User
{
protected:
    int userId;
    string name;
    string phone;

public:
    User();
    User(int userId, string name, string phone);
    ~User();

    string getName();
    void displayUser();
};


class Passenger : public User
{
private:
    string email;

public:
    
    Passenger();
    Passenger(int userId, string name, string phone, string email);

    ~Passenger();


    string getEmail();
    void setEmail(string email);

    void displayRole();
    void searchBus();
    void viewBookings();
    void cancelBooking();
    void displayPassenger();

    friend bool operator==(const Passenger& p1,
                           const Passenger& p2);
};

#endif
