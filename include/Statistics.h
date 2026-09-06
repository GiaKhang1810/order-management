#pragma once

#include "Queue.h"

#include <string>

class Statistics {
    private:
        const Queue& queue;

    public:
        Statistics(const Queue& queue) : queue(queue) {}

        int getTotalOrders() const;
        double getTotalValue() const;
        int getOrdersCountByStatus(OrderStatus status) const;
        int countOrdersByDate(const std::string& date) const;

        void displaySummary() const;
};
