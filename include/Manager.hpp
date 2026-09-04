#pragma once

#include "Order.hpp"
#include "Queue.hpp"

#include <string>

using std::string;

class Manager {
    private:
        Queue queue;
    public:
        Manager() : queue() {}

        void addOrder(const string& orderID, const string& date, const string& customer, double money);
        void deleteOrder(const string& orderID);
        // void processOrder();

        void changeStatus(const string& orderID, OrderStatus status);

        const Order* findOrder(const string& orderID) const;
        // const Order* findOrder(const string& date) const;
        // const Order* findOrder(OrderStatus status) const;

        // void showOrders() const;
        // void showStatistics() const;
};
