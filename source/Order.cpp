#include "Order.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

using
    std::cout,
    std::invalid_argument,
    std::string;

Order::Order(const string& identity, const string& date, const string& customer, double money, OrderStatus status) {
    if (
        identity.empty() ||
        date.empty() ||
        customer.empty() ||
        money < 0
    ) throw invalid_argument("Cannot create order with empty fields or negative money.");

    this -> identity = identity;
    this -> date = date;
    this -> customer = customer;
    this -> money = money;
    this -> status = status;
}

const string& Order::getOrderID() const {
    return identity;
}

const string& Order::getDate() const {
    return date;
}

const string& Order::getCustomer() const {
    return customer;
}

double Order::getMoney() const {
    return money;
}

OrderStatus Order::getStatus() const {
    return status;
}

void Order::setOrderID(const string& identity) {
    if (
        identity.empty()
    ) throw invalid_argument("Order ID cannot be empty.");

    this -> identity = identity;
}

void Order::setDate(const string& date) {
    if (
        date.empty()
    ) throw invalid_argument("Order date cannot be empty.");

    this -> date = date;
}

void Order::setCustomer(const string& customer) {
    if (
        customer.empty()
    ) throw invalid_argument("Order customer cannot be empty.");

    this -> customer = customer;
}

void Order::setMoney(double money) {
    if (
        money < 0
    ) throw invalid_argument("Order money cannot be negative.");

    this -> money = money;
}

void Order::setStatus(OrderStatus status) {
    this -> status = status;
}

void Order::display() const {
    cout
        << "===============================\n"
        << "Order ID: " << identity
        << "\nDate: " << date
        << "\nCustomer: " << customer
        << "\nMoney: " << money
        << "\nStatus: " << getStatusString(status)
        << "\n===============================\n";
}

string Order::getStatusString(OrderStatus status) {
    switch (status) {
        case OrderStatus::PENDING:
            return "Pending";
        case OrderStatus::PROCESSED:
            return "Processed";
        case OrderStatus::CANCELLED:
            return "Cancelled";
        case OrderStatus::COMPLETED:
            return "Completed";
        default:
            return "Unknown";
    }
}
