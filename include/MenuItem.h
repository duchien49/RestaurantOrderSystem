#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
using namespace std;

class MenuItem {
public:
    int id;
    string name;
    double price;
    bool available;

    MenuItem(int id, string name, double price);
};

#endif
