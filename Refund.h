#ifndef REFUND_H
#define REFUND_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class RefundException : public exception {
private:
    string message;

public:
    explicit RefundException(const string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidRefundException : public RefundException {
public:
    explicit InvalidRefundException(const string& msg)
        : RefundException(msg) {}
};

class RefundProcessingException : public RefundException {
public:
    explicit RefundProcessingException(const string& msg)
        : RefundException(msg) {}
};

class IRefundable {
public:
    virtual void processRefund() = 0;
    virtual ~IRefundable() {}
};

class RefundFinally {
public:
    ~RefundFinally() noexcept {
        cout << "Finally-equivalent cleanup: refund operation finished.\n";
    }
};

class RefundBase : public IRefundable {
protected:
    int refundId;

public:
    RefundBase();
    RefundBase(int id);

    virtual void displayBase() const;
    virtual ~RefundBase() {}
};

class RefundSummary {
public:
    int refundId;
    double amount;
    string status;

    RefundSummary()
        : refundId(0), amount(0), status("Pending") {}

    RefundSummary(int id, double value, string refundStatus)
        : refundId(id), amount(value), status(refundStatus) {}
};

class Refund final : public RefundBase {
private:
    double amount;
    string status;
    static int refundCount;
    static mutex refundMutex;

public:
    class RefundDetails {
    private:
        string description;

    public:
        RefundDetails();
        RefundDetails(string description);
        void displayDetails() const;
    };

    Refund();
    Refund(int id, double amount, string status);
    Refund(int id);

    ~Refund() override;

    void processRefund() override;

    void setRefund(double amount);
    void setRefund(double amount, string status);

    void displayBase() const override;
    void displayRefund() const;

    int getRefundId() const;
    double getAmount() const;
    string getStatus() const;

    static int getRefundCount();

    Refund& operator=(const Refund& other);

    operator double() const;
    operator RefundSummary() const;

    friend Refund operator+(const Refund& r1, const Refund& r2);
    friend ostream& operator<<(ostream& out, const Refund& r);
    friend istream& operator>>(istream& in, Refund& r);
};

class RefundThread {
private:
    thread worker;

protected:
    virtual void run() = 0;

public:
    RefundThread() = default;
    RefundThread(const RefundThread&) = delete;
    RefundThread& operator=(const RefundThread&) = delete;

    virtual ~RefundThread();
    void start();
    void join();
    bool joinable() const;
};

class RefundProcessingThread : public RefundThread {
private:
    IRefundable* refundable;

protected:
    void run() override;

public:
    explicit RefundProcessingThread(IRefundable* refundable);
    ~RefundProcessingThread() override;
};

class RefundRunnable {
public:
    virtual void run() = 0;
    virtual ~RefundRunnable() {}
};

class RefundRunnableTask : public RefundRunnable {
private:
    IRefundable* refundable;

public:
    explicit RefundRunnableTask(IRefundable* refundable);
    void run() override;
};

class RefundRunnableExecutor {
private:
    thread worker;

public:
    RefundRunnableExecutor() = default;
    RefundRunnableExecutor(const RefundRunnableExecutor&) = delete;
    RefundRunnableExecutor& operator=(const RefundRunnableExecutor&) = delete;

    ~RefundRunnableExecutor();
    void start(RefundRunnable& task);
    void join();
    bool joinable() const;
};

template <typename T>
T getLargerRefund(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
class RefundStorage {
private:
    T data;

public:
    RefundStorage(T value) : data(value) {}

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

#endif
