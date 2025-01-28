#include "MarketDataFeed.hpp"

MarketDataFeed::MarketDataFeed(const std::vector<double>& prices) : marketPrices(prices){}

void MarketDataFeed::fetchNextPrice(const std::function<void(double)>& newPrice)
{
    if(currentIndex < marketPrices.size())
    {
        double price = marketPrices[currentIndex++];
        newPrice(price);
    }
    else
    {
        std::cerr << "Market data ended\n";
    }
}