#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

using namespace std;

vector<string> execute_trades(vector<double>& prices, double threshold)
{
    vector<string> trades;
    for(size_t i = 1; i < prices.size(); i++)
    {
        if(prices[i] > prices[i-1] * (1 + threshold))
        {
            trades.push_back("Buy");
        }
        else if(prices[i] < prices[i-1] * (1 + threshold))
        {
            trades.push_back("Sell");
        }
        else
        {
            trades.push_back("Hold");
        }
    }
    return trades;
}

vector<double> compute_moving_average(vector<double>& prices, size_t length)
{
    vector<double> moving_average;

    if(length > prices.size())
    {
        return moving_average;
    }

    double sum = 0;
    for(size_t i = 0; i < prices.size(); i++)
    {
        sum += prices[i];
        if(i >= length-1)
        {
            moving_average.push_back(sum / length);
            sum -= prices[i - length + 1];
        }
    }

    return moving_average;
}

PYBIND11_MODULE(trading, m)
{
    m.def("compute_moving_average", &compute_moving_average, "A function to computer moving average");
    m.def("execute_trades", &execute_trades, "A function to execute trades based on threshold");
}