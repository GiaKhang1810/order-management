#include "Order.hpp"
#include "Queue.hpp"
#include "Manager.hpp"

#include <string>

using std::string;

void Manager::addOrder(const string& orderID, const string& date, const string& customer, double money) {
    Order order(orderID, date, customer, money);
    queue.enqueue(order);
}

void Manager::deleteOrder(const string& orderID) {
    Order* order = queue.findByID(orderID);
    if (order == nullptr)
        throw std::runtime_error("Order not found.");

    queue.removeByID(orderID);
}

void Manager::changeStatus(const string& orderID, OrderStatus status) {
    if (queue.updateStatus(orderID, status) == false)
        throw std::runtime_error("Order not found.");
}

const Order* Manager::findOrder(const string& orderID) const {
    return queue.findByID(orderID);
}
