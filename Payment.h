
#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <mutex>
#include <thread>

using namespace std;

class PaymentException : public runtime_error {
public:
    PaymentException(string message) : runtime_error(message) {}
};

class PaymentValidationException : public PaymentException {
public:
    PaymentValidationException(string message)
        : PaymentException(message) {}
};

class PaymentProcessingException : public PaymentValidationException {
public:
    PaymentProcessingException(string message)
        : PaymentValidationException(message) {}
};

class PaymentInterface {
public:
    virtual void displayPayment() const = 0;
    virtual ~PaymentInterface() = default;
};

class PaymentSummary {
public:
    int paymentId;
    double amount;
    string status;

    PaymentSummary() : paymentId(0), amount(0), status("Pending") {}

    PaymentSummary(int id, double value, string paymentStatus)
        : paymentId(id), amount(value), status(paymentStatus) {}
};

class Payment : virtual public PaymentInterface {
private:
    int paymentId;
    double amount;
    string method;
    string status;

    static int paymentCount;
    static mutex paymentMutex;

public:
    class PaymentDetails {
    public:
        double amount;
        string method;

        PaymentDetails(double value = 0, string paymentMethod = "")
            : amount(value), method(paymentMethod) {}

        void displayDetails() const {
            cout << "Amount: " << amount << '\n';
            cout << "Method: " << method << '\n';
        }
    };

    Payment();
    Payment(int id, double amount, string method);
    Payment(int id);
    Payment(const Payment& other);
    virtual ~Payment() override;

    void makePayment();

    void setPayment(double amount);
    void setPayment(double amount, string method);

    void displayPayment() const override;

    int getPaymentId() const;
    double getAmount() const;
    string getMethod() const;
    string getStatus() const;

    static int getPaymentCount();

    Payment& operator=(const Payment& other);
    Payment operator+(const Payment& other) const;

    operator double() const;
    operator PaymentSummary() const;

    friend ostream& operator<<(ostream& out, const Payment& payment);
    friend bool operator==(const Payment& p1, const Payment& p2);

    friend class PaymentInspector;
};

class PaymentInspector {
public:
    static void displayPrivateDetails(const Payment& payment);
};

class PaymentRecord {
protected:
    string description;

public:
    PaymentRecord(string text = "General payment")
        : description(text) {}

    virtual ~PaymentRecord() = default;

    virtual void displayRecord() const {
        cout << "Payment record: " << description << '\n';
    }
};

class OnlinePaymentRecord : public PaymentRecord {
private:
    string platform;

public:
    OnlinePaymentRecord(string text, string paymentPlatform)
        : PaymentRecord(text), platform(paymentPlatform) {}

    void displayRecord() const override {
        cout << "Payment record: " << description << '\n';
        cout << "Platform: " << platform << '\n';
    }
};

template <typename T>
T getLargerPayment(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
class PaymentStorage {
private:
    T data;

public:
    PaymentStorage(T value) : data(value) {}

    T getData() const {
        return data;
    }

    void setData(T value) {
        data = value;
    }

    void displayData() const {
        cout << "Stored data: " << data << '\n';
    }
};

void demonstratePaymentThreads(Payment& payment);

#endif
