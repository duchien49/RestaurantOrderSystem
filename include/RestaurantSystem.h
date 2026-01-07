#ifndef RESTAURANTSYSTEM_H
#define RESTAURANTSYSTEM_H

#include <vector>
#include "Order.h"
#include "MenuItem.h"

class RestaurantSystem {
private:
    vector<MenuItem> menu;
    vector<Order> orders;
    int nextOrderId;

public:
    RestaurantSystem();
    void displayMenu();
    void createOrder();
    void addItemToOrder();
    void viewOrder();
    void updateStatus();
    void checkout();
    void run();
};

#endif
