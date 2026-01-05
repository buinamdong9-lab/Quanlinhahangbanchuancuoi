#include "Customer.h"
#include "Bill.h"
#include <iostream>
using namespace std;

Customer::Customer()
    : id(0), name(""), phone(""),
    totalRevenue(0.0), billCount(0)
{
    for (int i = 0; i < MAX_BILLS_PER_CUSTOMER; ++i)
        historyBills[i] = NULL;
}

Customer::Customer(int _id, const string& _name, const string& _phone)
    : id(_id), name(_name), phone(_phone),
    totalRevenue(0.0), billCount(0)
{
    for (int i = 0; i < MAX_BILLS_PER_CUSTOMER; ++i)
        historyBills[i] = NULL;
}

int Customer::getID() const { return id; }
string Customer::getName() const { return name; }
string Customer::getPhone() const { return phone; }
double Customer::getTotalRevenue() const { return totalRevenue; }
int Customer::getBillCount() const { return billCount; }

void Customer::setName(const string& _name) { name = _name; }
void Customer::setPhone(const string& _phone) { phone = _phone; }

void Customer::addBill(Bill* bill) {
    if (!bill) return;
    if (billCount < MAX_BILLS_PER_CUSTOMER) {
        historyBills[billCount++] = bill;
    }
}

void Customer::updateRevenue(double amount) {
    totalRevenue += amount;
}

void Customer::display() const {
    cout << "Customer ID: " << id
        << " | Name: " << name
        << " | Phone: " << phone
        << " | Total revenue: " << totalRevenue
        << " | Bills: " << billCount
        << endl;
}
