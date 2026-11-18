
#include "BusOperator.h"
#include <algorithm>
#include <chrono>

using namespace std;

int BusOperator::operatorCount = 0;
mutex BusOperator::operatorMutex;

BusOperator::OperatorDetails::OperatorDetails()
    : totalBuses(0), status("Inactive") {}

BusOperator::OperatorDetails::OperatorDetails(int buses, string status)
    : totalBuses(buses), status(status) {}

BusOperator::BusOperator()
    : operatorId(0),
      name("Unknown"),
      companyName("Unknown"),
      phone("Unknown") {

    lock_guard<mutex> lock(operatorMutex);
    ++operatorCount;
}

BusOperator::BusOperator(int id, string name, string companyName, string phone)
    : operatorId(id),
      name(name),
      companyName(companyName),
      phone(phone) {

    if (id <= 0) {
        throw InvalidOperatorId();
    }

    if (name.empty() || companyName.empty() || phone.empty()) {
        throw InvalidOperatorDetails("Operator details cannot be empty.");
    }

    lock_guard<mutex> lock(operatorMutex);
    ++operatorCount;
}

BusOperator::BusOperator(const BusOperator& other)
    : operatorId(0),
      name("Unknown"),
      companyName("Unknown"),
      phone("Unknown") {

    lock_guard<mutex> lock(operatorMutex);

    operatorId = other.operatorId;
    name = other.name;
    companyName = other.companyName;
    phone = other.phone;
    managedBusIds = other.managedBusIds;

    ++operatorCount;
}

BusOperator::~BusOperator() {
    lock_guard<mutex> lock(operatorMutex);
    --operatorCount;
}

void BusOperator::setOperator(string name, string phone) {
    if (name.empty() || phone.empty()) {
        throw InvalidOperatorDetails("Name and phone cannot be empty.");
    }

    lock_guard<mutex> lock(operatorMutex);

    this->name = name;
    this->phone = phone;
}

void BusOperator::setOperator(string name, string companyName, string phone) {
    if (name.empty() || companyName.empty() || phone.empty()) {
        throw InvalidOperatorDetails("Operator details cannot be empty.");
    }

    lock_guard<mutex> lock(operatorMutex);

    this->name = name;
    this->companyName = companyName;
    this->phone = phone;
}

void BusOperator::addBus(int busId) {
    if (busId <= 0) {
        throw InvalidOperatorDetails("Bus ID must be positive.");
    }

    lock_guard<mutex> lock(operatorMutex);

    if (find(managedBusIds.begin(), managedBusIds.end(), busId)
        != managedBusIds.end()) {
        throw BusOperatorProcessingException(
            "Bus ID is already assigned to this operator."
        );
    }

    managedBusIds.push_back(busId);

    cout << "Bus " << busId << " assigned to operator "
         << name << ".\n";
}

bool BusOperator::removeBus(int busId) {
    lock_guard<mutex> lock(operatorMutex);

    auto it = find(managedBusIds.begin(),
                   managedBusIds.end(), busId);

    if (it == managedBusIds.end()) {
        return false;
    }

    managedBusIds.erase(it);

    cout << "Bus " << busId << " removed from operator "
         << name << ".\n";

    return true;
}

void BusOperator::displayManagedBuses() const {
    lock_guard<mutex> lock(operatorMutex);

    cout << "Managed Bus IDs: ";

    if (managedBusIds.empty()) {
        cout << "No buses assigned";
    } else {
        for (int busId : managedBusIds) {
            cout << busId << " ";
        }
    }

    cout << '\n';
}

void BusOperator::displayOperator() const {
    lock_guard<mutex> lock(operatorMutex);

    cout << "\n--- Bus Operator Details ---\n";
    cout << "Operator ID: " << operatorId << '\n';
    cout << "Name: " << name << '\n';
    cout << "Company: " << companyName << '\n';
    cout << "Phone: " << phone << '\n';

    cout << "Managed Bus IDs: ";

    if (managedBusIds.empty()) {
        cout << "No buses assigned";
    } else {
        for (int busId : managedBusIds) {
            cout << busId << " ";
        }
    }

    cout << '\n';
}

int BusOperator::getOperatorId() const {
    lock_guard<mutex> lock(operatorMutex);
    return operatorId;
}

string BusOperator::getName() const {
    lock_guard<mutex> lock(operatorMutex);
    return name;
}

string BusOperator::getCompanyName() const {
    lock_guard<mutex> lock(operatorMutex);
    return companyName;
}

string BusOperator::getPhone() const {
    lock_guard<mutex> lock(operatorMutex);
    return phone;
}

int BusOperator::getOperatorCount() {
    lock_guard<mutex> lock(operatorMutex);
    return operatorCount;
}

BusOperator& BusOperator::operator=(const BusOperator& other) {
    if (this == &other) {
        return *this;
    }

    lock_guard<mutex> lock(operatorMutex);

    operatorId = other.operatorId;
    name = other.name;
    companyName = other.companyName;
    phone = other.phone;
    managedBusIds = other.managedBusIds;

    return *this;
}

BusOperator::operator int() const {
    lock_guard<mutex> lock(operatorMutex);
    return operatorId;
}

ostream& operator<<(ostream& out, const BusOperator& op) {
    lock_guard<mutex> lock(BusOperator::operatorMutex);

    out << "Operator ID: " << op.operatorId
        << "\nName: " << op.name
        << "\nCompany: " << op.companyName
        << "\nPhone: " << op.phone;

    return out;
}

bool operator==(const BusOperator& op1, const BusOperator& op2) {
    lock_guard<mutex> lock(BusOperator::operatorMutex);
    return op1.operatorId == op2.operatorId;
}

void BusOperatorAdmin::displayOperatorDetails(const BusOperator& op) {
    lock_guard<mutex> lock(BusOperator::operatorMutex);

    cout << "\n--- Admin View ---\n";
    cout << "Operator ID: " << op.operatorId << '\n';
    cout << "Operator Name: " << op.name << '\n';
    cout << "Company: " << op.companyName << '\n';
    cout << "Phone: " << op.phone << '\n';
    cout << "Managed buses: " << op.managedBusIds.size() << '\n';
}

void BusOperator::runOperatorTasks() {
    cout << "\nStarting Bus Operator Multithreading...\n";

    thread t1([this]() {
        displayOperator();
        this_thread::sleep_for(chrono::seconds(1));
        this_thread::yield();
    });

    thread t2([this]() {
        displayManagedBuses();
        this_thread::sleep_for(chrono::seconds(1));
        this_thread::yield();
    });

    thread t3([this]() {
        cout << "Operator ID: " << getOperatorId() << '\n';
        this_thread::sleep_for(chrono::seconds(1));
        this_thread::yield();
    });

    t1.join();
    t2.join();
    t3.join();

    cout << "All Bus Operator Threads Completed!\n";
}

void demonstrateOperatorThreads(BusOperator& op) {
    thread t1(&BusOperator::displayOperator, &op);
    thread t2(&BusOperator::displayManagedBuses, &op);
    thread t3([&op]() {
        cout << "Operator Name: " << op.getName() << '\n';
    });

    t1.join();
    t2.join();
    t3.join();
}
