#include "MarketDataFeed.hpp"

MarketDataFeed::MarketDataFeed(const std::vector<double>& prices) : marketPrices(prices){}

bool MarketDataFeed::fetchNextPrice(const std::function<void(double)>& newPrice)
{
    if(currentIndex < marketPrices.size())
    {
        double price = marketPrices[currentIndex++];
        newPrice(price);
        return true;
    }
    else
    {
        std::cerr << "Market data ended\n";
        return false;
    }
}

double MarketDataFeed::getLastPrice(const std::string& symbol)
{
    if(currentIndex == 0)
    {
        return marketPrices.empty() ? 0.0 : marketPrices.back();
    }

    return marketPrices[currentIndex - 1];
}