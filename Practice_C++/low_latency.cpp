// Understanding importance of low latency in quantitative trading

// In trading, every microsecond counts. Optimizing for low latency involves minimizing unnecessary computations and avoiding delays.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Inline function - suggest to a compiler that this function should be expanded at the call site rather performing a traditional function call, to reduce overhead.
inline double calculatePriceChange1(double oldPrice, double newPrice)
{
    return newPrice - oldPrice;
}

double calculatePriceChange2(double oldPrice, double newPrice)
{
    return newPrice - oldPrice;
}

double calculateAverage(vector<double>& stocks)
{
    double average = 0.0;

    for(double stock : stocks)
    {
        average += stock;
    }

    average /= stocks.size();

    return average;
}

int main()
{
    cout << "Inline Functions" << endl;
    cout << "Calculate Price Change with Inline function: " << calculatePriceChange1(125.02, 164.32) << endl;
    cout << "Calculate Price Change with traditional function call: " << calculatePriceChange2(125.02, 164.32) << endl << endl;

    cout << "Avoiding unnecessary copies" << endl;
    vector<double> stocks = {131.21, 123.22, 131.22, 211.21, 121.11};
    cout << "Total Average " << calculateAverage(stocks) << endl << endl;

    return 0;
}