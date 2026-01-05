#include "Food.h"
#include <iostream>
using namespace std;

Food::Food()
    : MenuItem(),
    dishType(""),
    servingSize(0),
    isVegetarian(false)
{
    category = "Food";
}

Food::Food(int _id,
    const string& _name,
    double _price,
    int _stock,
    const string& _dishType,
    int _servingSize,
    bool _isVegetarian)
    : MenuItem(_id, _name, _price, "Food", _stock),
    dishType(_dishType),
    servingSize(_servingSize),
    isVegetarian(_isVegetarian) {
}

string Food::getDishType() const { return dishType; }
int Food::getServingSize() const { return servingSize; }
bool Food::getIsVegetarian() const { return isVegetarian; }

void Food::setDishType(const string& _dishType) { dishType = _dishType; }

void Food::setServingSize(int _servingSize) {
    if (_servingSize < 0) _servingSize = 0;
    servingSize = _servingSize;
}

void Food::setIsVegetarian(bool _isVegetarian) {
    isVegetarian = _isVegetarian;
}

void Food::display() const {
    cout << "[Food] ID: " << id
        << " | Name: " << name
        << " | Price: " << price
        << " | Stock: " << stock
        << " | Dish type: " << dishType
        << " | Serving: " << servingSize << " g"
        << " | Vegetarian: " << (isVegetarian ? "Yes" : "No")
        << endl;
}

MenuItem* Food::clone() const {
    return new Food(*this);
}
