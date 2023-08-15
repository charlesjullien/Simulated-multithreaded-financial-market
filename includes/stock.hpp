#include <iostream>


using namespace std;

class Stock {

    public :

    Stock(const string& _name, double _initialLiquidityPool, double _initialSupply);

    string getName() const;
    double getPrice() const;
    double getSupply() const;
    double getTotalSupply() const;
    double getLiquidityPool() const;
    bool getIsRunning() const;

    void setNewPrice(double _supplyAmountBought, bool isBuying);
    void setNewSupply(double _newSupply);
    void updatePriceFromThread(double _newLiquidityPool);
    void setIsRunning();

    private :

    string name;
    double price;
    double totalSupply;
    double currentSupply;
    double liquidityPool;
    bool isRunning;

};