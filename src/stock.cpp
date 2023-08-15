#include "../includes/Stock.hpp"


Stock::Stock(const string& _name, double _initialLiquidityPool, double _initialSupply)
{
    name = _name;
    totalSupply = _initialSupply;
    currentSupply = _initialSupply;
    liquidityPool = _initialLiquidityPool;
    price = _initialLiquidityPool / _initialSupply;
}


string Stock::getName() const
{
    return (name);
}

double Stock::getPrice() const
{
    return (liquidityPool / currentSupply);
}

double Stock::getSupply() const 
{
    return (currentSupply);
}

double Stock::getTotalSupply() const 
{
    return (totalSupply);
}

double Stock::getLiquidityPool() const 
{
    return (liquidityPool);
}

bool Stock::getIsRunning() const
{
    return (isRunning);
}



void Stock::setNewSupply(double _newSupply)
{
    currentSupply = _newSupply;
}

void Stock::setNewPrice(double _supplyAmountBought, bool isBuying)
{
    if (isBuying)
        liquidityPool += _supplyAmountBought * price;
    else
        liquidityPool -= _supplyAmountBought * price;
    price = liquidityPool / currentSupply;
}

void Stock::updatePriceFromThread(double _newLiquidityPool)
{
    liquidityPool = _newLiquidityPool;
    price = liquidityPool / currentSupply;
}

void Stock::setIsRunning()
{
    isRunning = true;
}


