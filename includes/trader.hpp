#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Stock.hpp"

using namespace std;

struct buyOrder {
    Stock* stock;
    double quantity;
    double price;
};

struct sellOrder {
    Stock* stock;
    double quantity;
    double price;
};

class Trader {

    public :

    Trader(const string& _name, double _initialMoney);

    void buy(Stock *_stock, double _quantity);
    void sell(Stock *_stock, double _quantity);

    void newBuyOrder(Stock *_stock, double _quantity, double _price);
    void newSellOrder(Stock *_stock, double _quantity, double _price);

    bool executeBuyOrders();
    bool executeSellOrders();

    void showBuyOrders() const;
    void showSellOrders() const;
    void showPortfolio() const;
    string getName() const;
    double getMoney() const;


    private :

    string name;
    double money;
    map<Stock*, double> portfolio;
    vector<buyOrder> buyOrderBook;
    vector<sellOrder> sellOrderBook;


};