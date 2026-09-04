#include "Order.hpp"
#include "Queue.hpp"

#include <iostream>
#include <stdexcept>

using
    std::cout,
    std::runtime_error,
    std::string;

void Queue::enqueue(const Order& order) {
    QueueNode* node = new QueueNode(order);

    if (isEmpty() == true)
        front = rear = node;
    else {
        rear -> next = node;
        rear = node;
    }

    size++;
}

Order Queue::dequeue() {
    if (isEmpty() == true)
        throw runtime_error("Queue is empty.");

    QueueNode* temp = front;
    Order order = front -> data;
    front = front -> next;

    delete temp;
    size--;

    if (front == nullptr)
        rear = nullptr;

    return order;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

int Queue::getSize() const {
    return size;
}

const Order& Queue::peek() const {
    if (isEmpty() == true)
        throw runtime_error("Queue is empty.");

    return front -> data;
}

Order* Queue::findByID(const string& id) {
    QueueNode* current = front;

    while (current != nullptr) {
        if (current -> data.getOrderID() == id)
            return &current -> data;

        current = current -> next;
    }

    return nullptr;
}

const Order* Queue::findByID(const string& id) const {
    const QueueNode* current = front;

    while (current != nullptr) {
        if (current -> data.getOrderID() == id)
            return &current -> data;

        current = current -> next;
    }

    return nullptr;
}

bool Queue::updateStatus(const string& id, OrderStatus status) {
    Order* order = findByID(id);

    if (order == nullptr)
        return false;

    order -> setStatus(status);

    return true;
}

bool Queue::removeByID(const string& id) {
    if (isEmpty() == true)
        return false;

    QueueNode* current = front;
    QueueNode* previous = nullptr;

    while (current != nullptr) {
        if (current -> data.getOrderID() == id) {
            if (previous == nullptr)
                front = current -> next;
            else
                previous -> next = current -> next;

            if (current == rear)
                rear = previous;

            delete current;

            size--;

            if (size == 0) {
                front = nullptr;
                rear = nullptr;
            }

            return true;
        }

        previous = current;
        current = current -> next;
    }

    return false;
}

void Queue::display() const {
    if (isEmpty() == true) {
        cout << "Queue is empty.\n";
        return;
    }

    const QueueNode* current = front;

    while (current != nullptr) {
        current -> data.display();
        cout << "-------------------------\n";
        current = current -> next;
    }
}
