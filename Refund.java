#include "Refund.h"

Refund::Refund()
{
    refundId = 0;
    amount = 0;
    status = "Pending";
}

Refund::Refund(int id, double amount)
{
    refundId = id;
    this->amount = amount;
    status = "Pending";
}


Refund::~Refund()
{
    cout << "Refund object destroyed." << endl;
}


void Refund::processRefund()
{
    status = "Processed";
}


void Refund::setRefund(double amount)
{
    this->amount = amount;
}

void Refund::setRefund(double amount, string status)
{
    this->amount = amount;
    this->status = status;
}

void Refund::displayRefund()
{
    cout << "\n========== REFUND ==========" << endl;
    cout << "Refund ID : " << refundId << endl;
    cout << "Amount    : Rs. " << amount << endl;
    cout << "Status    : " << status << endl;
    cout << "============================" << endl;
}


Refund& Refund::operator=(const Refund& other)
{
    if (this != &other)
    {
        refundId = other.refundId;
        amount = other.amount;
        status = other.status;
    }

    return *this;
}

Refund operator+(const Refund& r1, const Refund& r2)
{
    Refund temp;

    temp.refundId = r1.refundId + r2.refundId;
    temp.amount = r1.amount + r2.amount;
    temp.status = "Combined";

    return temp;
}
