#ifndef CHECKOUT_ITEM_H
#define CHECKOUT_ITEM_H

#include <string>
using namespace std;

class Item {
    const string name;
    const float price;

public:
    Item(string new_name, float new_price);

    ~Item();

    const string get_name() const;

    const float get_price() const;
};

struct Item_compare {
    bool operator() (const Item& lhs, const Item& rhs) const;
};

#endif //CHECKOUT_ITEM_H