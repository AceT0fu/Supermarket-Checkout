#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "Item.h"
#include "Set.h"
using namespace std;


//adds items to stock
void generate_stock(vector<Item> &stock) {
    stock.push_back(Item("Cheese sandwich", 1.5f));
    stock.push_back(Item("Ham sandwich", 2.0f));
    stock.push_back(Item("Orange juice", 0.8f));
    stock.push_back(Item("Coca cola", 1.0f));
    stock.push_back(Item("Biscuits", 0.6f));
    stock.push_back(Item("Crisps", 0.8f));
}

//creates discount sets
void generate_sets(vector<Set> &sets, vector<Item> stock) {
    vector<Item> first_set{stock[0], stock[2], stock[4]};
    vector<Item> second_set{stock[1], stock[3], stock[5]};

    sets.push_back(Set(first_set));
    sets.push_back(Set(second_set));
}


//prints items in stock
void view_stock(vector<Item> stock) {
    cout << "Enter the number of the item you would like to add to your basket:" << endl;

    for (int i = 0; i < stock.size(); i++) {
        Item item = stock[i];
        cout << (i + 1) << ") " << item.get_name() << ": \x9C"
             << item.get_price() << endl;
    }

    cout << "Enter \"d\" to view discount deals" << endl;
    cout << "Enter \"b\" to view your basket" << endl;
    cout << "Enter \"c\" to checkout" << endl;
}

//prints discounts
void view_discounts(vector<Set> sets) {
    cout << endl << "Buy 3 identical items and get 1 free" << endl;
    cout << "Buy an item set and get the cheapest item in the set free:" << endl;

    for (int i = 0; i < sets.size(); i++) {
        vector<Item> items = sets[i].get_items();
        cout << items[0].get_name() << " + " << items[1].get_name()
             << " + " << items[2].get_name() << endl;
    }

    cout << endl;
}

//prints items in basket
void view_basket(map<Item, int, Item_compare> &basket) {
    cout << endl << "Items in the basket:" << endl;

    for (const auto &p : basket) {
        Item item = p.first;
        cout << item.get_name() << ": " << p.second << endl;
    }

    cout << endl;
}

//adds an item to basket
void add_to_basket(vector<Item> stock, map<Item, int, Item_compare> &basket, const string &str) {
    cout << endl;

    int num;
    stringstream ss;

    ss << str;
    ss >> num;

    //checks if item is in the stock
    if (num < 1 || num  > stock.size()) {
        cout << "Item number " << num << " does not exist" << endl << endl;
        return;
    }

    Item item = stock[num - 1];
    string item_name = item.get_name();
    float item_price = item.get_price();

    //adds to basket
    if (basket.count(item) == 0) {
        basket[item] = 1;
    } else {
        basket[item]++;
    }


    cout << item_name << " successfully added to the basket!" << endl;
    cout << "Basket now contains " << basket[item]
         << " " << item_name << endl << endl;
}

//returns if a string is a number
bool is_number(const string &str) {
    string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

//checks if 3 identical items have been bought and returns discount amount
float calculate_tiple_discount(pair<Item, int> pair) {
    float discount = 0.0f;

    while (pair.second >= 3) {
        pair.second -= 3;
        discount += pair.first.get_price();
    }

    return discount;
}


//calculates
void calculate_set_discount(map<Item, int, Item_compare> basket, vector<Set> &sets, ofstream &file, float &total) {
    for (int i = 0; i < sets.size();) {
        vector<Item> items = sets[i].get_items();
        bool complete_set = true;

        for (int j = 0; j < items.size(); j++) {
            if (basket.count(items[j]) == 0) {
                complete_set = false;
                break;
            }
        }

        if (complete_set) {
            for (int j = 0; j < items.size(); j++) {
                basket[items[j]]--;

                if (basket[items[j]] <= 0) {
                    basket.erase(items[j]);
                }
            }
            float discount = sets[i].get_lowest_price();
            file << "Set " << (i + 1) << " complete, " << discount << " discount" << endl;
            total -= discount;
        } else {
            i++;
        }
    }
}

void print_receipt(map<Item, int, Item_compare> &basket, vector<Set> &sets) {
    ofstream file;
    file.open("receipt.txt");

    file << fixed;
    file << setprecision(2);

    float total = 0.0f;
    file << "Receipt:" << endl;

    for (const auto &p : basket) {
        Item item = p.first;
        int amount = p.second;

        float discount = calculate_tiple_discount(p);
        float cost = item.get_price() * amount - discount;

        file << item.get_name() << ": " << amount << " x " << item.get_price();
        if (discount > 0.0f) {
            file << endl << "\t\t - " << discount;
        }
        file << " = " << cost << endl;

        total += cost;
    }

    file << endl;

    calculate_set_discount(basket, sets, file, total);

    file << "Total is " << total;
    file.close();

    cout << "Created file \"receipt.txt\"";
}

int main() {
    cout << fixed;
    cout << setprecision(2);

    vector<Item> stock;
    vector<Set> sets;
    map<Item, int, Item_compare> basket;

    generate_stock(stock);
    generate_sets(sets, stock);

    bool shopping = true;

    while (shopping) {
        view_stock(stock);
        cout << endl << "Type here...";

        string inp;
        cin >> inp;

        if (inp == "c" || inp == "C") {
            shopping = false;
        } else if (inp == "b" || inp == "B") {
            view_basket(basket);
        } else if (inp == "d" || inp == "D") {
            view_discounts(sets);
        } else if (is_number(inp)) {
            add_to_basket(stock, basket, inp);
        } else {
            cout << "Invalid input: " << inp << endl << endl;
        }
    }

    print_receipt(basket, sets);

    return 0;
}