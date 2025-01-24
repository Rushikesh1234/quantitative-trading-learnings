#include "OrderBook/OrderBook.hpp"
#include "ExecutionEngine/ExecutionEngine.hpp"
#include "LatencySimulator/LatencySimulator.hpp"
#include "RiskManagement/RiskManager.hpp"

int main()
{
    OrderBook orderBook;
    ExecutionEngine executionEngine;
    LatencySimputor latencySimulator;
    RiskManager riskManager(10.0, 20.0, 100000.0);

    latencySimulator.simulateLatency(100);
    executionEngine.executeTrade({0, "USD", 100000.0, 0, false});
    latencySimulator.simulateLatency(50);
    executionEngine.executeTrade({0, "AAPL", 0.0, 0, true});

    latencySimulator.simulateLatency(100);
    orderBook.placeOrder(true, 100.5, 10);
    orderBook.placeOrder(false, 101.0, 5);
    orderBook.placeOrder(true, 102.3, 15);
    orderBook.placeOrder(false, 99.8, 20);
    orderBook.placeOrder(true, 100.7, 25);
    orderBook.placeOrder(false, 101.2, 8);
    orderBook.placeOrder(true, 103.0, 12);
    orderBook.placeOrder(false, 98.5, 30);
    orderBook.placeOrder(true, 100.9, 18);
    orderBook.placeOrder(false, 102.0, 10);
    orderBook.placeOrder(true, 101.5, 7);
    orderBook.placeOrder(false, 100.2, 16);
    orderBook.placeOrder(true, 99.5, 40);
    orderBook.placeOrder(false, 103.5, 6);
    orderBook.placeOrder(true, 104.0, 9);
    orderBook.placeOrder(false, 97.0, 25);
    orderBook.placeOrder(true, 101.1, 22);
    orderBook.placeOrder(false, 100.8, 13);
    orderBook.placeOrder(true, 98.2, 35);
    orderBook.placeOrder(false, 105.0, 4);

    latencySimulator.simulateLatency(100);
    orderBook.matchOrder();

    executionEngine.executeTrade({1, "AAPL", 150.5, 5, true});
    latencySimulator.simulateLatency(10000);
    executionEngine.executeTrade({2, "AAPL", 149.5, 5, false});
    
    orderBook.printOrderBook();
    latencySimulator.simulateLatency(100);
    executionEngine.printAccountStatus();

    riskManager.setPositionLimit("AAPL", 500);
    std::string symbol = "AAPL";
    double tradePrice = 150.5;
    int tradeQuantity = 300;
    bool isBuy = true;

    if(riskManager.validateTrade(symbol, tradePrice, tradePrice, isBuy))
    {
        std::cout << "Trade Approved: " << (isBuy ? "Buy" : "Sell") << " " << tradeQuantity << " of " << symbol << " at " << tradePrice << "\n";
    }
    else
    {
        std::cout << "Trade rejected due to risk limit. \n";
    }

    riskManager.updatePortfolioValue(95000.0); // for loss check
    riskManager.printRiskStatus();


    return 0;
}