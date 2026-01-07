#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================== ENUM ==================
enum OrderStatus {
    PENDING,
    COOKING,
    DONE,
    PAID
};

// ================== MENU ITEM ==================
class MenuItem {
public:
    int id;
    string name;
    double price;
    bool available;

    MenuItem(int id, string name, double price) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->available = true;
    }
};

//Order item
class OrderItem {
public:
    MenuItem item;
    int quantity;

    OrderItem(MenuItem item, int quantity)
        : item(item), quantity(quantity) {}

    double getTotal() {
        return item.price * quantity;
    }
};

//Order
class Order {
public:
    int orderId;
    vector<OrderItem> items;
    OrderStatus status;

    Order(int id) {
        orderId = id;
        status = PENDING;
    }

    void addItem(MenuItem item, int quantity) {
        items.push_back(OrderItem(item, quantity));
    }

    double calculateTotal() {
        double total = 0;
        for (auto &i : items)
            total += i.getTotal();
        return total;
    }

    void display() {
        cout << "\nOrder ID: " << orderId << endl;
        cout << "Items:\n";
        for (auto &i : items) {
            cout << "- " << i.item.name
                 << " x" << i.quantity
                 << " = $" << i.getTotal() << endl;
        }
        cout << "Total: $" << calculateTotal() << endl;
    }
};

//System
class RestaurantSystem {
private:
    vector<MenuItem> menu;
    vector<Order> orders;
    int nextOrderId = 1;

public:
    RestaurantSystem() {
        menu.push_back(MenuItem(1, "Fried Rice", 5.0));
        menu.push_back(MenuItem(2, "Noodle Soup", 4.5));
        menu.push_back(MenuItem(3, "Grilled Chicken", 7.0));
    }

    void displayMenu() {
        cout << "\n=== MENU ===\n";
        for (auto &m : menu) {
            cout << m.id << ". " << m.name << " - $" << m.price << endl;
        }
    }

    void createOrder() {
        orders.push_back(Order(nextOrderId));
        cout << "New order created. Order ID: " << nextOrderId << endl;
        nextOrderId++;
    }

    Order* findOrder(int id) {
        for (auto &o : orders) {
            if (o.orderId == id)
                return &o;
        }
        return nullptr;
    }

    MenuItem* findMenuItem(int id) {
        for (auto &m : menu) {
            if (m.id == id)
                return &m;
        }
        return nullptr;
    }

    void addItemToOrder() {
        int orderId, menuId, quantity;
        cout << "Enter Order ID: ";
        cin >> orderId;

        Order* order = findOrder(orderId);
        if (!order) {
            cout << "Order not found!\n";
            return;
        }

        displayMenu();
        cout << "Enter Menu Item ID: ";
        cin >> menuId;
        MenuItem* item = findMenuItem(menuId);

        if (!item) {
            cout << "Item not found!\n";
            return;
        }

        cout << "Enter quantity: ";
        cin >> quantity;

        order->addItem(*item, quantity);
        cout << "Item added successfully.\n";
    }

    void viewOrder() {
        int id;
        cout << "Enter Order ID: ";
        cin >> id;

        Order* order = findOrder(id);
        if (!order) {
            cout << "Order not found!\n";
            return;
        }
        order->display();
    }

    void updateStatus() {
        int id;
        cout << "Enter Order ID: ";
        cin >> id;

        Order* order = findOrder(id);
        if (!order) {
            cout << "Order not found!\n";
            return;
        }

        cout << "1. Pending\n2. Cooking\n3. Done\n4. Paid\nChoose status: ";
        int choice;
        cin >> choice;

        order->status = static_cast<OrderStatus>(choice - 1);
        cout << "Status updated.\n";
    }

    void checkout() {
        int id;
        cout << "Enter Order ID: ";
        cin >> id;

        Order* order = findOrder(id);
        if (!order) {
            cout << "Order not found!\n";
            return;
        }

        if (order->status != DONE) {
            cout << "Order not ready for payment!\n";
            return;
        }

        order->status = PAID;
        cout << "Payment successful. Total: $" << order->calculateTotal() << endl;
    }

    void run() {
        int choice;
        do {
            cout << "\n===== RESTAURANT ORDER MANAGEMENT =====\n";
            cout << "1. Display Menu\n";
            cout << "2. Create Order\n";
            cout << "3. Add Item to Order\n";
            cout << "4. View Order\n";
            cout << "5. Update Order Status\n";
            cout << "6. Checkout\n";
            cout << "0. Exit\n";
            cout << "Choose: ";
            cin >> choice;

            switch (choice) {
                case 1: displayMenu(); break;
                case 2: createOrder(); break;
                case 3: addItemToOrder(); break;
                case 4: viewOrder(); break;
                case 5: updateStatus(); break;
                case 6: checkout(); break;
                case 0: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }
};

int main() {
    RestaurantSystem system;
    system.run();
    return 0;
}
