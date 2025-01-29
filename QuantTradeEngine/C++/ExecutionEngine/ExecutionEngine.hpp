#ifndef EXECUTIONENGINE_HPP
#define EXECUTIONENGINE_HPP

#include <iostream>
#include <string>
#include <unordered_map>

struct Trade
{
    int tradeId;
    std::string symbol;
    double price;
    int quantity;
    bool isBuy;
};

class ExecutionEngine
{
    private:
        int tradeCounter;
        std::unordered_map<std::string, double> balances;
        std::unordered_map<std::string, int> positions;

    public:
        ExecutionEngine(double initialBalance);
        double executeTrade(const Trade& trade);
        void printAccountStatus();
        std::unordered_map<std::string, int> getPositions() const;
        double getBalance(const std::string& symbol) const;
};

#endif