#include "Payment.h"

Payment::Payment()
{
    paymentId = 0;
    amount = 0;
    method = "Unknown";
    status = "Pending";
}

Payment::Payment(
    int id,
    double amount,
    string method)
{
    paymentId = id;
    this->amount = amount;
    this->method = method;
    status = "Pending";
}

Payment::~Payment()
{
    cout << "Payment object destroyed." << endl;
}

void Payment::makePayment()
{
    status = "Successful";
}

void Payment::setPayment(double amount)
{
    this->amount = amount;
}

void Payment::setPayment(
    double amount,
    string method)
{
    this->amount = amount;
    this->method = method;
}

void Payment::displayPayment()
{
    cout << "\n========== PAYMENT ==========" << endl;
    cout << "Payment ID : " << paymentId << endl;
    cout << "Amount     : Rs. " << amount << endl;
    cout << "Method     : " << method << endl;
    cout << "Status     : " << status << endl;
    cout << "=============================" << endl;
}

Payment& Payment::operator=(const Payment& other)
{
    if (this != &other)
    {
        paymentId = other.paymentId;
        amount = other.amount;
        method = other.method;
        status = other.status;
    }

    return *this;
}

Payment Payment::operator+(const Payment& other)
{
    Payment temp;

    temp.paymentId = paymentId + other.paymentId;
    temp.amount = amount + other.amount;
    temp.method = method + " + " + other.method;
    temp.status = "Combined";

    return temp;
}
