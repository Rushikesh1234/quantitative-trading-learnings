
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

struct Order
{
    int id;
    bool isBuy;
    double price;
    int volume;
};

struct Data
{
    string time;
    double bid;
    double ask;   
};

class Backtesting
{
    private:
        int orderId = 0;
        map<double, int, greater<>> bids;
        map<double, int> asks;
        double cashBalance = 1000000.00;
        int position = 0;

    public: 
        void load_and_process_data(const string& filepath)
        {
            ifstream file(filepath);
            if(!file.is_open())
            {
                cout << "File is not accessible\n" << filepath << endl;
                return;
            }

            string line;

            getline(file, line);

            while(getline(file, line))
            {
                cout << "\n\n";
                Data data = parse_data(line);
                processData(data);
            }

            file.close();
        }

        Data parse_data(string& line)
        {
            Data data;
            stringstream ss(line);
            string time;
            string bid;
            string ask;

            if(getline(ss, time, ',') && getline(ss, bid, ',') && std::getline(ss, ask) && !time.empty() && !bid.empty() && !ask.empty())
            {
                data.time = time;
                data.bid = stod(bid);
                data.ask = stod(ask);
            }
            else
            {
                cout << "Malformed line\n" << endl;
            }

            return data;
        }

        void processData(const Data& data)
        {
            cout << "Processing Data: Time= " << data.time << " Bid= " << data.bid << " Ask= " << data.ask << "\n";
            double spread  = data.ask - data.bid;
            if(spread > 0.02)
            {
                placeOrder(true, data.bid, 100);
                placeOrder(false, data.ask, 100);
            }

            marketOrders();
        }

        void placeOrder(bool isBuy, double price, int volume)
        {
            Order order = {++orderId, isBuy, price, volume};
            if(isBuy)
            {
                bids[price] += volume;
            }
            else
            {
                asks[price] += volume;
            }

            cout << "Order Placed: " << (isBuy ? "Buy" : "Sell") << " order: " << "Price=" << price << ", Volume=" << volume << "\n";
        }

        void marketOrders()
        {
            while(!bids.empty() && !asks.empty())
            {
                auto bestBid = bids.begin();
                auto bestAsk = asks.begin();

                if(bestBid->first >= bestAsk->first)
                {
                    int matchVolume = min(bestBid->second, bestAsk->second);

                    double tradePrice = (bestBid->first + bestAsk->first) / 2;

                    cashBalance -= matchVolume * tradePrice;

                    position += (bestBid->second > bestAsk->second ? matchVolume : -matchVolume);

                    bestBid->second -= matchVolume;
                    bestAsk->second -= matchVolume;

                    if(bestAsk->second == 0)
                    {
                        asks.erase(bestAsk);
                    }
                    if(bestBid->second == 0)
                    {
                        bids.erase(bestBid);
                    }

                    cout << "Executed Trade: Time=" << bestBid->first << ", Price=" << tradePrice << ", Volume=" << matchVolume << ", CashBalance=" << cashBalance << ", Position=" << position << "\n";
                }
                else
                {
                    break;
                }
            }
        }
};

int main()
{
    Backtesting backtester;

    backtester.load_and_process_data("market_data.csv");

    return 0;
}