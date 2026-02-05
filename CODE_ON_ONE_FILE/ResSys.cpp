#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// ===== ENUM =====
enum OrderStatus {
    PENDING = 1,
    PREPARING = 2,
    DONE = 3
};

// ===== MENU ITEM =====
class MenuItem {
public:
    int id;
    string name;
    double price;

    MenuItem(int id, string name, double price)
        : id(id), name(name), price(price) {}
};

// ===== ORDER ITEM =====
class OrderItem {
public:
    MenuItem item;
    int quantity;

    OrderItem(MenuItem item, int quantity)
        : item(item), quantity(quantity) {}
};

// ===== ORDER =====
class Order {
public:
    int id;
    vector<OrderItem> items;
    OrderStatus status;
    int tableNumber;

    Order(int id)
        : id(id), status(PENDING), tableNumber(-1) {}

    void addItem(MenuItem item, int qty) {
        items.push_back(OrderItem(item, qty));
    }

    double total() {
        double sum = 0;
        for (auto &i : items)
            sum += i.item.price * i.quantity;
        return sum;
    }
};

// ===== SYSTEM =====
class RestaurantSystem {
public:
    vector<MenuItem> menu;
    vector<Order> orders;
    int nextOrderId = 1;

    RestaurantSystem() {
        menu = {
            {1, "Com Chien Trung", 30000},
            {2, "Mi Tron", 40000},
            {3, "Coffee", 25000},
            {4, "Lau Chay", 80000}
        };
    }

    void viewMenu() {
        cout << "\n--- MENU ---\n";
        for (auto &m : menu)
            cout << m.id << ". " << m.name << " - " << m.price << " VND\n";
    }

    MenuItem* findMenuItem(int id) {
        for (auto &m : menu)
            if (m.id == id) return &m;
        return nullptr;
    }

    Order* createOrder() {
        orders.push_back(Order(nextOrderId++));
        cout << "Order created. ID: " << orders.back().id << endl;
        return &orders.back();
    }

    Order* findOrder(int id) {
        for (auto &o : orders)
            if (o.id == id) return &o;
        return nullptr;
    }

    void saveOrder(Order &o) {
        ofstream file("data/orders.txt", ios::app);
        file << o.id << "," << o.tableNumber << "," << o.status << "," << o.total() << endl;
        file.close();

        ofstream itemFile("data/order_items.txt", ios::app);
        for (auto &i : o.items) {
            itemFile << o.id << "," << i.item.name << "," << i.quantity << endl;
        }
        itemFile.close();
    }
};

// ===== CUSTOMER =====
class Customer {
public:
    RestaurantSystem &system;
    Order* cart = nullptr;

    Customer(RestaurantSystem &sys) : system(sys) {}

    void viewMenu() {
        system.viewMenu();
    }

    void createOrder() {
        cart = system.createOrder();
    }

    void addToCart(int menuId, int qty) {
        if (!cart) return;
        MenuItem* item = system.findMenuItem(menuId);
        if (item) {
            cart->addItem(*item, qty);
            cout << "Added to cart\n";
        }
    }
};

// ===== STAFF =====
class Staff {
public:
    RestaurantSystem &system;

    Staff(RestaurantSystem &sys) : system(sys) {}

    void assignTable(int orderId, int table) {
        Order* o = system.findOrder(orderId);
        if (o) {
            o->tableNumber = table;
            cout << "Table assigned\n";
        }
    }

    void manageOrders(int orderId) {
        Order* o = system.findOrder(orderId);
        if (o) {
            o->status = PREPARING;
            cout << "Order is preparing\n";
        }
    }

    void processPayment(int orderId) {
        Order* o = system.findOrder(orderId);
        if (o && o->status == DONE) {
            system.saveOrder(*o);
            cout << "Paid: " << o->total() << " VND\n";
        }
    }
};

// ===== MANAGER =====
class Manager {
public:
    void manageStaff() {
        cout << "Manager managing staff...\n";
    }

    void viewDashboard() {
        cout << "Manager dashboard\n";
    }
};

// ===== ADMIN =====
class Admin {
public:
    void manageStaff() {
        cout << "Admin managing staff...\n";
    }

    void manageGoods() {
        cout << "Admin managing goods...\n";
    }

    void viewDashboard() {
        cout << "Admin dashboard\n";
    }
};

// ===== MAIN =====
int main() {
    RestaurantSystem system;

    Customer customer(system);
    Staff staff(system);
    Manager manager;
    Admin admin;

    customer.viewMenu();
    customer.createOrder();
    customer.addToCart(1, 2);
    customer.addToCart(3, 1);

    staff.assignTable(1, 5);
    staff.manageOrders(1);

    Order* o = system.findOrder(1);
    if (o) o->status = DONE;

    staff.processPayment(1);

    manager.viewDashboard();
    admin.manageGoods();

    return 0;
}
