#include "stock.hpp"

// Constructor

Stock::Stock(const string& _name, unsigned int _initialLiquidityPool, unsigned int _initialSupply)
{
    name = _name;
    totalSupply = _initialSupply;
    currentSupply = _initialSupply;
    price = _initialLiquidityPool / _initialSupply;
}

// Getters

string Stock::getName()
{
    return (name);
}

unsigned int Stock::getPrice()
{
    price = liquidityPool / supply;
    return (price);
}

unsigned int Stock::getSupply()
{
    return (currentSupply);
}

unsigned int Stock::getLiquidityPool()
{
    return (liquidityPool);
}

// Setters

void Stock::setNewSupply(unsigned int _newSupply, bool isBuying)
{
    if (isBuying)
        currentSupply -= _newSupply;
    else
        currentSupply += _newSupply; 
}

void Stock::setNewPrice(unsigned int _supplyAmountBought, bool isBuying)
{
    if (isBuying)
    {
        setNewSupply(_supplyAmountBought, 1);
        liquidityPool += _supplyAmountBought * price;
    }
    else
    {
        setNewSupply(_supplyAmountBought, 0);
        liquidityPool -= _supplyAmountBought * price;
    }
    price = getPrice();
}

// Others

