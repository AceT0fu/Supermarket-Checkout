#include "Item.h"
using namespace std;

Item::Item(string new_name, float new_price)
    :   name(new_name), price(new_price) {}

Item::~Item() {}

string const Item::get_name() const {
    return name;
}

float const Item::get_price() const {
    return price;
}

bool Item_compare::operator() (const Item &lhs, const Item &rhs) const {
    return lhs.get_name() < rhs.get_name();
}