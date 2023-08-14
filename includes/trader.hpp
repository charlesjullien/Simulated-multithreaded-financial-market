#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "stock.hpp"

using namespace std;

struct buyOrder {
    Stock* stock;
    unsigned int quantity;
    unsigned int price;
};

struct sellOrder {
    Stock* stock;
    unsigned int quantity;
    unsigned int price;
};

class Trader {

    public :

    Trader(const string& _name, unsigned int _initialMoney)

    void buy(Stock *_stock, unsigned int _quantity);
    void sell(Stock *_stock, unsigned int _quantity);

    void newBuyOrder(Stock *_stock, unsigned int _quantity, unsigned int _price);
    void newSellOrder(Stock *_stock, unsigned int _quantity, unsigned int _price);

    void showOrders() const;
    void showPortfolio() const;

    private :

    string name;
    unsigned int money;
    map<Stock*, unsigned int> portfolio;
    vector<buyOrder> buyOrderBook;
    vector<sellOrder> sellOrderBook;


};