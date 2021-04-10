#include "Set.h"
#include <assert.h>

Set::Set(vector<Item> new_items)
    : items(new_items) {
    assert (new_items.size() == 3);
}

vector<Item> Set::get_items() {
    return items;
}

float Set::get_lowest_price() {
    float lowest = items[0].get_price();

    for (int i = 0; i < items.size() - 1; i++) {
        lowest = min(items[i].get_price(), items[i + 1].get_price());
    }
    return lowest;
}