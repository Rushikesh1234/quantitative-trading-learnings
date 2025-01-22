#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <iostream>
#include <map>

struct Order
{
    int id;
    bool isBuy;
    double price;
    int quantity;
};

class OrderBook
{
    private:
        std::map<double, int, std::greater<>> bids;
        std::map<double, int> asks;
        int orderId = 0;

    public:
        void placeOrder(bool isBuy, double price, int quantity);
        void matchOrder();
        void printOrderBook();
};

#endif