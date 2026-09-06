#include "Order.h"
#include "Queue.h"
#include "Statistics.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using
    std::chrono::duration_cast,
    std::chrono::high_resolution_clock,
    std::chrono::microseconds,
    std::cout,
    std::ifstream,
    std::invalid_argument,
    std::runtime_error,
    std::string,
    std::stringstream;

string trim(const string& text) {
    const size_t first = text.find_first_not_of(" \t\r\n");
    const size_t last = text.find_last_not_of(" \t\r\n");

    if (first == string::npos)
        return "";

    return text.substr(first, last - first + 1);
}

OrderStatus stringToStatus(const string& status) {
    if (status == "PENDING")
        return OrderStatus::PENDING;

    if (status == "PROCESSED")
        return OrderStatus::PROCESSED;

    if (status == "CANCELLED")
        return OrderStatus::CANCELLED;

    if (status == "COMPLETED")
        return OrderStatus::COMPLETED;

    throw invalid_argument(
        "Invalid order status: " + status
    );
}

void loadDataFromFile(
    Queue& queue,
    const string& filename
) {
    ifstream file(filename);

    if (!file.is_open())
        throw runtime_error(
            "Cannot open file: " + filename
        );

    string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        if (line.empty())
            continue;

        stringstream stream(line);

        string identity;
        string date;
        string customer;
        string moneyText;
        string statusText;

        std::getline(stream, identity, '|');
        std::getline(stream, date, '|');
        std::getline(stream, customer, '|');
        std::getline(stream, moneyText, '|');
        std::getline(stream, statusText, '|');

        identity = trim(identity);
        date = trim(date);
        customer = trim(customer);
        moneyText = trim(moneyText);
        statusText = trim(statusText);

        try {
            double money = std::stod(moneyText);

            OrderStatus status =
                stringToStatus(statusText);

            Order order(
                identity,
                date,
                customer,
                money,
                status
            );

            queue.enqueue(order);
        }
        catch (const std::exception& error) {
            cout
                << "Error at line "
                << lineNumber
                << ": "
                << error.what()
                << '\n';
        }
    }

    file.close();
}

long long measureSearch(
    Queue& queue,
    const string& orderId
) {
    const auto start =
        high_resolution_clock::now();

    queue.findById(orderId);

    const auto end =
        high_resolution_clock::now();

    return duration_cast<microseconds>(
        end - start
    ).count();
}

long long measureSort(Queue& queue) {
    const auto start =
        high_resolution_clock::now();

    queue.sortByMoney();

    const auto end =
        high_resolution_clock::now();

    return duration_cast<microseconds>(
        end - start
    ).count();
}

int main() {
    try {
        Queue queue;

        loadDataFromFile(
            queue,
            "data/TestData_12_100000.txt"
        );

        cout << "\n";
        cout << "========== ALL ORDERS ==========\n";
        queue.display();

        cout << "\n";
        cout << "========== FRONT ORDER ==========\n";
        queue.peek().display();

        cout << "\n";
        cout << "========== FIND BY ID ==========\n";

        Order* order =
            queue.findById("DH00005");

        if (order != nullptr)
            order->display();
        else
            cout << "Order not found.\n";

        cout << "\n";
        cout << "========== FIND BY DATE ==========\n";

        Queue ordersByDate = queue.getOrdersByDate("02/09/2026");

        ordersByDate.display();

        cout << "\n";
        cout << "========== FIND BY STATUS ==========\n";

        Queue ordersByStatus = queue.getOrdersByStatus(OrderStatus::PENDING);

        ordersByStatus.display();

        cout << "\n";
        cout << "========== UPDATE STATUS ==========\n";

        if (
            queue.updateStatus(
                "DH00005",
                OrderStatus::COMPLETED
            )
        ) {
            cout << "Update status successfully.\n";
        }
        else {
            cout << "Order not found.\n";
        }

        cout << "\n";
        cout << "========== STATISTICS ==========\n";

        Statistics statistics(queue);
        statistics.displaySummary();

        cout << "\n";
        cout << "========== SEARCH TIME ==========\n";

        long long searchTime =
            measureSearch(
                queue,
                "DH00005"
            );

        cout << "\n";
        cout << "========== SORT TIME ==========\n";

        long long sortTime =
            measureSort(queue);

        cout << "\n";
        cout << "========== SORTED ORDERS ==========\n";

        queue.display();

        cout << "\n";
        cout << "========== DEQUEUE ==========\n";

        Order removedOrder =
            queue.dequeue();

        cout << "Removed order:\n";
        removedOrder.display();

        cout << "\n";
        cout << "========== QUEUE AFTER DEQUEUE ==========\n";

        queue.display();

        cout
            << "Search time: "
            << searchTime
            << " microseconds\n";

        cout
            << "Merge Sort time: "
            << sortTime
            << " microseconds\n";
    }
    catch (const std::exception& error) {
        cout
            << "Error: "
            << error.what()
            << '\n';

        return 1;
    }

    return 0;
}
