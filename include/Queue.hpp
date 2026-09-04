#pragma once

#include "Order.hpp"

#include <string>

using std::string;

struct QueueNode {
    Order data;
    QueueNode* next;

    QueueNode(const Order& order) : data(order), next(nullptr) {}
};

class Queue {
    private:
        QueueNode* front;
        QueueNode* rear;
        int size;
    public:
        Queue() : front(nullptr), rear(nullptr), size(0) {}

        ~Queue() {
            while (isEmpty() == false)
                dequeue();
        }

        void enqueue(const Order& order);
        Order dequeue();

        bool isEmpty() const;
        int getSize() const;

        const Order& peek() const;

        Order* findByID(const std::string& id);
        const Order* findByID(const std::string& id) const;

        bool updateStatus(const string& id, OrderStatus status);
        bool removeByID(const std::string& id);

        void display() const;
};
