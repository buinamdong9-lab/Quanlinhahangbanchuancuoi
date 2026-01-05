#include <iostream>
#include <string>
#include <limits>
#include "Restaurant.h"
using namespace std;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pauseScreen() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==== MENU ITEM OPS ====

void menuLoadMenu(Restaurant& res) {
    string filename;
    cout << "Enter menu file name (default: menu.txt): ";
    getline(cin, filename);
    if (filename.empty()) filename = "menu.txt";

    if (res.loadMenuFromFile(filename))
        cout << "Loaded menu successfully.\n";
    else
        cout << "Failed to load menu.\n";
}

void menuShowMenu(Restaurant& res) {
    res.showMenu();
}

void menuAddMenuItem(Restaurant& res) {
    int typeChoice;
    cout << "Add Menu Item:\n";
    cout << "1. Food\n";
    cout << "2. Drink\n";
    cout << "Your choice: ";
    cin >> typeChoice;
    clearInput();

    int id, stock;
    double price;
    string name;

    cout << "Enter ID: ";
    cin >> id;
    clearInput();

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter stock: ";
    cin >> stock;
    clearInput();

    MenuItem* item = NULL;

    if (typeChoice == 1) {
        string dishType;
        int servingSize;
        char vegChar;
        bool isVegetarian;

        cout << "Enter dish type (appetizer/main course/dessert/...): ";
        getline(cin, dishType);

        cout << "Enter serving size (grams): ";
        cin >> servingSize;

        cout << "Is vegetarian? (y/n): ";
        cin >> vegChar;
        clearInput();
        isVegetarian = (vegChar == 'y' || vegChar == 'Y');

        item = new Food(id, name, price, stock,
            dishType, servingSize, isVegetarian);
    }
    else if (typeChoice == 2) {
        string beverageType;
        char alcoChar, hotChar;
        bool isAlcoholic, isHot;

        cout << "Enter beverage type (soft drink/juice/beer/...): ";
        getline(cin, beverageType);

        cout << "Is alcoholic? (y/n): ";
        cin >> alcoChar;

        cout << "Is hot? (y = hot / n = cold): ";
        cin >> hotChar;
        clearInput();

        isAlcoholic = (alcoChar == 'y' || alcoChar == 'Y');
        isHot = (hotChar == 'y' || hotChar == 'Y');

        item = new Drink(id, name, price, stock,
            beverageType, isAlcoholic, isHot);
    }
    else {
        cout << "Invalid type.\n";
        return;
    }

    if (res.addMenuItem(item))
        cout << "Menu item added.\n";
    else {
        cout << "Failed to add menu item.\n";
        delete item;
    }
}

void menuUpdateMenuItem(Restaurant& res) {
    int id;
    cout << "Enter ID of menu item to update: ";
    cin >> id;
    clearInput();

    string newName;
    double newPrice;
    int newStock;

    cout << "Enter new name: ";
    getline(cin, newName);

    cout << "Enter new price: ";
    cin >> newPrice;

    cout << "Enter new stock: ";
    cin >> newStock;
    clearInput();

    if (res.updateMenuItem(id, newName, newPrice, newStock))
        cout << "Menu item updated.\n";
    else
        cout << "Failed to update (ID not found).\n";
}

void menuRemoveMenuItem(Restaurant& res) {
    int id;
    cout << "Enter ID of menu item to remove: ";
    cin >> id;
    clearInput();

    if (res.removeMenuItem(id))
        cout << "Menu item removed.\n";
    else
        cout << "Failed to remove (ID not found).\n";
}

void menuFindMenuItem(Restaurant& res) {
    int id;
    cout << "Enter ID of menu item to find: ";
    cin >> id;
    clearInput();

    MenuItem* item = res.findMenuItemByID(id);
    if (item) {
        cout << "Found item:\n";
        item->display();
    }
    else {
        cout << "Menu item not found.\n";
    }
}

// ==== CUSTOMER OPS ====

void menuAddCustomer(Restaurant& res) {
    int id;
    string name, phone;

    cout << "Enter customer ID: ";
    cin >> id;
    clearInput();

    cout << "Enter customer name: ";
    getline(cin, name);

    cout << "Enter phone: ";
    getline(cin, phone);

    Customer* c = res.addCustomer(id, name, phone);
    if (c) cout << "Customer added.\n";
    else   cout << "Failed to add customer.\n";
}

void menuShowCustomers(Restaurant& res) {
    res.showCustomers();
}

// ==== BILL OPS ====

void menuCreateBill(Restaurant& res) {
    int billID;
    cout << "Enter new bill ID: ";
    cin >> billID;

    int customerID;
    cout << "Enter customer ID: ";
    cin >> customerID;
    clearInput();

    Customer* c = res.findCustomerByID(customerID);
    if (!c) {
        cout << "Customer not found. Add customer first.\n";
        return;
    }

    Bill* bill = res.createBill(billID, c);
    if (!bill) {
        cout << "Cannot create bill (limit reached).\n";
        return;
    }

    string dt;
    cout << "Enter date/time (e.g., 2025-12-28 19:30): ";
    getline(cin, dt);
    bill->setDateTime(dt);

    while (true) {
        int itemID;
        cout << "Enter menu item ID to add (0 to stop): ";
        cin >> itemID;
        if (itemID == 0) {
            clearInput();
            break;
        }

        MenuItem* item = res.findMenuItemByID(itemID);
        if (!item) {
            cout << "Item not found.\n";
            continue;
        }

        int quantity;
        cout << "Enter quantity: ";
        cin >> quantity;
        clearInput();

        if (!bill->addItem(item, quantity))
            cout << "Failed to add item.\n";
        else
            cout << "Item added.\n";
    }

    res.finalizeBill(bill);
    cout << "Bill saved.\n";
}

void menuShowAllBills(Restaurant& res) {
    res.showAllBills();
}

// ==== STATISTICS ====

void menuShowStatistics(Restaurant& res) {
    double total = res.getTotalRevenue();
    cout << "Total revenue: " << total << endl;

    Customer* top = res.getTopCustomerByRevenue();
    if (top) {
        cout << "Top customer:\n";
        top->display();
    }
    else {
        cout << "No customers yet.\n";
    }
}

// ==== MAIN MENU ====

void printMainMenu() {
    cout << "\n=========== RESTAURANT SYSTEM ===========\n";
    cout << "1. Load menu from file\n";
    cout << "2. Show menu\n";
    cout << "3. Add menu item\n";
    cout << "4. Update menu item\n";
    cout << "5. Remove menu item\n";
    cout << "6. Find menu item by ID\n";
    cout << "7. Add customer\n";
    cout << "8. Show customers\n";
    cout << "9. Create bill\n";
    cout << "10. Show all bills\n";
    cout << "11. Show statistics\n";
    cout << "0. Exit\n";
    cout << "=========================================\n";
    cout << "Your choice: ";
}

int main() {
    Restaurant res("My Restaurant");

    int choice = -1;
    do {
        printMainMenu();
        if (!(cin >> choice)) {
            cin.clear();
            clearInput();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: menuLoadMenu(res);        pauseScreen(); break;
        case 2: menuShowMenu(res);        pauseScreen(); break;
        case 3: menuAddMenuItem(res);     pauseScreen(); break;
        case 4: menuUpdateMenuItem(res);  pauseScreen(); break;
        case 5: menuRemoveMenuItem(res);  pauseScreen(); break;
        case 6: menuFindMenuItem(res);    pauseScreen(); break;
        case 7: menuAddCustomer(res);     pauseScreen(); break;
        case 8: menuShowCustomers(res);   pauseScreen(); break;
        case 9: menuCreateBill(res);      pauseScreen(); break;
        case 10: menuShowAllBills(res);   pauseScreen(); break;
        case 11: menuShowStatistics(res); pauseScreen(); break;
        case 0: cout << "Exiting...\n";   break;
        default:
            cout << "Invalid choice.\n";
            pauseScreen();
            break;
        }

    } while (choice != 0);

    return 0;
}
