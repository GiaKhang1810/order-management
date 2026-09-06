#include "Statistics.h"

#include <iostream>
#include <string>

using
    std::cout,
    std::string;

int Statistics::getTotalOrders() const {
    return queue.getSize();
}

double Statistics::getTotalValue() const {
    double total = 0;

    Queue filteredQueue = queue;

    while (filteredQueue.isEmpty() == false) {
        total += filteredQueue.dequeue().getMoney();
    }

    return total;
}

int Statistics::getOrdersCountByStatus(OrderStatus status) const {
    Queue filteredQueue = queue.getOrdersByStatus(status);

    return filteredQueue.getSize();
}

int Statistics::countOrdersByDate(const string& date) const {
    Queue filteredQueue = queue.getOrdersByDate(date);

    return filteredQueue.getSize();
}

void Statistics::displaySummary() const {
    cout
        << "========== Statistics ==========\n"
        << "Total orders: " << getTotalOrders() << '\n'
        << "Total value: " << getTotalValue() << '\n'
        << "Pending: " << getOrdersCountByStatus(OrderStatus::PENDING) << '\n'
        << "Processed: " << getOrdersCountByStatus(OrderStatus::PROCESSED) << '\n'
        << "Cancelled: " << getOrdersCountByStatus(OrderStatus::CANCELLED) << '\n'
        << "Completed: " << getOrdersCountByStatus(OrderStatus::COMPLETED) << '\n'
        << "================================\n";
}
