
#include "Refund.h"

int Refund::refundCount = 0;
mutex Refund::refundMutex;

RefundBase::RefundBase() : refundId(0) {}

RefundBase::RefundBase(int id) : refundId(id) {}

void RefundBase::displayBase() const {
    cout << "Refund ID: " << refundId << '\n';
}

Refund::RefundDetails::RefundDetails()
    : description("No details") {}

Refund::RefundDetails::RefundDetails(string description)
    : description(description) {}

void Refund::RefundDetails::displayDetails() const {
    cout << "Refund details: " << description << '\n';
}

Refund::Refund()
    : RefundBase(), amount(0), status("Pending") {
    lock_guard<mutex> lock(refundMutex);
    ++refundCount;
}

Refund::Refund(int id, double amount, string status)
    : RefundBase(id), amount(amount), status(status) {
    if (id <= 0) {
        throw InvalidRefundException("Refund ID must be positive.");
    }

    if (amount < 0) {
        throw InvalidRefundException("Refund amount cannot be negative.");
    }

    lock_guard<mutex> lock(refundMutex);
    ++refundCount;
}

Refund::Refund(int id)
    : RefundBase(id), amount(0), status("Pending") {
    if (id <= 0) {
        throw InvalidRefundException("Refund ID must be positive.");
    }

    lock_guard<mutex> lock(refundMutex);
    ++refundCount;
}

Refund::~Refund() {
    lock_guard<mutex> lock(refundMutex);
    --refundCount;
}

void Refund::processRefund() {
    lock_guard<mutex> lock(refundMutex);

    cout << "Refund processing started.\n";

    this_thread::yield();
    this_thread::sleep_for(chrono::milliseconds(500));

    if (refundId <= 0) {
        throw InvalidRefundException("Invalid refund ID.");
    }

    if (amount <= 0) {
        throw RefundProcessingException(
            "Refund amount must be greater than zero."
        );
    }

    status = "Processed";

    cout << "Refund processed successfully.\n";
}

void Refund::setRefund(double amount) {
    if (amount < 0) {
        throw InvalidRefundException(
            "Refund amount cannot be negative."
        );
    }

    lock_guard<mutex> lock(refundMutex);
    this->amount = amount;
}

void Refund::setRefund(double amount, string status) {
    if (amount < 0) {
        throw InvalidRefundException(
            "Refund amount cannot be negative."
        );
    }

    lock_guard<mutex> lock(refundMutex);
    this->amount = amount;
    this->status = status;
}

void Refund::displayBase() const {
    lock_guard<mutex> lock(refundMutex);
    cout << "RefundBase display overridden.\n";
    cout << "Refund ID: " << refundId << '\n';
}

void Refund::displayRefund() const {
    lock_guard<mutex> lock(refundMutex);
    cout << "Refund ID: " << refundId << '\n';
    cout << "Amount: " << amount << '\n';
    cout << "Status: " << status << '\n';
}

int Refund::getRefundId() const {
    lock_guard<mutex> lock(refundMutex);
    return refundId;
}

double Refund::getAmount() const {
    lock_guard<mutex> lock(refundMutex);
    return amount;
}

string Refund::getStatus() const {
    lock_guard<mutex> lock(refundMutex);
    return status;
}

int Refund::getRefundCount() {
    lock_guard<mutex> lock(refundMutex);
    return refundCount;
}

Refund& Refund::operator=(const Refund& other) {
    if (this != &other) {
        scoped_lock lock(refundMutex);
        refundId = other.refundId;
        amount = other.amount;
        status = other.status;
    }

    return *this;
}

Refund::operator double() const {
    lock_guard<mutex> lock(refundMutex);
    return amount;
}

Refund::operator RefundSummary() const {
    lock_guard<mutex> lock(refundMutex);
    return RefundSummary(refundId, amount, status);
}

Refund operator+(const Refund& r1, const Refund& r2) {
    double combinedAmount;
    {
        lock_guard<mutex> lock(Refund::refundMutex);
        combinedAmount = r1.amount + r2.amount;
    }

    Refund result;
    result.amount = combinedAmount;
    result.status = "Combined";
    return result;
}

ostream& operator<<(ostream& out, const Refund& r) {
    lock_guard<mutex> lock(Refund::refundMutex);
    out << "Refund ID: " << r.refundId
        << "\nAmount: " << r.amount
        << "\nStatus: " << r.status;

    return out;
}

istream& operator>>(istream& in, Refund& r) {
    int id;
    double amount;
    string status;

    cout << "Enter refund ID: ";
    if (!(in >> id)) {
        throw RefundProcessingException("Invalid refund ID input.");
    }

    cout << "Enter refund amount: ";
    if (!(in >> amount)) {
        throw RefundProcessingException("Invalid refund amount input.");
    }

    cout << "Enter refund status: ";
    if (!(in >> status)) {
        throw RefundProcessingException("Invalid refund status input.");
    }

    if (id <= 0) {
        throw InvalidRefundException("Refund ID must be positive.");
    }

    if (amount < 0) {
        throw InvalidRefundException("Refund amount cannot be negative.");
    }

    lock_guard<mutex> lock(Refund::refundMutex);
    r.refundId = id;
    r.amount = amount;
    r.status = status;

    return in;
}

RefundThread::~RefundThread() {
    if (worker.joinable()) {
        worker.join();
    }
}

void RefundThread::start() {
    if (worker.joinable()) {
        throw RefundProcessingException(
            "Refund thread has already been started."
        );
    }

    worker = thread(&RefundThread::run, this);
}

void RefundThread::join() {
    if (worker.joinable()) {
        worker.join();
    }
}

bool RefundThread::joinable() const {
    return worker.joinable();
}

RefundProcessingThread::RefundProcessingThread(IRefundable* refundable)
    : refundable(refundable) {
    if (refundable == nullptr) {
        throw InvalidRefundException(
            "Refund interface pointer cannot be null."
        );
    }
}

RefundProcessingThread::~RefundProcessingThread() {
    join();
}

void RefundProcessingThread::run() {
    try {
        refundable->processRefund();
    }
    catch (const exception& e) {
        cout << "Refund thread error: " << e.what() << '\n';
    }
}

RefundRunnableTask::RefundRunnableTask(IRefundable* refundable)
    : refundable(refundable) {
    if (refundable == nullptr) {
        throw InvalidRefundException(
            "Refund interface pointer cannot be null."
        );
    }
}

void RefundRunnableTask::run() {
    try {
        this_thread::yield();
        this_thread::sleep_for(chrono::milliseconds(500));
        refundable->processRefund();
    }
    catch (const exception& e) {
        cout << "Runnable refund error: " << e.what() << '\n';
    }
}

RefundRunnableExecutor::~RefundRunnableExecutor() {
    if (worker.joinable()) {
        worker.join();
    }
}

void RefundRunnableExecutor::start(RefundRunnable& task) {
    if (worker.joinable()) {
        throw RefundProcessingException(
            "Runnable thread has already been started."
        );
    }

    worker = thread(&RefundRunnable::run, &task);
}

void RefundRunnableExecutor::join() {
    if (worker.joinable()) {
        worker.join();
    }
}

bool RefundRunnableExecutor::joinable() const {
    return worker.joinable();
}
