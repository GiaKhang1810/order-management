#include "Manager.hpp"
#include "Order.hpp"
#include "Queue.hpp"

#include <iostream>
#include <string>

using
    std::cout,
    std::cin,
    std::exception,
    std::string;

void menu() {
    cout
        << "Order Management System\n"
        << "=======================\n"
        << "1. Add Order\n"
        << "2. Delete Order\n"
        << "3. Find Order\n"
        << "4. Change Order Status\n"
        << "5. Show Statistics\n"
        << "6. Find Orders By Date\n"
        << "7. Find Orders By Status\n"
        << "0. Exit\n"
        << "=======================\n"
        << "Enter your choice: ";
}

int main() {
    Manager manager;

    while (true) {
        try {
            menu();

            int choice;
            cin >> choice;

            if (choice == 0)
                break;

            if (choice == 1) {
                string orderID;

                cout << "\n========================\nEnter Order ID: ";
                cin >> orderID;

                if (manager.findOrder(orderID) != nullptr) {
                    cout << "========================\nOrder ID already exists. Please try again.\n========================\n\n";
                    continue;
                }

                string date, customer;
                double money;

                cout << "Enter Date (YYYY-MM-DD): ";
                cin >> date;

                cout << "Enter Customer Name: ";
                cin >> customer;

                cout << "Enter Money Amount: ";
                cin >> money;

                cout << "========================\n\n";

                manager.addOrder(orderID, date, customer, money);
            }
        } catch (const exception& error) {
            cout << "Caught exception: " << error.what() << "\n";
        }
    }

    cout << "Exiting Order Management System.\n";

    return 0;
}
