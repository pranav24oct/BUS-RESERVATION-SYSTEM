

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

// Operator Overloading
// == compares two Passenger objects
bool Passenger::operator==(const Passenger& other)
{
    return userId == other.userId;
}
