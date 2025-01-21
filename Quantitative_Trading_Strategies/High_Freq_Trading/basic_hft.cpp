#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

double get_price_from_exhangeA()
{
    return 100.0 + (rand() % 100) / 100.0;
}

double get_price_from_exhangeB()
{
    return 100.0 + (rand() % 150) / 100.0;
}

void executeTrade(const string& signal, const string& exchange, const double& amount)
{
    cout << "Signal is " << signal << " on " << exchange << " with amount " << amount << endl;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    const double threshold = 0.20;
    bool running = true;

    while(running)
    {
        double priceA = get_price_from_exhangeA();
        double priceB = get_price_from_exhangeB();

        if(priceA + threshold < priceB)
        {
            executeTrade("BUY", "Exchange A", priceA);
            executeTrade("SELL", "Exchange B", priceB);
        }
        else if(priceB + threshold < priceA)
        {
            executeTrade("BUY", "Exchange B", priceB);
            executeTrade("SELL", "Exchange A", priceA);
        }
    }

    return 0;
}