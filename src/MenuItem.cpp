#include "MenuItem.h"

MenuItem::MenuItem(int id, string name, double price) {
    this->id = id;
    this->name = name;
    this->price = price;
    this->available = true;
}
