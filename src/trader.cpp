#include "trader.hpp"

Trader::Trader(const string& _name, unsigned int _initialMoney)
{
    name = _name;
    money = _initialMoney;
}



void Trader::buy(Stock *_stock, unsigned int _quantity)
{
    if (_quantity <= _stock->getSupply() && money == _stock->getPrice() * _quantity)
    {
        unsigned int totalPrice = 0;
        totalPrice = _stock->getPrice() * _quantity;
        money -= totalPrice;
        portfolio[_stock] += _quantity;
        _stock->setNewSupply(_stock->getSupply() - _quantity);
        cout << name << " purchased " << _quantity <<  " " << _stock->getName() << " for " << totalPrice << ".00 Euros." << endl;
        cout << _stock->getName() << " price is now " << _stock->getPrice();
    }
}


void Trader::sell(Stock *_stock, unsigned int _quantity)
{
    if (portfolio[_stock] >= _quantity)
    {
        totalPrice = _quantity * _stock->getPrice();
        portfolio[_stock] -= _quantity;
        money += totalPrice;
        _stock->setNewSupply(_stock->getSupply() + _quantity);
        cout << name << " sold " << _quantity <<  " " << _stock->getName() << " for " << totalPrice << ".00 Euros." << endl;
        cout << _stock->getName() << " price is now " << _stock->getPrice();
    }
}

void newBuyOrder(Stock *_stock, unsigned int _quantity, unsigned int _price)
{

}


void newSellOrder(Stock *_stock, unsigned int _quantity, unsigned int _price)
{

}

void Trader::showOrders() const
{
    
}

void Trader::showPortfolio() const
{
    
}