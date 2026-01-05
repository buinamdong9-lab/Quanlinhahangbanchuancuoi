#include "Bill.h"
#include "Customer.h"
#include <iostream>
using namespace std;

Bill::Bill()
    : billID(0), dateTime(""), customer(NULL),
    tableCount(0), itemCount(0),
    taxRate(0.08), serviceRate(0.05)
{
    for (int i = 0; i < MAX_TABLES_PER_BILL; ++i)
        tableIDs[i] = -1;
}

Bill::Bill(int _billID, Customer* _customer)
    : billID(_billID), dateTime(""), customer(_customer),
    tableCount(0), itemCount(0),
    taxRate(0.08), serviceRate(0.05)
{
    for (int i = 0; i < MAX_TABLES_PER_BILL; ++i)
        tableIDs[i] = -1;
}

int Bill::getID() const { return billID; }
string Bill::getDateTime() const { return dateTime; }
Customer* Bill::getCustomer() const { return customer; }
int Bill::getTableCount() const { return tableCount; }
int Bill::getItemCount() const { return itemCount; }
double Bill::getTaxRate() const { return taxRate; }
double Bill::getServiceRate() const { return serviceRate; }

void Bill::setDateTime(const string& dt) { dateTime = dt; }

void Bill::setTaxRate(double rate) {
    if (rate < 0) rate = 0;
    taxRate = rate;
}

void Bill::setServiceRate(double rate) {
    if (rate < 0) rate = 0;
    serviceRate = rate;
}

bool Bill::addTable(int tableID) {
    if (tableCount >= MAX_TABLES_PER_BILL) return false;
    tableIDs[tableCount++] = tableID;
    return true;
}

bool Bill::addItem(MenuItem* item, int quantity) {
    if (!item) return false;
    if (itemCount >= MAX_ORDER_ITEMS) return false;
    if (quantity <= 0) return false;

    items[itemCount++] = OrderItem(item, quantity);
    return true;
}

bool Bill::updateItemQuantity(int index, int newQuantity) {
    if (index < 0 || index >= itemCount) return false;
    if (newQuantity < 0) newQuantity = 0;
    items[index].setQuantity(newQuantity);
    return true;
}

bool Bill::removeItem(int index) {
    if (index < 0 || index >= itemCount) return false;
    for (int i = index; i < itemCount - 1; ++i)
        items[i] = items[i + 1];
    --itemCount;
    return true;
}

double Bill::calcSubtotal() const {
    double sum = 0.0;
    for (int i = 0; i < itemCount; ++i)
        sum += items[i].getTotal();
    return sum;
}

double Bill::calcTax() const { return calcSubtotal() * taxRate; }
double Bill::calcServiceFee() const { return calcSubtotal() * serviceRate; }

double Bill::calcTotal() const {
    return calcSubtotal() + calcTax() + calcServiceFee();
}

void Bill::display() const {
    cout << "================= BILL =================\n";
    cout << "Bill ID   : " << billID << endl;
    cout << "Date/Time : " << dateTime << endl;

    if (customer) {
        cout << "Customer  : " << customer->getName()
            << " | Phone: " << customer->getPhone() << endl;
    }

    cout << "Tables    : ";
    for (int i = 0; i < tableCount; ++i) {
        cout << tableIDs[i];
        if (i < tableCount - 1) cout << ", ";
    }
    cout << "\n----------------------------------------\n";

    cout << "Items:\n";
    for (int i = 0; i < itemCount; ++i)
        items[i].display();

    cout << "----------------------------------------\n";
    double subtotal = calcSubtotal();
    double tax = calcTax();
    double service = calcServiceFee();
    double total = calcTotal();

    cout << "Subtotal : " << subtotal << endl;
    cout << "Tax      : " << tax << endl;
    cout << "Service  : " << service << endl;
    cout << "TOTAL    : " << total << endl;
    cout << "========================================\n";
}
