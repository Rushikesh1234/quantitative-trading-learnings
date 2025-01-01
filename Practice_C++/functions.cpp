#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <functional>

namespace QuantTrading
{
    // Template Function
    template<typename T>
    T calculateMovingAverage(const std::vector<T>& prices, int period)
    {
        if(prices.size() < period || period <= 0)
        {
            throw std::invalid_argument("Invalid period or prices vector");
        }
        T sum = std::accumulate(prices.end() - period, prices.end(), static_cast<T>(0));
        return sum / period;
    }

    // Inline Function
    inline double calculatePercentageChange(double oldPrice, double newPrice)
    {
        return  ((newPrice - oldPrice) / oldPrice) * 100.0;
    }

    // Lamba Function
    auto generateSignal = [](double currentPrice, double movingAverage) -> std::string {
        return (currentPrice > movingAverage) ? "Buy" : "Sell";
    };

    // Function Overloading
    void print(const std::vector<double>& data)
    {
        for(const auto& val : data)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    void print(double val)
    {
        std::cout << val << "\n";
    }

    // Recursive Function
    int factorial(int n)
    {
        if(n <= 1)
        {
            return 1;
        }

        return n * factorial(n-1);
    }

    // Function with default arguments
    double calculateRisk(double portfolioValue, double stopLoss = 0.02)
    {
        return portfolioValue * stopLoss;
    }

    // Unit Test fucntion
    void unitTests()
    {
        std::vector<double> testPrices;
        testPrices.push_back(100);
        testPrices.push_back(102);
        testPrices.push_back(101);
        testPrices.push_back(104);
        testPrices.push_back(107);

        try
        {
            double movingAverage = calculateMovingAverage(testPrices, 3);
            if(movingAverage != (104+101+107) / 3.0)
            {
                throw std::logic_error("Test failed for moving average");
            }
            std::cout << "Unit tests passed.\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << "Unit test failed.\n";
        }
    }
}

int main()
{
    using namespace QuantTrading;

    std::vector<double> prices;
    prices.push_back(100.0);
    prices.push_back(102.0);
    prices.push_back(101.0);
    prices.push_back(104.0);
    prices.push_back(107.0);
    prices.push_back(110.0);


    std::cout << "Stock Prices: ";
    print(prices);

    try
    {
        double movingAverage = calculateMovingAverage(prices, 3);
        std::cout << "Moving Average for 3 days: ";
        print(movingAverage);

        double currentPrice = prices.back();
        std::string signal = generateSignal(currentPrice, movingAverage);
        std::cout << "Trading Signal: " << signal << "\n";

        double portfolioRisk = calculateRisk(10000);
        std::cout << "Portfolio Risk: $" << portfolioRisk << "\n";

        double change = calculatePercentageChange(prices.front(), prices.back());
        std::cout << "Percentage Change: " << change << "%\n";

        std::cout << "Factorial of 5 is " << factorial(5) << "\n";

        unitTests();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}