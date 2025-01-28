#ifndef MARKETDATAFEED_HPP
#define MARKETDATAFEED_HPP

#include <iostream>
#include <string>
#include <vector>

class MarketDataFeed
{
    private:
        std::vector<double> marketPrices;
        size_t currentIndex = 0;
    public:
        MarketDataFeed(const std::vector<double>& prices);

        void fetchNextPrice(const std::function<void(double)>& newPrice);
};

#endif