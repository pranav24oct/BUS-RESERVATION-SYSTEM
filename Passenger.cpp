class User
{
protected:
    int userId;
    string name;
    string phone;

public:


    User()
    {
        userId = 0;
        name = "Unknown";
        phone = "Unknown";
    }

    User(int userId, string name, string phone)
    {
        this->userId = userId;
        this->name = name;
        this->phone = phone;
    }

    ~User()
    {
        cout << "User object destroyed." << endl;
    }

    string getName()
    {
        return name;
    }

    void displayUser()
    {
        cout << "User ID : " << userId << endl;
        cout << "Name    : " << name << endl;
        cout << "Phone   : " << phone << endl;
    }
};


class Passenger : public User
{
private:
    string email;

public:

    Passenger()
        : User(0, "Unknown", "Unknown")
    {
        email = "Unknown";
    }

    Passenger(
        int userId,
        string name,
        string phone,
        string email)
        : User(userId, name, phone)
    {
        this->email = email;
    }

    ~Passenger()
    {
        cout << "Passenger object destroyed." << endl;
    }

    string getEmail()
    {
        return email;
    }

    void setEmail(string email)
    {
        this->email = email;
    }

    void displayRole()
    {
        cout << "Role : Passenger" << endl;
    }

    void searchBus()
    {
        cout << getName() << " is searching for a bus." << endl;
    }

    void viewBookings()
    {
        cout << getName() << " is viewing bookings." << endl;
    }

    void cancelBooking()
    {
        cout << getName() << " is cancelling a booking." << endl;
    }

    void displayPassenger()
    {
        cout << "\n========== PASSENGER ==========" << endl;

        displayUser();
        displayRole();

        cout << "Email : " << email << endl;

        cout << "===============================" << endl;
    }


    friend bool operator==(const Passenger& p1,
                           const Passenger& p2);
};


bool operator==(const Passenger& p1,
                const Passenger& p2)
{
    return p1.userId == p2.userId;
}
