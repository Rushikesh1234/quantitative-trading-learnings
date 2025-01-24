#include "RiskManager.hpp"

RiskManager::RiskManager(double maxDrawdownPercent, double maxExposurePercent, double initialPortfolioValue)
  : maxDrawdown(maxDrawdownPercent/100.0), 
    maxExposure(maxExposurePercent/100.0), 
    portfolioValue(initialPortfolioValue) {}

void RiskManager::setPositionLimit(const std::string& symbol, double limit)
{
    positionLimits[symbol] = limit;
}

bool RiskManager::validateTrade(const std::string& symbol, double tradeValue, int tradeQuantity, bool isBuy)
{
    double exposure = tradeValue / portfolioValue;

    if(exposure > maxExposure)
    {
        std::cerr << "Risk Violation: Trade exceeds maximum exposure (" << maxExposure*100 << "%)\n"; 
        return false;
    }
    
    if(positionLimits.find(symbol) != positionLimits.end() && tradeQuantity > positionLimits[symbol])
    {
        std::cerr << "Risk Violation: Trade exceeds positon limit for " << symbol << "\n";
        return false;
    }

    return true;
}

void RiskManager::updatePortfolioValue(double newValue)
{
    double drawdown = (portfolioValue - newValue) / portfolioValue;

    portfolioValue = newValue;

    if(drawdown > maxDrawdown)
    {
        std::cerr << "Risk Alert: Drawdown exceeded (" << maxDrawdown * 100 << "%)\n";
    }
}

void RiskManager::printRiskStatus()
{
    std::cout << "\nRisk management:\n";
    std::cout << "Portfolio Value: $"<< portfolioValue << "\n";
    std::cout << "Max Drawdown: " << maxDrawdown << "\n";
    std::cout << "Max Exposure: " << maxExposure << "\n";
    for(const auto& limit : positionLimits)
    {
        std::cout << "Posotion Limits - " << limit.first << ": " << limit.second <<" units\n";
    }
}




