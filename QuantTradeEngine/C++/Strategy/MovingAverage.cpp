#include "MovingAverage.hpp"

MovingAverage::MovingAverage(int shortW, int longW):shortWindow(shortW), longWindow(longW) {}

double MovingAverage::calculateSMA(int period)
{
    if(priceHistory.size() < period) return 0.0;

    double sum = std::accumulate(priceHistory.end() - period, priceHistory.end(), 0.0);

    return sum / period;
}

bool MovingAverage::shouldBuy(double price)
{
    double shortSMA = calculateSMA(shortWindow);
    double longSMA = calculateSMA(longWindow);
 
    return (shortSMA > longSMA);
}

bool MovingAverage::shouldSell(double price)
{
    double shortSMA = calculateSMA(shortWindow);
    double longSMA = calculateSMA(longWindow);

    return (shortSMA < longSMA);
}

void MovingAverage::updatePrice(double price)
{
    priceHistory.push_back(price);

    if(priceHistory.size() > longWindow)
    {
        priceHistory.erase(priceHistory.begin());
    }
}
