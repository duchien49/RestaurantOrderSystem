#include "RestaurantSystem.h"
#include <iostream>
using namespace std;

RestaurantSystem::RestaurantSystem() {
    nextOrderId = 1;
    menu.push_back(MenuItem(1, "Fried Rice", 5));
    menu.push_back(MenuItem(2, "Noodle Soup", 4.5));
}

void RestaurantSystem::displayMenu() {
    for (auto &m : menu)
        cout << m.id << ". " << m.name << " - $" << m.price << endl;
}

void RestaurantSystem::createOrder() {
    orders.push_back(Order(nextOrderId));
    cout << "Created Order ID: " << nextOrderId++ << endl;
}

void RestaurantSystem::addItemToOrder() {
    int orderId, itemId, qty;
    cin >> orderId >> itemId >> qty;
    orders[orderId - 1].addItem(menu[itemId - 1], qty);
}

void RestaurantSystem::viewOrder() {
    int id; cin >> id;
    orders[id - 1].display();
}

void RestaurantSystem::updateStatus() {
    int id, s;
    cin >> id >> s;
    orders[id - 1].status = (OrderStatus)(s - 1);
}

void RestaurantSystem::checkout() {
    int id; cin >> id;
    cout << "Total: $" << orders[id - 1].calculateTotal() << endl;
}

void RestaurantSystem::run() {
    int c;
    do {
        cout << "1.Menu 2.New Order 3.Add Item 4.View 5.Status 6.Pay 0.Exit\n";
        cin >> c;
        if (c == 1) displayMenu();
        else if (c == 2) createOrder();
        else if (c == 3) addItemToOrder();
        else if (c == 4) viewOrder();
        else if (c == 5) updateStatus();
        else if (c == 6) checkout();
    } while (c != 0);
}
