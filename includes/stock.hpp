#include <iostream>


using namespace std;

class Stock {

    public :

    Stock(const string& _name, unsigned int _initialLiquidityPool, unsigned int _initialSuppl, unsigned int _liquidityPooly);

    string getName() const;
    unsigned int getPrice() const;
    unsigned int getSupply() const;
    unsigned int getLiquidityPool() const;

    void setNewPrice(unsigned int _supplyAmountBought);
    void setNewSupply(unsigned int _newSupply);

    private :

    string name;
    unsigned int price;
    unsigned int totalSupply;
    unsigned int currentSupply;
    unsigned int liquidityPool;

};