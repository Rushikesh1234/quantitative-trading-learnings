#ifndef RISKMANAGER_HPP
#define RISKMANAGER_HPP

#include <string>
#include <unordered_map>
#include <iostream>

class RiskManager
{
    private:
        double maxDrawdown;
        double maxExposure;
        double portfolioValue;
        std::unordered_map<std::string, double> positionLimits;
    
    public:
        RiskManager(double maxDrawdownPercent, double maxExposurePercent, double initialPortfolioValue);

        void setPositionLimit(const std::string& symbol, double limit);

        bool validateTrade(const std::string& symbol, double tradeValue, int tradeQuantity, bool isBuy);

        void updatePortfolioValue(double newValue);

        void printRiskStatus();        
};

#endif