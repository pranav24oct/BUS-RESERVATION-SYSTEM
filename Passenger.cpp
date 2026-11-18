
#include "Passenger.h"
#include <chrono>

using namespace std;

int Passenger::passengerCount = 0;
mutex Passenger::passengerMutex;

PassengerSummary::PassengerSummary()
    : userId(0), name("Unknown") {}

PassengerSummary::PassengerSummary(int id, string passengerName)
    : userId(id), name(passengerName) {}

Passenger::PassengerDetails::PassengerDetails()
    : bookingStatus("No bookings"), totalBookings(0) {}

Passenger::PassengerDetails::PassengerDetails(string status, int bookings)
    : bookingStatus(status), totalBookings(bookings) {}

User::User()
    : userId(0), name("Unknown"), phone("Unknown") {}

User::User(int userId, string name, string phone)
    : userId(userId), name(name), phone(phone) {

    if (userId <= 0) {
        throw InvalidPassengerId();
    }

    if (name.empty()) {
        throw PassengerValidationException("Name cannot be empty.");
    }

    if (phone.empty()) {
        throw PassengerValidationException("Phone cannot be empty.");
    }
}

User::~User() {
    cout << "User object destroyed.\n";
}

int User::getUserId() const {
    lock_guard<mutex> lock(Passenger::passengerMutex);
    return userId;
}

string User::getName() const {
    lock_guard<mutex> lock(Passenger::passengerMutex);
    return name;
}

void User::displayUser() const {
    lock_guard<mutex> lock(Passenger::passengerMutex);

    cout << "User ID: " << userId << '\n';
    cout << "Name: " << name << '\n';
    cout << "Phone: " << phone << '\n';
}

Passenger::Passenger()
    : User(), email("Not provided") {
    lock_guard<mutex> lock(passengerMutex);
    ++passengerCount;
}

Passenger::Passenger(int userId, string name, string phone, string email)
    : User(userId, name, phone), email(email) {

    if (email.empty()) {
        throw InvalidPassengerEmail();
    }

    lock_guard<mutex> lock(passengerMutex);
    ++passengerCount;
}

Passenger::Passenger(int userId)
    : User(userId, "Unknown", "Unknown"), email("Not provided") {
    lock_guard<mutex> lock(passengerMutex);
    ++passengerCount;
}

Passenger::Passenger(const Passenger& other)
    : User(), email("Not provided") {

    lock_guard<mutex> lock(passengerMutex);

    userId = other.userId;
    name = other.name;
    phone = other.phone;
    email = other.email;

    ++passengerCount;
}

Passenger::~Passenger() {
    lock_guard<mutex> lock(passengerMutex);
    --passengerCount;
    cout << "Passenger object destroyed.\n";
}

void Passenger::setEmail(string email) {
    if (email.empty()) {
        throw InvalidPassengerEmail();
    }

    lock_guard<mutex> lock(passengerMutex);
    this->email = email;
}

string Passenger::getEmail() const {
    lock_guard<mutex> lock(passengerMutex);
    return email;
}

void Passenger::displayPassenger() const {
    lock_guard<mutex> lock(passengerMutex);

    cout << "User ID: " << userId << '\n';
    cout << "Name: " << name << '\n';
    cout << "Phone: " << phone << '\n';
    cout << "Email: " << email << '\n';
}

void Passenger::displayPassenger(bool showPhone) const {
    lock_guard<mutex> lock(passengerMutex);

    cout << "User ID: " << userId << '\n';
    cout << "Name: " << name << '\n';
    cout << "Email: " << email << '\n';

    if (showPhone) {
        cout << "Phone: " << phone << '\n';
    }
}

void Passenger::displayRole() const {
    lock_guard<mutex> lock(passengerMutex);
    cout << "Role: Passenger\n";
}

void Passenger::searchBus() const {
    lock_guard<mutex> lock(passengerMutex);
    cout << name << " is searching for buses.\n";
}

void Passenger::viewBookings() const {
    lock_guard<mutex> lock(passengerMutex);
    cout << name << " is viewing bookings.\n";
}

void Passenger::cancelBooking() const {
    lock_guard<mutex> lock(passengerMutex);
    cout << name << " is cancelling a booking.\n";
}

void Passenger::displayUsingPointer() const {
    lock_guard<mutex> lock(passengerMutex);

    const Passenger* ptr = this;

    cout << "Displaying details using object pointer:\n";
    cout << "User ID: " << ptr->userId << '\n';
    cout << "Name: " << ptr->name << '\n';
    cout << "Phone: " << ptr->phone << '\n';
    cout << "Email: " << ptr->email << '\n';
}

Passenger::operator int() const {
    lock_guard<mutex> lock(passengerMutex);
    return userId;
}

Passenger::operator PassengerSummary() const {
    lock_guard<mutex> lock(passengerMutex);
    return PassengerSummary(userId, name);
}

Passenger& Passenger::operator=(const Passenger& other) {
    if (this == &other) {
        return *this;
    }

    lock_guard<mutex> lock(passengerMutex);

    userId = other.userId;
    name = other.name;
    phone = other.phone;
    email = other.email;

    return *this;
}

bool operator==(const Passenger& p1, const Passenger& p2) {
    lock_guard<mutex> lock(Passenger::passengerMutex);
    return p1.userId == p2.userId;
}

ostream& operator<<(ostream& out, const Passenger& p) {
    lock_guard<mutex> lock(Passenger::passengerMutex);

    out << "Passenger ID: " << p.userId << '\n';
    out << "Name: " << p.name << '\n';
    out << "Phone: " << p.phone << '\n';
    out << "Email: " << p.email << '\n';

    return out;
}

int Passenger::getPassengerCount() {
    lock_guard<mutex> lock(passengerMutex);
    return passengerCount;
}

void Passenger::runPassengerTasks() {
    cout << "\nStarting Passenger Multithreading...\n";

    thread t1([this]() {
        searchBus();
        this_thread::sleep_for(chrono::seconds(1));
        this_thread::yield();
    });

    thread t2([this]() {
        viewBookings();
        this_thread::sleep_for(chrono::seconds(1));
        this_thread::yield();
    });

    thread t3([this]() {
        cancelBooking();
        this_thread::sleep_for(chrono::seconds(1));
        this_thread::yield();
    });

    t1.join();
    t2.join();
    t3.join();

    cout << "All Passenger Threads Completed!\n";
}

void demonstratePassengerThreads(Passenger& passenger) {
    thread t1(&Passenger::searchBus, &passenger);
    thread t2(&Passenger::viewBookings, &passenger);
    thread t3(&Passenger::cancelBooking, &passenger);

    t1.join();
    t2.join();
    t3.join();
}
