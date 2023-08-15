#include "../includes/Trader.hpp"

Trader::Trader(const string& _name, double _initialMoney)
{
    name = _name;
    money = _initialMoney;
}



void Trader::buy(Stock *_stock, double _quantity)
{
    if (_quantity <= _stock->getSupply() && money >= _stock->getPrice() * _quantity)
    {
        double totalPrice = 0;
        totalPrice = _stock->getPrice() * _quantity;
        money -= totalPrice;
        portfolio[_stock] += _quantity;
        _stock->setNewSupply(_stock->getSupply() - _quantity);
        _stock->setNewPrice(_quantity, 1);
        cout << name << " purchased " << _quantity <<  " " << _stock->getName() << " for " << totalPrice << " Euros." << endl;
        cout << _stock->getName() << " price is now " << _stock->getPrice();
    }
    else
        cout << "Cannot buy for now" << endl;
}


void Trader::sell(Stock *_stock, double _quantity)
{
    if (portfolio[_stock] >= _quantity)
    {
        double totalPrice = 0;
        totalPrice = _quantity * _stock->getPrice();
        portfolio[_stock] -= _quantity;
        money += totalPrice;
        _stock->setNewSupply(_stock->getSupply() + _quantity);
        _stock->setNewPrice(_quantity, 0);
        cout << name << " sold " << _quantity <<  " " << _stock->getName() << " for " << totalPrice << " Euros." << endl;
        cout << _stock->getName() << " price is now " << _stock->getPrice();
    }
    else
        cout << "Doesn't have this stock quantity." << endl;
}

void Trader::newBuyOrder(Stock *_stock, double _quantity, double _price)
{
    if (money >= _quantity * _price)
    {
        buyOrder newOrder = {_stock, _quantity, _price};
        buyOrderBook.push_back(newOrder);
        cout << name << " just setted a new buy order for " << _quantity << " " << _stock->getName() << " at " << _price << " Euros." << endl;   
    }
}


void Trader::newSellOrder(Stock *_stock, double _quantity, double _price)
{
    if (portfolio[_stock] >= _quantity)
    {
        sellOrder newOrder = {_stock, _quantity, _price};
        sellOrderBook.push_back(newOrder);
        cout << name << " just setted a new sell order for " << _quantity << " " << _stock->getName() << " at " << _price << " Euros." << endl;   
    }
}

void Trader::showBuyOrders() const
{
    cout << name << "'s orders:" << endl;
    vector<buyOrder>::const_iterator it = buyOrderBook.begin();
    while (it != buyOrderBook.end())
    {
        const buyOrder& order = *it;
        cout << "Buy order: " << order.quantity << " stocks of " << order.stock->getName() << " at price " << order.price << endl;
        it++;
    }
}

void Trader::showSellOrders() const
{
    cout << name << "'s orders:" << endl;
    vector<sellOrder>::const_iterator it = sellOrderBook.begin();
    while (it != sellOrderBook.end())
    {
        const sellOrder& order = *it;
        cout << "Sell order: " << order.quantity << " stocks of " << order.stock->getName() << " at price " << order.price << endl;
        it++;
    }
}


void Trader::showPortfolio() const
{
    cout << name << "'s portfolio:" << endl;
    map<Stock*, double>::const_iterator it = portfolio.begin();
    while (it != portfolio.end())
    {
        const pair<Stock*, double>& entry = *it;
        cout << entry.first->getName() << ": " << entry.second << " stocks" << endl;
        it++;
    }
}

string Trader::getName() const
{
    return (name);
}

double Trader::getMoney() const
{
    return (money);
}

bool Trader::executeBuyOrders()
{
    bool ordersExecuted = false;

    for (size_t j = 0; j < buyOrderBook.size(); j++)
    {
        buyOrder &order = buyOrderBook[j];
        if (order.stock->getPrice() <= order.price)
        {
            cout << "Executing buy order for " << order.quantity << " " << order.stock->getName() << " at " << order.price << " for trader " << getName() << endl;
            buy(order.stock, order.quantity);
            buyOrderBook.erase(buyOrderBook.begin() + j);
            ordersExecuted = true;
        }
    }

    return ordersExecuted;
}

bool Trader::executeSellOrders()
{
    bool ordersExecuted = false;

    for (size_t j = 0; j < sellOrderBook.size(); j++)
    {
        sellOrder &order = sellOrderBook[j];
        if (order.stock->getPrice() >= order.price)
        {
            cout << "Executing sell order for " << order.quantity << " " << order.stock->getName() << " at " << order.price << " for trader " << getName() << endl;
            sell(order.stock, order.quantity);
            sellOrderBook.erase(sellOrderBook.begin() + j);
            ordersExecuted = true;
        }
    }

    return ordersExecuted;
}
