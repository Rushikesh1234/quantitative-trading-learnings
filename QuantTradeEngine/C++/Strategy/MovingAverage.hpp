#ifndef MOVINGAVERAGE_HPP
#define MOVINGAVERAGE_HPP

#include <vector>
#include <iostream>
#include <string>
#include <numeric>

class MovingAverage
{
    private:
        double calculateSMA(int period);
        std::vector<double> priceHistory;
    public:
        MovingAverage(int shortW, int longW);
        int shortWindow;
        int longWindow;
        bool shouldBuy(double price);
        bool shouldSell(double price);
        void updatePrice(double price);
};

#endif