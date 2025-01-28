#include "MovingAverage.hpp"

MovingAverage::MovingAverage(int shortW, int longW):shortWindow(shortW), longWindow(longW) {}

std::string MovingAverage::genrateSignal(const std::vector<double>& prices)
{
    if(prices.size() < longWindow)
    {
        return "Hold";
    }

    double shortAvg = 0.0;
    double longAvg = 0.0;

    for(size_t i = prices.size() - shortWindow; i < prices.size(); i++)
    {
        shortAvg += prices[i];
    }

    for(size_t i = prices.size() - longWindow; i < prices.size(); i++)
    {
        longAvg += prices[i];
    }

    shortAvg /= shortWindow;
    longAvg /= longWindow;

    return (shortAvg > longAvg) ? "Buy" : "Sell";
}