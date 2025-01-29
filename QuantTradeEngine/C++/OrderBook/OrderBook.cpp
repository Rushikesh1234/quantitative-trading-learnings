#include "OrderBook.hpp"
#include <iostream>

void OrderBook::placeOrder(bool isBuy, double price, int quantity)
{
    orderId++;
    
    if(isBuy)
    {
        bids[price] += quantity;
    }
    else
    {
        asks[price] += quantity;
    }

    std::cout << "\nPlaced Order: " << (isBuy ? "Buy" : "Sell") << " " << quantity << " at " << price << "\n";
}

void OrderBook::matchOrder()
{
    while(!bids.empty() && !asks.empty())
    {
        auto bestBid = bids.rbegin();
        auto bestAsk = asks.begin();

        if(bestBid->first >= bestAsk->first)
        {
            int matchQty = std::min(bestBid->second, bestAsk->second);
            double tradePrice = bestAsk->first;

            std::cout << "\nMatched Order: " << matchQty << " units at " << tradePrice << "\n";

            bestBid->second -= matchQty;
            bestAsk->second -= matchQty;

            if(bestBid->second == 0) bids.erase(--bids.end());
            if(bestAsk->second == 0) asks.erase(asks.begin());
        }
        else
        {
            break;
        }
    }
}

void OrderBook::printOrderBook()
{
    std::cout << "\nOrderBook:\n";
    
    std::cout << "\nBids: \n";
    for(auto& bid : bids)
    {
        std::cout << bid.second << " at " << bid.first << "\n";
    }

    std::cout << "\nAsks: \n";
    for(auto& ask : asks)
    {
        std::cout << ask.second << " at " << ask.first << "\n";
    }
}