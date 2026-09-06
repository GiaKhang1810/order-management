#include "Manager.h"

#include <stdexcept>

using
    std::runtime_error,
    std::string;

void Manager::addOrder(
    const string& orderID,
    const string& date,
    const string& customer,
    double money
) {
    if (findOrder(orderID) != nullptr)
        throw runtime_error("Order ID already exists.");

    Order order(orderID, date, customer, money);
    queue.enqueue(order);
}

void Manager::deleteOrder(const string& orderID) {
    if (queue.removeByID(orderID) == false)
        throw runtime_error("Order not found.");
}

void Manager::processOrder(const string& orderID) {
    if (queue.updateStatus(orderID, OrderStatus::PROCESSED) == false)
        throw runtime_error("Order not found.");
}

void Manager::changeStatus(const string& orderID, OrderStatus status) {
    if (queue.updateStatus(orderID, status) == false)
        throw runtime_error("Order not found.");
}

const Order* Manager::findOrder(const string& orderID) const {
    return queue.findById(orderID);
}

void Manager::showOrders() const {
    queue.display();
}

void Manager::showOrdersByDate(const string& date) const {
    Queue filteredQueue = queue.getOrdersByDate(date);
    filteredQueue.display();
}

void Manager::showOrdersByStatus(OrderStatus status) const {
    Queue filteredQueue = queue.getOrdersByStatus(status);
    filteredQueue.display();
}

void Manager::showStatistics() const {
    Statistics statistics(queue);
    statistics.displaySummary();
}

void Manager::sortOrdersByMoney() {
    queue.sortByMoney();
}
