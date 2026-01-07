#include <cassert>
#include "Order.h"

int main() {
    MenuItem item(1, "Test", 10);
    Order order(1);

    order.addItem(item, 2);
    assert(order.calculateTotal() == 20);

    order.status = DONE;
    assert(order.status == DONE);

    return 0;
}
