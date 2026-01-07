#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "MenuItem.h"

class OrderItem {
public:
    MenuItem item;
    int quantity;

    OrderItem(MenuItem item, int quantity);
    double getTotal();
};

#endif
    