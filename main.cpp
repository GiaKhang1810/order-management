// #include "Manager.hpp"
// #include "Order.hpp"
// #include "Queue.hpp"
// #include "Statistics.hpp"

#include "Order.hpp"

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
    while (true) {
        try {
            menu();

            int choice;
            cin >> choice;

            if (choice == 0)
                break;
        } catch (const exception& error) {
            cout << "Caught exception: " << error.what() << "\n";
        }
    }

    return 0;
}
