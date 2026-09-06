#pragma once

#include "Order.h"
#include "Queue.h"
#include "Statistics.h"

#include <string>

using std::string;

class Manager {
    private:
        Queue queue;

    public:
        Manager() : queue() {}

        void addOrder(
            const string& orderID,
            const string& date,
            const string& customer,
            double money
        );

        void deleteOrder(const string& orderID);
        void processOrder(const string& orderID);
        void changeStatus(const string& orderID, OrderStatus status);

        const Order* findOrder(const string& orderID) const;

        void showOrders() const;
        void showOrdersByDate(const string& date) const;
        void showOrdersByStatus(OrderStatus status) const;
        void showStatistics() const;
        void sortOrdersByMoney();
};
