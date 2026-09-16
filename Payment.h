#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
using namespace std;

class Payment
{
private:
    int paymentId;
    double amount;
    string method;
    string status;

public:
    // Constructors and Destructor
    Payment();
    Payment(int id, double amount, string method);
    ~Payment();

    // Member functions
    void makePayment();
    void setPayment(double amount);
    void setPayment(double amount, string method);
    void displayPayment();

    // Operator overloading
    Payment& operator=(const Payment& other);
    Payment operator+(const Payment& other);
};

#endif
