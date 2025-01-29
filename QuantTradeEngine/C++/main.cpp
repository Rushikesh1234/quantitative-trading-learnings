#include "OrderBook/OrderBook.hpp"
#include "ExecutionEngine/ExecutionEngine.hpp"
#include "LatencySimulator/LatencySimulator.hpp"
#include "RiskManagement/RiskManager.hpp"
#include "Strategy/MovingAverage.hpp"
#include "MarketDataFeed/MarketDataFeed.hpp"

class TradingSimulator
{
    private:
        OrderBook orderBook;
        ExecutionEngine executionEngine;
        LatencySimulator latencySimulator;
        RiskManager riskManager;
        MarketDataFeed marketDataFeed;
        MovingAverage movingAverageStrategy;
        double portfolioValue;
    public:
        TradingSimulator(const std::vector<double>& prices, double initialBalance)
            : marketDataFeed(prices), 
            riskManager(10.0, 20.0, initialBalance), 
            movingAverageStrategy(5,20),
            executionEngine(initialBalance){
                portfolioValue = initialBalance;
            }

        void updatePortfolioValues()
        {
            double totalStockValue = 0.0;
            for(const auto& position : executionEngine.getPositions())
            {
                double lastPrice = marketDataFeed.getLastPrice(position.first);
                totalStockValue += position.second * lastPrice;
            }

            portfolioValue = executionEngine.getBalance("USD") + totalStockValue;
            riskManager.updatePortfolioValue(portfolioValue);
        }

        void simulate()
        {
            std::cout << "Starting Trading Simulation: \n";
            
            while(true)
            {
                bool hasMoreData = marketDataFeed.fetchNextPrice([&] (double price)
                {
                    latencySimulator.simulateLatency(50);

                    movingAverageStrategy.updatePrice(price);

                    bool isBuy = movingAverageStrategy.shouldBuy(price);
                    bool isSell = movingAverageStrategy.shouldSell(price);
                    int tradeQuantity = 10;
                    std::string symbol = "AAPL";

                    if(isBuy)
                    {
                        bool isTradeApprove = riskManager.validateTrade(symbol, price * tradeQuantity, tradeQuantity, isBuy);
                        
                        if(isTradeApprove)
                        {
                            double tradeValue = executionEngine.executeTrade({0, "AAPL", price, tradeQuantity, true});
                           
                            if(tradeValue > 0.0)
                            {
                                orderBook.placeOrder(true, price, tradeQuantity);
                                updatePortfolioValues();
                            }
                        }
                        else
                        {
                            std::cout << "Trade Execution Failed. Buy trade rejected due to risk limits.\n";
                        }
                    }
                    else if(isSell)
                    {
                        bool isTradeApprove = riskManager.validateTrade(symbol, price * tradeQuantity, tradeQuantity, false);
                        
                        if(isTradeApprove)
                        {
                            double tradeValue = executionEngine.executeTrade({0,"AAPL", price, tradeQuantity, false});
                            
                            if(tradeValue > 0.0)
                            {
                                orderBook.placeOrder(false, price, tradeQuantity);
                                updatePortfolioValues();
                            }
                        }
                        else
                        {
                            std::cout << "Trade Execution Failed. Sell trade rejected due to risk limits.\n";
                        }
                    }
                });
            
                if(!hasMoreData)
                {
                    break;
                }
            }

            orderBook.printOrderBook();
            executionEngine.printAccountStatus();
            riskManager.printRiskStatus();
        }
};

int main()
{
    double initialBalance = 100000.0;
    std::vector<double> marketPrices = {100.5, 101.5, 90.5, 85.4, 110.1, 103.9, 104.2, 98.1, 107.6};
    TradingSimulator simulator(marketPrices, initialBalance);
    simulator.simulate();
    return 0;
}