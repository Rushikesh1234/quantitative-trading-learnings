#ifndef MOVINGAVERAGE_HPP
#define MOVINGAVERAGE_HPP

#include <vector>
#include <iostream>
#include <string>

class MovingAverage
{
    private:
        int shortWindow;
        int longWindow;
    public:
        MovingAverage(int shortW, int longW);

        std::string genrateSignal(const std::vector<double>& prices);
};

#endif