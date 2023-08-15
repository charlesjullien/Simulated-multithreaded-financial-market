#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include "../includes/Trader.hpp"

using namespace std;

void simulateStockPriceChanges(Stock& stock, mutex& outputMutex)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-0.03, 0.03);
    uniform_real_distribution<> spacesNb(0, 150);

    while (true)
    {
        this_thread::sleep_for(chrono::seconds(20));

        double currentLiquidity = stock.getLiquidityPool();
        double percentageChange = dis(gen);
        double newLiquidityPool = currentLiquidity + currentLiquidity * percentageChange;
        unsigned int spaces = spacesNb(gen);

        if (newLiquidityPool > 0)
        {
            stock.updatePriceFromThread(newLiquidityPool);
            std::lock_guard<std::mutex> lock(outputMutex);
            for (int i = 0; i < spaces; i++)
            {
                cout << " ";
            }
            if (percentageChange < 0)
                cout << "\033[31m" << stock.getName() << " : " << stock.getPrice() << "\033[0m" << endl;
            else
                cout << "\033[32m" << stock.getName() << " : " << stock.getPrice() << "\033[0m" << endl;
                
            // lock.unlock();
        }
    }
}

int main(int ac, char **av)
{
    vector<Stock> stocks;
    vector<Trader> traders;
    unordered_map<string, int> commandMap =
    {
        {"create trader", 1},
        {"create stock", 2},
        {"display portfolio", 3},
        {"display order book", 4},
        {"create order", 5},
        {"buy", 6},
        {"sell", 7},
        {"display stocks", 8},
        {"display traders", 9},
        {"quit", 10}
    };
    vector<thread> priceThreads;
    string command;
    mutex outputMutex;
    mutex priceChangeMutex;

    ////

    traders.emplace_back("John", 100000);
    traders.emplace_back("Bob", 705430);
    stocks.emplace_back("Hsbc", 600000, 50000);
    stocks.emplace_back("Tesla", 1350000, 70000);

    ////

    while (command != "quit")
    {
        cout << "Enter a command (create trader, create stock, display portfolio, display order book, create order, buy/sell, display stocks, display traders, quit): " << endl;
        getline(cin, command);
        cout << "Command entered: " << command << endl;

        switch (commandMap[command])
        {
            case 1: // create trader
            {
                cout << "Creating a new trader..." << endl;
                string name;
                double initialMoney;
                cout << "Enter trader's name: ";
                getline(cin, name);
                cout << "Enter initial money: ";
                cin >> initialMoney;
                traders.emplace_back(name, initialMoney);
                break;
            }
            case 2: // create stock
            {
                cout << "Creating a new stock..." << endl;
                string name;
                double initialLiquidityPool;
                double initialSupply;
                cout << "Enter stock's name: ";
                getline(cin, name);
                cout << "Enter initial liquidity pool: ";
                cin >> initialLiquidityPool;
                cout << "Enter initial supply: ";
                cin >> initialSupply;
                stocks.emplace_back(name, initialLiquidityPool, initialSupply);
                break;
            }
            case 3: // display portfolio
            {
                string traderName;
                cout << "Enter trader's name: ";
                getline(cin, traderName);

                for (const Trader& trader : traders)
                {
                    if (trader.getName() == traderName)
                    {
                        trader.showPortfolio();
                        break;
                    }
                }
                break;
            }
            case 4: // display order book
            {
                string traderName;
                cout << "Enter trader's name: ";
                getline(cin, traderName);

                for (const Trader& trader : traders)
                {
                    if (trader.getName() == traderName)
                    {
                        trader.showBuyOrders();
                        trader.showSellOrders();
                        break;
                    }
                }
                break;
            }
            case 5: // create order
            {
                string traderName;
                cout << "Enter trader's name: ";
                getline(cin, traderName);

                for (size_t i = 0; i < traders.size(); i++)
                {
                    if (traders[i].getName() == traderName)
                    {
                        string orderType;
                        cout << "Enter order type (buy/sell): ";
                        getline(cin, orderType);

                        if (orderType == "buy")
                        {
                            string stockName;
                            double quantity;
                            double price;
                            cout << "Enter the stock name to buy: ";
                            getline(cin, stockName);
                            cout << "Enter the quantity to buy: ";
                            cin >> quantity;
                            cout << "Enter the price to activate the order: ";
                            cin >> price;
                            for (size_t j = 0; j < stocks.size(); j++)
                            {
                                if (stocks[j].getName() == stockName)
                                {
                                    traders[i].newBuyOrder(&stocks[j], quantity, price);
                                }
                            }
                        }
                        else if (orderType == "sell")
                        {
                            string stockName;
                            double quantity;
                            double price;
                            cout << "Enter the stock name to sell: ";
                            getline(cin, stockName);
                            cout << "Enter the quantity to sell: ";
                            cin >> quantity;
                            cout << "Enter the price to activate the order: ";
                            cin >> price;
                            for (size_t j = 0; j < stocks.size(); j++)
                            {
                                if (stocks[j].getName() == stockName)
                                {
                                    traders[i].newSellOrder(&stocks[j], quantity, price);
                                }
                            }
                        }
                        else
                        {
                            cout << "Invalid order type" << endl;
                        }
                        break;
                    }
                }
                break;
            }
            case 6: // buy
            {
                string traderName;
                cout << "Enter trader's name: ";
                getline(cin, traderName);

                for (size_t i = 0; i < traders.size(); i++)
                {
                    if (traders[i].getName() == traderName)
                    {
                        double quantity;
                        string stockName;
                        cout << "Enter the stock name to buy: ";
                        getline(cin, stockName);
                        cout << "Enter the quantity to buy: ";
                        cin >> quantity;
                        for (size_t j = 0; j < stocks.size(); j++)
                        {
                            if (stocks[j].getName() == stockName)
                            {
                                traders[i].buy(&stocks[j], quantity);
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case 7: // sell
            {
                string traderName;
                cout << "Enter trader's name: ";
                getline(cin, traderName);

                for (size_t i = 0; i < traders.size(); ++i)
                {
                    if (traders[i].getName() == traderName)
                    {
                        string stockName;
                        double quantity;
                        cout << "Enter the stock name to sell: ";
                        getline(cin, stockName);
                        cout << "Enter the quantity to sell: ";
                        cin >> quantity;
                        for (size_t j = 0; j < stocks.size(); j++)
                        {
                            if (stocks[j].getName() == stockName)
                            {
                                traders[i].sell(&stocks[j], quantity);
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case 8: // display stocks
            {
                for (const Stock& stock : stocks)
                {
                    cout << "Stock: " << stock.getName() << endl;
                    cout << "Initial Supply: " << stock.getTotalSupply() << endl;
                    cout << "Current Supply: " << stock.getSupply() << endl;
                    cout << "Price: " << stock.getPrice() << endl;
                    cout << "Liquidity Pool: " << stock.getLiquidityPool() << endl;
                    cout << "--------------------------" << endl;
                }
                break;
            }
            case 9: // display traders
            {
                for (const Trader& trader : traders)
                {
                    cout << "Trader: " << trader.getName() << endl;
                    cout << "Money: " << trader.getMoney() << endl;
                    cout << "Portfolio: " << endl;
                    trader.showPortfolio();
                    cout << "--------------------------" << endl;
                }
                break;
            }
            case 10: // quit
            {
                for (size_t i = 0; i < priceThreads.size(); ++i)
                {
                    if (priceThreads[i].joinable())
                        priceThreads[i].join();
                }
                break;
            }
            default:
                cout << "Invalid command..." << endl;
                break;
        }
        for (size_t i = 0; i < traders.size(); i++)
        {
            Trader& trader = traders[i];
            bool ordersExecuted = false;
            ordersExecuted = trader.executeBuyOrders();
            ordersExecuted = trader.executeSellOrders();
        }
        {
            std::lock_guard<std::mutex> lock(priceChangeMutex);
            for (size_t i = 0; i < stocks.size(); ++i)
            {
                if (stocks[i].getIsRunning() == false)
                {
                    priceThreads.emplace_back(simulateStockPriceChanges, ref(stocks[i]), ref(outputMutex));
                    stocks[i].setIsRunning();
                }
            }
        }
    }
    for (size_t i = 0; i < priceThreads.size(); ++i)
    {
        if (priceThreads[i].joinable())
            priceThreads[i].join();
    }
    return 0;
}