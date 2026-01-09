#ifndef BILL_H
#define BILL_H

#include <string>
#include "config.h"
#include "Order.h"
using namespace std;

class Customer; // forward declaration

class Bill {
private:
    int billID;
    string dateTime;
    Customer* customer;

    int tableIDs[MAX_TABLES_PER_BILL];
    int tableCount;

    OrderItem items[MAX_ORDER_ITEMS];
    int itemCount;

    double taxRate;
    double serviceRate;

public:
    Bill();
    Bill(int _billID, Customer* _customer);

    int getID() const;
    string getDateTime() const;
    Customer* getCustomer() const;
    int getTableCount() const;
    int getItemCount() const;

    double getTaxRate() const;
    double getServiceRate() const;

    void setDateTime(const string& dt);
    void setTaxRate(double rate);
    void setServiceRate(double rate);

    bool addTable(int tableID);
    bool addItem(MenuItem* item, int quantity);
    bool updateItemQuantity(int index, int newQuantity);
    bool removeItem(int index);

    double calcSubtotal() const;
    double calcTax() const;
    double calcServiceFee() const;
    double calcTotal() const;

    void display() const;
};

#endif
