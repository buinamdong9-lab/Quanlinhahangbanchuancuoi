#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "MenuItem.h"

class OrderItem {
private:
    MenuItem* item;
    int quantity;

public:
    OrderItem();
    OrderItem(MenuItem* _item, int _quantity);

    MenuItem* getItem() const;
    int getQuantity() const;

    void setItem(MenuItem* _item);
    void setQuantity(int q);

    double getTotal() const;
    void display() const;
};

#endif // ORDERITEM_H
