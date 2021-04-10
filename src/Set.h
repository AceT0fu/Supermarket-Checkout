#ifndef CHECKOUT_SET_H
#define CHECKOUT_SET_H

#include <vector>
#include "Item.h"

class Set {
    const vector<Item> items;

public:
    Set(vector<Item> new_items);

    vector<Item> get_items();

    float get_lowest_price();

};


#endif //CHECKOUT_SET_H
