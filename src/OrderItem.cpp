#include "OrderItem.h"

OrderItem::OrderItem(MenuItem item, int quantity)
    : item(item), quantity(quantity) {}

double OrderItem::getTotal() {
    return item.price * quantity;
}
