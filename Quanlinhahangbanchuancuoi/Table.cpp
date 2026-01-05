#include "Table.h"
using namespace std;

Table::Table()
    : id(0), status(EMPTY), capacity(0) {
}

Table::Table(int _id, int _capacity)
    : id(_id), status(EMPTY), capacity(_capacity) {
}

int Table::getID() const { return id; }
TableStatus Table::getStatus() const { return status; }
int Table::getCapacity() const { return capacity; }

void Table::setStatus(TableStatus s) { status = s; }

void Table::setCapacity(int c) {
    if (c < 0) c = 0;
    capacity = c;
}

void Table::markWaiting() { status = WAITING; }
void Table::markOccupied() { status = OCCUPIED; }
void Table::markEmpty() { status = EMPTY; }

void Table::display() const {
    cout << "Table ID: " << id
        << " | Capacity: " << capacity
        << " | Status: ";
    switch (status) {
    case EMPTY:    cout << "EMPTY"; break;
    case WAITING:  cout << "WAITING"; break;
    case OCCUPIED: cout << "OCCUPIED"; break;
    default:       cout << "UNKNOWN"; break;
    }
    cout << endl;
}
