#pragma once

#include "Order.hpp"
#include "Queue.hpp"

#include <string>

using std::string;

class Manager {
    private:
        Queue queue;
    public:
        void addOrder(const Order& order);
        void deleteOrder(const string& orderID);
        void processOrder();

        void changeStatus(const string& orderID, OrderStatus status);

        void findOrder(const string& orderID) const;
        void findOrder(const string& date) const;
        void findOrder(OrderStatus status) const;

        void showOrders() const;
        void showStatistics() const;
};
