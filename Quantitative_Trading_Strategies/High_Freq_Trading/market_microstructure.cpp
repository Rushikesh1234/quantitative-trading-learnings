

#include <iostream>
#include <map>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class OrderBook
{
    public:
        map<double, int> bids;
        map<double, int> asks;

        void addOrder(bool isBid, double price, int volume)
        {
            auto& book = isBid ? bids : asks;
            book[price] += volume;
        }

        void processMarketorder(bool isBuy, int volume)
        {
            auto& book = isBuy ? asks : bids;

            while(volume > 0 && !book.empty())
            {
                auto it = isBuy ? book.begin() : --book.end();
                double price = it->first;
                int availableVolume = it->second;

                if(volume >= availableVolume)
                {
                    volume -= availableVolume;
                    book.erase(price);
                }
                else
                {
                    book[price] -= volume;
                    volume = 0;
                }

                cout << "Executed " << (isBuy ? "buy" : "sell") << " at price: " << price << "\n";
            }

            if(volume > 0)
            {
                cout << "Market order partially filled, remaining volume: " << volume << "\n";
            }

        }

        double calculateSpread()
        {
            if(bids.empty() || asks.empty())
            {
                cout << "Order book incomplete \n";
                return -1;
            }
            double bestBid = bids.rbegin()->first;
            double bestAsk = asks.rbegin()->first;

            int bidVolume = bids.rbegin()->second;
            int askVolume = asks.rbegin()->second;

            return bidVolume + askVolume;
        }

        void displayOrder()
        {
            cout << "Order Book \nAsks (Sell Orders):\n";
            for (auto& [price, volume] : asks) 
                cout << "Price: " << price << ", Volume: " << volume << "\n";
            cout << "Bids (Buy Orders):\n";
            for (auto it = bids.rbegin(); it != bids.rend(); ++it) 
                cout << "Price: " << it->first << ", Volume: " << it->second << "\n";
        
        } 

        double calculateLiquiditySpread()
        {
            if(bids.empty() || asks.empty())
            {
                cout << "Order book is incomplete to calculate liquidity\n";
                return 0;
            }

            double bestbid = bids.rbegin()->first;
            double bestask = asks.begin()->first;

            int bidVolume = bids.rbegin()->second;
            int askVolume = asks.begin()->second;

            return bidVolume + askVolume;

        }
};

int main()
{
    /*
        Order Types and Order Book  ->
        Market Orders: Executed immediately at the current best available price.
        Limit Orders: Added to the order book if not immediately matched.
        Order Book: Displays all outstanding buy/sell limit orders, crucial for understanding supply and demand.
    */
 
    OrderBook ob;

    cout << "Limit Orders: " << endl;
    ob.addOrder(false, 10.05, 50);
    ob.addOrder(false, 10.10, 30);
    ob.addOrder(true, 10.00, 100);
    ob.addOrder(true, 9.95, 40);

    cout << "Initial orderbook \n";
    ob.displayOrder();
    cout << endl << endl;

    cout << "\nProcessing Market Buy Order for 60 \n";
    ob.processMarketorder(true, 60);

    cout << "\nOrder book after Market Buy Order\n";
    ob.displayOrder();

    cout << "\nProcessing Market sell order for 120 \n";
    ob.processMarketorder(false, 120);

    cout << "\nOrder book after Market Sell Order\n";
    ob.displayOrder();

    /*
        Liquidity and Spreads ->
        Liquidity: Liquidity refers to how easily an asset can be bought or sold in the market without significantly affecting its price.
        Bid-Ask Spread: The spread is the difference between the best (highest) bid price and the best (lowest) ask price in the order book. Spread = Ask Price − Bid Price

    */

    OrderBook ob1;

    cout << "Liquidity and Spreads: " << endl;
    ob1.addOrder(true, 10.00, 100);  
    ob1.addOrder(true, 9.95, 50);  
    ob1.addOrder(false, 10.05, 80);
    ob1.addOrder(false, 10.10, 40);

    cout << "Initial Orderbook \n";
    ob1.displayOrder();
    cout << endl << endl;

    cout << "Regular Spread Value";
    double spread = ob1.calculateSpread();
    if(spread >= 0)
    {
        cout << "\nSpread is " << spread << "\n";
    }

    cout << "\nCalculating liquidity spread value";
    int liquiditySpread = ob1.calculateLiquiditySpread();
    cout << "\nLiquidity Spread " << liquiditySpread << "\n";


    /*
        Latency and Execution:
        Low Latency: Essential in HFT, as milliseconds or microseconds can determine profitability.
        Colocation: Placing servers near exchange data centers to minimize latency.
        Network Latency: Time taken for data to travel between the trading system and the exchange server. Minimized by: colocating servers near exchange data centers.
        Processing Latency: Time taken to process an order by the trading system or the exchange. Minimized by: using optimized algorithms and high-performance hardware.
        Order Execution Latency: Time between order placement and execution on the exchange. Minimized by: prioritizing order types and efficient market access.
        Factors Affecting Latency: Order Book Depth,  Market Conditions,  Exchange Infrastructure
    */

    OrderBook ob3;
    cout << "\nLatency and Executions: " << endl;
    ob3.addOrder(true, 10.00, 100); 
    ob3.addOrder(false, 10.05, 80);

    cout << "Initial Order Book:\n";
    ob3.displayOrder();

    auto start = high_resolution_clock::now();
    ob3.processMarketorder(true, 50);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "\nMarket Order Latency: " << duration.count() << " ms\n";

    cout << "\nOrder Book After Execution:\n";
    ob3.displayOrder();

    return 0;
}