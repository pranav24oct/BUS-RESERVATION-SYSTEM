#include "Passenger.h"

// ================= USER =================

User::User()
{
    userId = 0;
    name = "Unknown";
    phone = "Unknown";
}

User::User(int userId, string name, string phone)
{
    this->userId = userId;
    this->name = name;
    this->phone = phone;
}

User::~User()
{
    cout << "User object destroyed." << endl;
}

string User::getName()
{
    return name;
}

void User::displayUser()
{
    cout << "User ID : " << userId << endl;
    cout << "Name    : " << name << endl;
    cout << "Phone   : " << phone << endl;
}


// ================= PASSENGER =================

Passenger::Passenger()
    : User(0, "Unknown", "Unknown")
{
    email = "Unknown";
}

Passenger::Passenger(
    int userId,
    string name,
    string phone,
    string email)
    : User(userId, name, phone)
{
    this->email = email;
}

Passenger::~Passenger()
{
    cout << "Passenger object destroyed." << endl;
}

string Passenger::getEmail()
{
    return email;
}

void Passenger::setEmail(string email)
{
    this->email = email;
}

void Passenger::displayRole()
{
    cout << "Role : Passenger" << endl;
}

void Passenger::searchBus()
{
    cout << getName() << " is searching for a bus." << endl;
}

void Passenger::viewBookings()
{
    cout << getName() << " is viewing bookings." << endl;
}

void Passenger::cancelBooking()
{
    cout << getName() << " is cancelling a booking." << endl;
}

void Passenger::displayPassenger()
{
    cout << "\n========== PASSENGER ==========" << endl;

    displayUser();
    displayRole();

    cout << "Email : " << email << endl;

    cout << "===============================" << endl;
}


// ================= FRIEND OPERATOR =================

bool operator==(const Passenger& p1,
                const Passenger& p2)
{
    return p1.userId == p2.userId;
}
