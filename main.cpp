#include "Order.h"
#include "Queue.h"
#include "Statistics.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <limits>

using namespace std;
using namespace std::chrono;

string trim(const string& text)
{
    const size_t first =
        text.find_first_not_of(" \t\r\n");

    const size_t last =
        text.find_last_not_of(" \t\r\n");

    if (first == string::npos)
        return "";

    return text.substr(first, last - first + 1);
}

OrderStatus stringToStatus(const string& status)
{
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

long long getElapsedTime(
    const high_resolution_clock::time_point& start,
    const high_resolution_clock::time_point& end
)
{
    return duration_cast<microseconds>(
        end - start
    ).count();
}

void displayTime(long long time)
{
    cout << "\nExecution time: "
         << time
         << " microseconds\n";
}

void loadDataFromFile(
    Queue& queue,
    const string& filename
)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error(
            "Cannot open file: " + filename
        );
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        if (trim(line).empty())
            continue;

        stringstream stream(line);

        string identity;
        string date;
        string customer;
        string moneyText;
        string statusText;

        getline(stream, identity, '|');
        getline(stream, date, '|');
        getline(stream, customer, '|');
        getline(stream, moneyText, '|');
        getline(stream, statusText, '|');

        identity = trim(identity);
        date = trim(date);
        customer = trim(customer);
        moneyText = trim(moneyText);
        statusText = trim(statusText);

        try
        {
            double money = stod(moneyText);

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
        catch (const exception& error)
        {
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

OrderStatus selectStatus()
{
    cout << "\n";
    cout << "========== ORDER STATUS ==========\n";
    cout << "1. PENDING\n";
    cout << "2. PROCESSED\n";
    cout << "3. CANCELLED\n";
    cout << "4. COMPLETED\n";
    cout << "==================================\n";

    int choice;

    while (true)
    {
        cout << "Choose status: ";

        if (cin >> choice)
        {
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            break;
        }

        cout << "Invalid input. Please enter a number.\n";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }

    switch (choice)
    {
        case 1:
            return OrderStatus::PENDING;

        case 2:
            return OrderStatus::PROCESSED;

        case 3:
            return OrderStatus::CANCELLED;

        case 4:
            return OrderStatus::COMPLETED;

        default:
            throw invalid_argument(
                "Invalid status choice."
            );
    }
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    cin.get();
}

int inputInt(const string& message)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return value;
        }

        cout << "Invalid input. Please enter a number.\n";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }
}

string inputString(const string& message)
{
    string value;

    cout << message;
    getline(cin, value);

    return trim(value);
}

void displayMenu()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "        ORDER MANAGEMENT SYSTEM             \n";
    cout << "============================================\n";
    cout << "1. Display all orders\n";
    cout << "2. Peek front order\n";
    cout << "3. Find order by ID\n";
    cout << "4. Find orders by date\n";
    cout << "5. Find orders by status\n";
    cout << "6. Update order status\n";
    cout << "7. Display statistics\n";
    cout << "8. Sort orders by money\n";
    cout << "9. Dequeue order\n";
    cout << "10. Reload data file\n";
    cout << "0. Exit\n";
    cout << "============================================\n";
}

int main()
{
    Queue queue;
    string filename;

    cout << "============================================\n";
    cout << "        ORDER MANAGEMENT SYSTEM             \n";
    cout << "============================================\n";

    filename =
        inputString(
            "Enter data file path: "
        );

    try
    {
        auto start = high_resolution_clock::now();

        loadDataFromFile(
            queue,
            filename
        );

        auto end = high_resolution_clock::now();

        cout << "\nData loaded successfully!";

        displayTime(
            getElapsedTime(start, end)
        );
    }
    catch (const exception& error)
    {
        cout
            << "\nError: "
            << error.what()
            << '\n';

        return 1;
    }

    pauseScreen();

    while (true)
    {
        clearScreen();

        cout << "Current data file: "
             << filename
             << "\n";

        displayMenu();

        int choice =
            inputInt("Choose function: ");

        try
        {
            switch (choice)
            {
                case 1:
                {
                    clearScreen();

                    cout
                        << "========== ALL ORDERS ==========\n";

                    auto start =
                        high_resolution_clock::now();

                    queue.display();

                    auto end =
                        high_resolution_clock::now();

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 2:
                {
                    clearScreen();

                    cout
                        << "========== FRONT ORDER ==========\n";

                    auto start =
                        high_resolution_clock::now();

                    const Order& order =
                        queue.peek();

                    auto end =
                        high_resolution_clock::now();

                    order.display();

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 3:
                {
                    clearScreen();

                    cout
                        << "========== FIND BY ID ==========\n";

                    string orderId =
                        inputString(
                            "Enter Order ID: "
                        );

                    auto start =
                        high_resolution_clock::now();

                    Order* order =
                        queue.findById(orderId);

                    auto end =
                        high_resolution_clock::now();

                    cout << '\n';

                    if (order != nullptr)
                        order->display();
                    else
                        cout << "Order not found.\n";

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 4:
                {
                    clearScreen();

                    cout
                        << "========== FIND BY DATE ==========\n";

                    string date =
                        inputString(
                            "Enter date (DD/MM/YYYY): "
                        );

                    auto start =
                        high_resolution_clock::now();

                    Queue ordersByDate =
                        queue.getOrdersByDate(date);

                    auto end =
                        high_resolution_clock::now();

                    ordersByDate.display();

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 5:
                {
                    clearScreen();

                    cout
                        << "========== FIND BY STATUS ==========\n";

                    OrderStatus status =
                        selectStatus();

                    auto start =
                        high_resolution_clock::now();

                    Queue ordersByStatus =
                        queue.getOrdersByStatus(status);

                    auto end =
                        high_resolution_clock::now();

                    ordersByStatus.display();

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 6:
                {
                    clearScreen();

                    cout
                        << "========== UPDATE STATUS ==========\n";

                    string orderId =
                        inputString(
                            "Enter Order ID: "
                        );

                    OrderStatus newStatus =
                        selectStatus();

                    auto start =
                        high_resolution_clock::now();

                    bool result =
                        queue.updateStatus(
                            orderId,
                            newStatus
                        );

                    auto end =
                        high_resolution_clock::now();

                    if (result)
                        cout
                            << "\nUpdate status successfully.\n";
                    else
                        cout
                            << "\nOrder not found.\n";

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 7:
                {
                    clearScreen();

                    cout
                        << "========== STATISTICS ==========\n";

                    auto start =
                        high_resolution_clock::now();

                    Statistics statistics(queue);

                    statistics.displaySummary();

                    auto end =
                        high_resolution_clock::now();

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 8:
                {
                    clearScreen();

                    cout
                        << "========== SORT BY MONEY ==========\n";

                    auto start =
                        high_resolution_clock::now();

                    queue.sortByMoney();

                    auto end =
                        high_resolution_clock::now();

                    cout
                        << "Orders sorted successfully.\n";

                    cout
                        << "\n========== SORTED ORDERS ==========\n";

                    queue.display();

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 9:
                {
                    clearScreen();

                    cout
                        << "========== DEQUEUE ==========\n";

                    auto start =
                        high_resolution_clock::now();

                    Order removedOrder =
                        queue.dequeue();

                    auto end =
                        high_resolution_clock::now();

                    cout
                        << "Removed order:\n";

                    removedOrder.display();

                    cout
                        << "\n========== QUEUE AFTER DEQUEUE ==========\n";

                    queue.display();

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 10:
                {
                    clearScreen();

                    cout
                        << "========== RELOAD DATA ==========\n";

                    string newFilename =
                        inputString(
                            "Enter new data file path: "
                        );

                    auto start =
                        high_resolution_clock::now();

                    Queue newQueue;

                    loadDataFromFile(
                        newQueue,
                        newFilename
                    );

                    queue = newQueue;

                    filename = newFilename;

                    auto end =
                        high_resolution_clock::now();

                    cout
                        << "\nData reloaded successfully.\n";

                    displayTime(
                        getElapsedTime(start, end)
                    );

                    pauseScreen();
                    break;
                }

                case 0:
                {
                    cout
                        << "\nExiting program...\n";

                    return 0;
                }

                default:
                {
                    cout
                        << "\nInvalid choice. "
                        << "Please choose again.\n";

                    pauseScreen();
                    break;
                }
            }
        }
        catch (const exception& error)
        {
            cout
                << "\nError: "
                << error.what()
                << '\n';

            pauseScreen();
        }
    }

    return 0;
}
