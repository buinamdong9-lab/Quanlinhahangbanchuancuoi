#include "Drink.h"
#include <iostream>
using namespace std;

Drink::Drink()
    : MenuItem(),
    beverageType(""),
    isAlcoholic(false),
    isHot(false)
{
    category = "Drink";
}

Drink::Drink(int _id,
    const string& _name,
    double _price,
    int _stock,
    const string& _beverageType,
    bool _isAlcoholic,
    bool _isHot)
    : MenuItem(_id, _name, _price, "Drink", _stock),
    beverageType(_beverageType),
    isAlcoholic(_isAlcoholic),
    isHot(_isHot) {
}

string Drink::getBeverageType() const { return beverageType; }
bool Drink::getIsAlcoholic() const { return isAlcoholic; }
bool Drink::getIsHot() const { return isHot; }

void Drink::setBeverageType(const string& _beverageType) {
    beverageType = _beverageType;
}

void Drink::setIsAlcoholic(bool _isAlcoholic) {
    isAlcoholic = _isAlcoholic;
}

void Drink::setIsHot(bool _isHot) {
    isHot = _isHot;
}

void Drink::display() const {
    cout << "[Drink] ID: " << id
        << " | Name: " << name
        << " | Price: " << price
        << " | Stock: " << stock
        << " | Type: " << beverageType
        << " | Alcoholic: " << (isAlcoholic ? "Yes" : "No")
        << " | Temperature: " << (isHot ? "Hot" : "Cold")
        << endl;
}

MenuItem* Drink::clone() const {
    return new Drink(*this);
}
