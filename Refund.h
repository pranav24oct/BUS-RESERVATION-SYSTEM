#ifndef REFUND_H
#define REFUND_H

#include <iostream>
#include <string>
using namespace std;


// Base class for demonstrating Object Slicing
class RefundBase
{
protected:
    int refundId;

public:
    RefundBase();
    RefundBase(int id);

    virtual void displayBase();
};


// Refund class
class Refund final : public RefundBase
{
private:
    double amount;
    string status;

    // Static variable
    static int refundCount;

public:

    // Nested class
    class RefundDetails
    {
    private:
        string description;

    public:
        RefundDetails();
        RefundDetails(string desc);

        void displayDetails();
    };


    // Constructors and Destructor
    Refund();
    Refund(int id, double amount);
    ~Refund();


    // Member functions
    void processRefund();

    void setRefund(double amount);
    void setRefund(double amount, string status);

    void displayRefund();


    // Static function
    static int getRefundCount();


    // Assignment operator
    Refund& operator=(const Refund& other);


    // Arithmetic operator
    friend Refund operator+(const Refund& r1, const Refund& r2);


    // Stream operators using friend functions
    friend ostream& operator<<(ostream& out, const Refund& r);
    friend istream& operator>>(istream& in, Refund& r);
};

#endif
