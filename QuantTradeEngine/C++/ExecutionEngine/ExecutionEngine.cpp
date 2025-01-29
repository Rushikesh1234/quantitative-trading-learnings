#include "ExecutionEngine.hpp"

ExecutionEngine::ExecutionEngine(double initialBalance)
{
    balances["USD"] = initialBalance;
    tradeCounter = 0;
}

double ExecutionEngine::executeTrade(const Trade& trade)
{
    tradeCounter++;

    double tradeValue = trade.price * trade.quantity;

    if(trade.isBuy)
    {
        if(balances["USD"] >= tradeValue)
        {
            balances["USD"] -= tradeValue;
            positions[trade.symbol] += trade.quantity;
        }
        else
        {
             std::cerr << "Trade Error: Insufficient funds to buy!\n";
             return 0.0;
        }
    }
    else
    {
        if (positions[trade.symbol] >= trade.quantity)
        {
            positions[trade.symbol] -= trade.quantity;
            balances["USD"] += tradeValue;
        }
        else
        {
            std::cerr << "Trade Error: Insufficient quantity to sell!\n";
            return 0.0;
        }
    }
    std::cout << "\nTrade Executed: ID " << tradeCounter << " | " << (trade.isBuy ? "BUY" : "SELL") << " " << trade.quantity << " of " << trade.symbol << " at " << trade.price << "\n";
    return tradeValue;
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

std::unordered_map<std::string, int> ExecutionEngine::getPositions() const
{
    return positions;
}

double ExecutionEngine::getBalance(const std::string& symbol) const
{
    auto it = balances.find(symbol);
    if(it != balances.end())
    {
        return it->second;
    }
    return 0.0;
}