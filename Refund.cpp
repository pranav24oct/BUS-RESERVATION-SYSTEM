#include "Refund.h"


// ==============================
// RefundBase
// ==============================

RefundBase::RefundBase()
{
    refundId = 0;
}

RefundBase::RefundBase(int id)
{
    refundId = id;
}

void RefundBase::displayBase()
{
    cout << "Refund ID : " << refundId << endl;
}


// ==============================
// Static variable
// ==============================

int Refund::refundCount = 0;


// ==============================
// RefundDetails - Nested Class
// ==============================

Refund::RefundDetails::RefundDetails()
{
    description = "No details";
}

Refund::RefundDetails::RefundDetails(string desc)
{
    description = desc;
}

void Refund::RefundDetails::displayDetails()
{
    cout << "Refund Details : " << description << endl;
}


// ==============================
// Refund Constructors
// ==============================

Refund::Refund()
{
    refundId = 0;
    amount = 0;
    status = "Pending";

    refundCount++;
}

Refund::Refund(int id, double amount)
{
    refundId = id;
    this->amount = amount;
    status = "Pending";

    refundCount++;
}


// ==============================
// Destructor
// ==============================

Refund::~Refund()
{
    cout << "Refund object destroyed." << endl;
}


// ==============================
// Process Refund
// ==============================

void Refund::processRefund()
{
    status = "Processed";
}


// ==============================
// Function Overloading
// ==============================

void Refund::setRefund(double amount)
{
    this->amount = amount;
}

void Refund::setRefund(double amount, string status)
{
    this->amount = amount;
    this->status = status;
}


// ==============================
// Display Refund
// ==============================

void Refund::displayRefund()
{
    cout << "\n========== REFUND ==========" << endl;
    cout << "Refund ID : " << refundId << endl;
    cout << "Amount    : Rs. " << amount << endl;
    cout << "Status    : " << status << endl;
    cout << "============================" << endl;
}


// ==============================
// Static Function
// ==============================

int Refund::getRefundCount()
{
    return refundCount;
}


// ==============================
// Assignment Operator
// ==============================

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


// ==============================
// + Operator Overloading
// ==============================

Refund operator+(const Refund& r1, const Refund& r2)
{
    Refund temp;

    temp.refundId = r1.refundId + r2.refundId;
    temp.amount = r1.amount + r2.amount;
    temp.status = "Combined";

    return temp;
}


// ==============================
// << Stream Operator
// Friend Function
// ==============================

ostream& operator<<(ostream& out, const Refund& r)
{
    out << "\n========== REFUND ==========" << endl;
    out << "Refund ID : " << r.refundId << endl;
    out << "Amount    : Rs. " << r.amount << endl;
    out << "Status    : " << r.status << endl;
    out << "============================" << endl;

    return out;
}


// ==============================
// >> Stream Operator
// Friend Function
// ==============================

istream& operator>>(istream& in, Refund& r)
{
    cout << "Enter Refund ID: ";
    in >> r.refundId;

    cout << "Enter Amount: ";
    in >> r.amount;

    cout << "Enter Status: ";
    in >> r.status;

    return in;
}
