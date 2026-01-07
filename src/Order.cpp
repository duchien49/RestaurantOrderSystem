#include "Order.h"
#include <iostream>
using namespace std;

Order::Order(int id) {
    orderId = id;
    status = PENDING;
}

void Order::addItem(MenuItem item, int quantity) {
    items.push_back(OrderItem(item, quantity));
}

double Order::calculateTotal() {
    double total = 0;
    for (auto &i : items)
        total += i.getTotal();
    return total;
}

void Order::display() {
    cout << "Order ID: " << orderId << endl;
    for (auto &i : items) {
        cout << "- " << i.item.name
             << " x" << i.quantity
             << " = $" << i.getTotal() << endl;
    }
    cout << "Total: $" << calculateTotal() << endl;
}
