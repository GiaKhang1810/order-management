#pragma once

#include <iostream>
#include <string>

using std::string;

enum class OrderStatus {
    PENDING,
    PROCESSED,
    CANCELLED,
    COMPLETED
};

class Order {
    private:
        string identity;
        string date;
        string customer;
        double money;
        OrderStatus status;
    public:
        Order() {}

        Order(
            const string& identity,
            const string& date,
            const string& customer,
            double money,
            OrderStatus status = OrderStatus::PENDING
        );

        const string& getOrderID() const;
        const string& getDate() const;
        const string& getCustomer() const;
        double getMoney() const;
        OrderStatus getStatus() const;

        void setOrderID(const string& identity);
        void setDate(const string& date);
        void setCustomer(const string& customer);
        void setMoney(double money);
        void setStatus(OrderStatus status);

        void display() const;

        static string getStatusString(OrderStatus status);
};
