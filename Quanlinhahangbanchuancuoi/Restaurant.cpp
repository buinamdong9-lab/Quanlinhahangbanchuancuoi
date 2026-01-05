#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Restaurant::Restaurant()
    : name(""),
    menuCount(0),
    customerCount(0),
    billCount(0)
{
    for (int i = 0; i < MAX_MENU_ITEMS; ++i) menu[i] = NULL;
    for (int i = 0; i < MAX_CUSTOMERS; ++i) customers[i] = NULL;
    for (int i = 0; i < MAX_BILLS; ++i) bills[i] = NULL;
}

Restaurant::Restaurant(const string& _name)
    : name(_name),
    menuCount(0),
    customerCount(0),
    billCount(0)
{
    for (int i = 0; i < MAX_MENU_ITEMS; ++i) menu[i] = NULL;
    for (int i = 0; i < MAX_CUSTOMERS; ++i) customers[i] = NULL;
    for (int i = 0; i < MAX_BILLS; ++i) bills[i] = NULL;
}

Restaurant::~Restaurant() {
    for (int i = 0; i < menuCount; ++i) delete menu[i];
    for (int i = 0; i < customerCount; ++i) delete customers[i];
    for (int i = 0; i < billCount; ++i) delete bills[i];
}

// ===== MENU =====

bool Restaurant::loadMenuFromFile(const string& filename) {
    ifstream fin(filename.c_str());
    if (!fin.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return false;
    }

    // clear old menu
    for (int i = 0; i < menuCount; ++i) {
        delete menu[i];
        menu[i] = NULL;
    }
    menuCount = 0;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;

        getline(ss, token, ';');
        char type = token.empty() ? ' ' : token[0];

        getline(ss, token, ';');
        int id = stoi(token);

        getline(ss, token, ';');
        string name = token;

        getline(ss, token, ';');
        double price = stod(token);

        getline(ss, token, ';');
        int stock = stoi(token);

        if (type == 'F') {
            string dishType;
            int servingSize;
            bool isVegetarian;

            getline(ss, dishType, ';');
            getline(ss, token, ';');
            servingSize = stoi(token);

            getline(ss, token, ';');
            isVegetarian = (token == "1");

            if (menuCount < MAX_MENU_ITEMS) {
                menu[menuCount++] = new Food(
                    id, name, price, stock,
                    dishType, servingSize, isVegetarian
                );
            }
        }
        else if (type == 'D') {
            string beverageType;
            bool isAlcoholic;
            bool isHot;

            getline(ss, beverageType, ';');
            getline(ss, token, ';');
            isAlcoholic = (token == "1");
            getline(ss, token, ';');
            isHot = (token == "1");

            if (menuCount < MAX_MENU_ITEMS) {
                menu[menuCount++] = new Drink(
                    id, name, price, stock,
                    beverageType, isAlcoholic, isHot
                );
            }
        }
    }

    fin.close();
    cout << "Loaded " << menuCount << " menu items.\n";
    return true;
}

bool Restaurant::saveMenuToFile(const string& filename) const {
    ofstream fout(filename.c_str());
    if (!fout.is_open()) {
        cout << "Cannot open file to save: " << filename << endl;
        return false;
    }

    for (int i = 0; i < menuCount; ++i) {
        MenuItem* item = menu[i];
        if (!item) continue;

        Food* f = dynamic_cast<Food*>(item);
        Drink* d = dynamic_cast<Drink*>(item);

        if (f) {
            fout << "F;"
                << f->getID() << ";"
                << f->getName() << ";"
                << f->getPrice() << ";"
                << f->getStock() << ";"
                << f->getDishType() << ";"
                << f->getServingSize() << ";"
                << (f->getIsVegetarian() ? 1 : 0)
                << "\n";
        }
        else if (d) {
            fout << "D;"
                << d->getID() << ";"
                << d->getName() << ";"
                << d->getPrice() << ";"
                << d->getStock() << ";"
                << d->getBeverageType() << ";"
                << (d->getIsAlcoholic() ? 1 : 0) << ";"
                << (d->getIsHot() ? 1 : 0)
                << "\n";
        }
    }

    fout.close();
    cout << "Saved menu to file.\n";
    return true;
}

bool Restaurant::addMenuItem(MenuItem* item) {
    if (!item) return false;
    if (menuCount >= MAX_MENU_ITEMS) return false;
    menu[menuCount++] = item;
    return true;
}

bool Restaurant::removeMenuItem(int id) {
    for (int i = 0; i < menuCount; ++i) {
        if (menu[i] && menu[i]->getID() == id) {
            delete menu[i];
            for (int j = i; j < menuCount - 1; ++j)
                menu[j] = menu[j + 1];
            menu[menuCount - 1] = NULL;
            --menuCount;
            return true;
        }
    }
    return false;
}

MenuItem* Restaurant::findMenuItemByID(int id) const {
    for (int i = 0; i < menuCount; ++i) {
        if (menu[i] && menu[i]->getID() == id)
            return menu[i];
    }
    return NULL;
}

bool Restaurant::updateMenuItem(int id,
    const string& newName,
    double newPrice,
    int newStock)
{
    MenuItem* item = findMenuItemByID(id);
    if (!item) return false;
    item->setName(newName);
    item->setPrice(newPrice);
    item->setStock(newStock);
    return true;
}

void Restaurant::showMenu() const {
    cout << "===== MENU (" << menuCount << " items) =====\n";
    for (int i = 0; i < menuCount; ++i) {
        if (menu[i]) menu[i]->display();
    }
    cout << "============================================\n";
}

// ===== CUSTOMER =====

Customer* Restaurant::addCustomer(int id,
    const string& name,
    const string& phone)
{
    if (customerCount >= MAX_CUSTOMERS) return NULL;
    customers[customerCount] = new Customer(id, name, phone);
    return customers[customerCount++];
}

Customer* Restaurant::findCustomerByID(int id) {
    for (int i = 0; i < customerCount; ++i) {
        if (customers[i] && customers[i]->getID() == id)
            return customers[i];
    }
    return NULL;
}

void Restaurant::showCustomers() const {
    cout << "===== CUSTOMERS (" << customerCount << ") =====\n";
    for (int i = 0; i < customerCount; ++i) {
        if (customers[i]) customers[i]->display();
    }
    cout << "=======================================\n";
}

// ===== BILL =====

Bill* Restaurant::createBill(int billID, Customer* customer) {
    if (billCount >= MAX_BILLS) return NULL;
    bills[billCount] = new Bill(billID, customer);
    return bills[billCount++];
}

void Restaurant::finalizeBill(Bill* bill) {
    if (!bill) return;
    Customer* c = bill->getCustomer();
    if (c) {
        double total = bill->calcTotal();
        c->updateRevenue(total);
        c->addBill(bill);
    }
}

void Restaurant::showAllBills() const {
    cout << "===== ALL BILLS (" << billCount << ") =====\n";
    for (int i = 0; i < billCount; ++i) {
        if (bills[i]) bills[i]->display();
    }
    cout << "====================================\n";
}

// ===== STATISTICS =====

double Restaurant::getTotalRevenue() const {
    double sum = 0.0;
    for (int i = 0; i < billCount; ++i) {
        if (bills[i]) sum += bills[i]->calcTotal();
    }
    return sum;
}

Customer* Restaurant::getTopCustomerByRevenue() {
    if (customerCount == 0) return NULL;
    Customer* best = customers[0];
    for (int i = 1; i < customerCount; ++i) {
        if (customers[i]->getTotalRevenue() > best->getTotalRevenue())
            best = customers[i];
    }
    return best;
}
