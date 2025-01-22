#include "ExecutionEngine.hpp"

void ExecutionEngine::executeTrade(const Trade& trade)
{
    tradeCounter++;

    double tradeValue = trade.price * trade.quantity;

    if(trade.isBuy)
    {
        balances["USD"] -= tradeValue;
        positions[trade.symbol] += trade.quantity;
    }
    else
    {
        balances["USD"] += tradeValue;
        positions[trade.symbol] -= trade.quantity;
    }

    std::cout << "\nTrade Executed: ID " << tradeCounter << " | " << (trade.isBuy ? "BUY" : "SELL") << " " << trade.quantity << " of " << trade.symbol << " at " << trade.price << "\n";
}

void ExecutionEngine::printAccountStatus()
{
    std::cout << "\nAccount Balances:\n";
    for(const auto& balance : balances)
    {
        std::cout << balance.first << ": " << balance.second << "\n";
    }
    
    std::cout << "\nPositions:\n";
    for(const auto& position : positions)
    {
        std::cout << position.first << ": " << position.second << "\n";
    }
}