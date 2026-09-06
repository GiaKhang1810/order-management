#include "Queue.h"

#include <iostream>
#include <stdexcept>

using
    std::cout,
    std::runtime_error,
    std::string;

Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

Queue::Queue(const Queue& other) : front(nullptr), rear(nullptr), size(0) {
    copyFrom(other);
}

Queue& Queue::operator=(const Queue& other) {
    if (this == &other)
        return *this;

    while (!isEmpty())
        dequeue();

    copyFrom(other);

    return *this;
}

Queue::~Queue() {
    while (!isEmpty())
        dequeue();
}

void Queue::copyFrom(const Queue& other) {
    const QueueNode* current = other.front;

    while (current != nullptr) {
        enqueue(current -> data);
        current = current -> next;
    }
}

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

    return front->data;
}

Order* Queue::findById(const string& id) {
    QueueNode* current = front;

    while (current != nullptr) {
        if (current -> data.getOrderID() == id)
            return &current -> data;

        current = current -> next;
    }

    return nullptr;
}

const Order* Queue::findById(const string& id) const {
    const QueueNode* current = front;

    while (current != nullptr) {
        if (current -> data.getOrderID() == id)
            return &current -> data;

        current = current -> next;
    }

    return nullptr;
}

bool Queue::updateStatus(const string& id, OrderStatus status) {
    Order* order = findById(id);

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
                previous -> next = current->next;

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
        current = current->next;
    }

    return false;
}

Queue Queue::getOrdersByStatus(OrderStatus status) const {
    Queue filteredQueue;
    const QueueNode* current = front;

    while (current != nullptr) {
        if (current -> data.getStatus() == status)
            filteredQueue.enqueue(current -> data);

        current = current -> next;
    }

    return filteredQueue;
}

Queue Queue::getOrdersByDate(const string& date) const {
    Queue filteredQueue;
    const QueueNode* current = front;

    while (current != nullptr) {
        if (current -> data.getDate() == date)
            filteredQueue.enqueue(current -> data);

        current = current -> next;
    }

    return filteredQueue;
}

QueueNode* Queue::getMiddle(QueueNode* head) {
    if (head == nullptr || head -> next == nullptr)
        return head;

    QueueNode* slow = head;
    QueueNode* fast = head -> next;

    while (fast != nullptr && fast -> next != nullptr) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }

    return slow;
}

QueueNode* Queue::merge(QueueNode* left, QueueNode* right) {
    if (left == nullptr)
        return right;

    if (right == nullptr)
        return left;

    if (left -> data.getMoney() <= right -> data.getMoney()) {
        left -> next = merge(left -> next, right);
        return left;
    }

    right->next = merge(left, right -> next);
    return right;
}

QueueNode* Queue::mergeSort(QueueNode* head) {
    if (head == nullptr || head -> next == nullptr)
        return head;

    QueueNode* middle = getMiddle(head);
    QueueNode* right = middle -> next;

    middle -> next = nullptr;

    QueueNode* left = mergeSort(head);
    right = mergeSort(right);

    return merge(left, right);
}

void Queue::sortByMoney() {
    if (size < 2)
        return;

    front = mergeSort(front);

    rear = front;

    while (rear->next != nullptr)
        rear = rear->next;
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
        current = current->next;
    }
}
