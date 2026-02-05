#include <iostream>
#include <vector>
using namespace std;

enum OrderStatus {
    PENDING = 1,
    PREPARING = 2,
    DONE = 3
};

struct MenuItem {
    int id;
    string name;
    double price;
};

struct OrderItem {
    MenuItem item;
    int quantity;
};

struct Order {
    int id;
    vector<OrderItem> items;
    OrderStatus status;
};  

vector<MenuItem> menu = {
    {1, "Com Chien Trung", 30000},
    {2, "Mi Tron", 40000},
    {3, "Coffee", 25000},
    {4, "Lau Chay", 80000},
    {5, "Nuoc Ep", 30000},
    {6, "Nuoc Ngot", 20000},
    {7, "Com Tam", 35000},
    {8, "Com Chay", 20000}
};

vector<Order> orders;
int nextOrderId = 1;

void displayMenu() {
    cout << "\n MENU \n";
    for (auto &m : menu) {
        cout << m.id << ". " << m.name
             << " - " << m.price << " VND\n";
    }
}

void createOrder() {
    Order o;
    o.id = nextOrderId++;
    o.status = PENDING;
    orders.push_back(o);

    cout << "New order created. Order ID: "
         << o.id << endl;
}

Order* findOrder(int id) {
    for (auto &o : orders)
        if (o.id == id)
            return &o;
    return nullptr;
}

void addItemToOrder() {
    int orderId, menuId, qty;

    cout << "Enter Order ID: ";
    cin >> orderId;

    Order* o = findOrder(orderId);
    if (!o) {
        cout << "Order not found!\n";
        return; 
    }

    cout << "Enter Menu ID: ";
    cin >> menuId;
    cout << "Enter Quantity: ";
    cin >> qty;

    for (auto &m : menu) {
        if (m.id == menuId) {
            o->items.push_back({m, qty});
            cout << "Item added successfully!\n";
            return;
        }
    }

    cout << "Menu item not found!\n";
}

void updateOrderStatus() {
    int orderId, status;

    cout << "Enter Order ID: ";
    cin >> orderId;

    Order* o = findOrder(orderId);
    if (!o) {
        cout << "Order not found!\n";
        return;
    }

    cout << "Choose status (1.Pending 2.Preparing 3.Done): ";
    cin >> status;

    o->status = (OrderStatus)status;
    cout << "Order status updated successfully!\n";
}

double calculateTotal(Order &o) {
    double total = 0;
    for (auto &i : o.items)
        total += i.item.price * i.quantity;
    return total;
}

void checkout() {
    int orderId;
    cout << "Enter Order ID: ";
    cin >> orderId;

    Order* o = findOrder(orderId);
    if (!o) {
        cout << "Order not found!\n";
        return;
    }

    if (o->status != DONE) {
        cout << "Order not ready for payment!\n";
        return;
    }

    cout << "Payment successful!\n";
    cout << "Total: " << calculateTotal(*o)
         << " VND\n";
}

int main() {
    int choice;

    do {
        cout << "\n RESTAURANT ORDER SYSTEM \n";
        cout << "1. Display Menu\n";
        cout << "2. Create Order\n";
        cout << "3. Add Item to Order\n";
        cout << "5. Update Order Status\n";
        cout << "6. Checkout\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayMenu(); break;
            case 2: createOrder(); break;
            case 3: addItemToOrder(); break;
            case 5: updateOrderStatus(); break;
            case 6: checkout(); break;
        }
    } while (choice != 0);

    return 0;
}
