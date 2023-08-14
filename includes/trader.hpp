#include <string>
#include <iostream>
#include <map>

#include "stock.hpp"

using namespace std;

class Trader {

    public :

    Trader(const string& _name, unsigned int _initialMoney)

    void buy(Stock *_stock, unsigned int _quantity);
    void sell(Stock *_stock, unsigned int _quantity);

    void showOrders() const;
    void showPortfolio() const;

    private :

    string name;
    unsigned int money;
    map<Stock*, unsigned int> orders;
    map<Stock*, unsigned int> portfolio;



};