#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "OrderItem.h"

enum OrderStatus { PENDING, COOKING, DONE, PAID };

class Order {
public:
    int orderId;
    vector<OrderItem> items;
    OrderStatus status;

    Order(int id);
    void addItem(MenuItem item, int quantity);
    double calculateTotal();
    void display();
};

#endif
