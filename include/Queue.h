#pragma once

#include "Order.h"

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

        QueueNode* getMiddle(QueueNode* head);
        QueueNode* merge(QueueNode* left, QueueNode* right);
        QueueNode* mergeSort(QueueNode* head);
        void copyFrom(const Queue& other);

    public:
        Queue();
        Queue(const Queue& other);
        Queue& operator=(const Queue& other);

        ~Queue();

        void enqueue(const Order& order);
        Order dequeue();

        bool isEmpty() const;
        int getSize() const;

        const Order& peek() const;

        Order* findById(const string& id);
        const Order* findById(const string& id) const;

        bool updateStatus(const string& id, OrderStatus status);
        bool removeByID(const string& id);

        Queue getOrdersByStatus(OrderStatus status) const;
        Queue getOrdersByDate(const string& date) const;

        void sortByMoney();

        void display() const;
};
