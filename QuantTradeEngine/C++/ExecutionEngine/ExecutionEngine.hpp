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
        int tradeCounter = 0;
        std::unordered_map<std::string, double> balances;
        std::unordered_map<std::string, int> positions;

    public:
        void executeTrade(const Trade& trade);
        void printAccountStatus();
};

#endif