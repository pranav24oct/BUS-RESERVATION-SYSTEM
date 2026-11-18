
#ifndef BUS_OPERATOR_H
#define BUS_OPERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <thread>

using namespace std;

class BusOperatorException : public runtime_error {
public:
    BusOperatorException(const string& message)
        : runtime_error(message) {}
};

class BusOperatorValidationException : public BusOperatorException {
public:
    BusOperatorValidationException(const string& message)
        : BusOperatorException(message) {}
};

class InvalidOperatorId : public BusOperatorValidationException {
public:
    InvalidOperatorId()
        : BusOperatorValidationException("Operator ID must be positive.") {}
};

class InvalidOperatorDetails : public BusOperatorValidationException {
public:
    InvalidOperatorDetails(const string& message)
        : BusOperatorValidationException(message) {}
};

class BusOperatorProcessingException : public BusOperatorException {
public:
    BusOperatorProcessingException(const string& message)
        : BusOperatorException(message) {}
};

class BusOperator {
private:
    int operatorId;
    string name;
    string companyName;
    string phone;
    vector<int> managedBusIds;

    static int operatorCount;
    static mutex operatorMutex;

public:
    class OperatorDetails {
    public:
        int totalBuses;
        string status;

        OperatorDetails();
        OperatorDetails(int buses, string status);
    };

    BusOperator();
    BusOperator(int id, string name, string companyName, string phone);
    BusOperator(const BusOperator& other);

    virtual ~BusOperator();

    void setOperator(string name, string phone);
    void setOperator(string name, string companyName, string phone);

    void addBus(int busId);
    bool removeBus(int busId);
    void displayManagedBuses() const;

    virtual void displayOperator() const;

    int getOperatorId() const;
    string getName() const;
    string getCompanyName() const;
    string getPhone() const;

    static int getOperatorCount();

    BusOperator& operator=(const BusOperator& other);

    operator int() const;

    friend ostream& operator<<(ostream& out, const BusOperator& op);

    friend bool operator==(const BusOperator& op1,
                           const BusOperator& op2);

    friend class BusOperatorAdmin;

    void runOperatorTasks();
};

class BusOperatorAdmin {
public:
    static void displayOperatorDetails(const BusOperator& op);
};

template <typename T>
T getLargerOperator(T a, T b) {
    return (a > b) ? a : b;
}

template <class T>
class OperatorStorage {
private:
    T data;

public:
    OperatorStorage(T value) : data(value) {}

    void setData(T value) {
        data = value;
    }

    T getData() const {
        return data;
    }
};

void demonstrateOperatorThreads(BusOperator& op);

#endif
