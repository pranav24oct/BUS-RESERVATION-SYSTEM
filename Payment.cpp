
#include "Payment.h"

int Payment::paymentCount = 0;
mutex Payment::paymentMutex;

Payment::Payment()
    : paymentId(0), amount(0),
      method("Not selected"), status("Pending") {
    lock_guard<mutex> lock(paymentMutex);
    ++paymentCount;
}

Payment::Payment(int id, double amount, string method)
    : paymentId(id), amount(amount),
      method(method), status("Pending") {
    lock_guard<mutex> lock(paymentMutex);
    ++paymentCount;
}

Payment::Payment(int id)
    : paymentId(id), amount(0),
      method("Not selected"), status("Pending") {
    lock_guard<mutex> lock(paymentMutex);
    ++paymentCount;
}

Payment::Payment(const Payment& other) {
    lock_guard<mutex> lock(paymentMutex);
    paymentId = other.paymentId;
    amount = other.amount;
    method = other.method;
    status = other.status;
    ++paymentCount;
}

Payment::~Payment() {
    lock_guard<mutex> lock(paymentMutex);
    --paymentCount;
    cout << "Payment object destroyed.\n";
}

void Payment::makePayment() {
    lock_guard<mutex> lock(paymentMutex);

    if (amount <= 0) {
        throw PaymentValidationException("Invalid payment amount.");
    }

    if (method.empty() || method == "Not selected") {
        throw PaymentProcessingException("Payment method not selected.");
    }

    status = "Successful";
    cout << "Payment successful! ID: " << paymentId << '\n';
}

void Payment::setPayment(double amount) {
    lock_guard<mutex> lock(paymentMutex);

    if (amount <= 0)
        throw PaymentValidationException("Invalid payment amount.");

    this->amount = amount;
}

void Payment::setPayment(double amount, string method) {
    lock_guard<mutex> lock(paymentMutex);

    if (amount <= 0 || method.empty())
        throw PaymentValidationException("Invalid payment details.");

    this->amount = amount;
    this->method = method;
}

void Payment::displayPayment() const {
    lock_guard<mutex> lock(paymentMutex);

    cout << "Payment ID: " << paymentId << '\n';
    cout << "Amount: " << amount << '\n';
    cout << "Method: " << method << '\n';
    cout << "Status: " << status << '\n';
}

int Payment::getPaymentId() const {
    lock_guard<mutex> lock(paymentMutex);
    return paymentId;
}

double Payment::getAmount() const {
    lock_guard<mutex> lock(paymentMutex);
    return amount;
}

string Payment::getMethod() const {
    lock_guard<mutex> lock(paymentMutex);
    return method;
}

string Payment::getStatus() const {
    lock_guard<mutex> lock(paymentMutex);
    return status;
}

int Payment::getPaymentCount() {
    lock_guard<mutex> lock(paymentMutex);
    return paymentCount;
}

Payment& Payment::operator=(const Payment& other) {
    if (this != &other) {
        lock_guard<mutex> lock(paymentMutex);

        paymentId = other.paymentId;
        amount = other.amount;
        method = other.method;
        status = other.status;
    }

    return *this;
}

Payment Payment::operator+(const Payment& other) const {
    int newId;
    double newAmount;
    string newMethod;

    {
        lock_guard<mutex> lock(paymentMutex);

        newId = paymentId + other.paymentId;
        newAmount = amount + other.amount;
        newMethod = method + " + " + other.method;
    }

    Payment result(newId, newAmount, newMethod);
    result.status = "Combined";

    return result;
}

Payment::operator double() const {
    lock_guard<mutex> lock(paymentMutex);
    return amount;
}

Payment::operator PaymentSummary() const {
    lock_guard<mutex> lock(paymentMutex);
    return PaymentSummary(paymentId, amount, status);
}

ostream& operator<<(ostream& out, const Payment& payment) {
    lock_guard<mutex> lock(Payment::paymentMutex);

    out << "Payment ID: " << payment.paymentId << '\n';
    out << "Amount: " << payment.amount << '\n';
    out << "Method: " << payment.method << '\n';
    out << "Status: " << payment.status << '\n';

    return out;
}

bool operator==(const Payment& p1, const Payment& p2) {
    lock_guard<mutex> lock(Payment::paymentMutex);
    return p1.paymentId == p2.paymentId;
}

void PaymentInspector::displayPrivateDetails(const Payment& payment) {
    lock_guard<mutex> lock(Payment::paymentMutex);

    cout << "Private Payment Details:\n";
    cout << "Payment ID: " << payment.paymentId << '\n';
    cout << "Amount: " << payment.amount << '\n';
    cout << "Method: " << payment.method << '\n';
    cout << "Status: " << payment.status << '\n';
}

void demonstratePaymentThreads(Payment& payment) {
    auto task = [&payment]() {
        try {
            payment.makePayment();
        }
        catch (const PaymentException& e) {
            cout << "Payment error: " << e.what() << '\n';
        }
    };

    thread t1(task);
    thread t2(task);

    t1.join();
    t2.join();
}
