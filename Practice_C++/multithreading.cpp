// Multithreading - 

// In high-frequency trading, multiple tasks often need to be executed simultaneously

#include <iostream>
#include <thread>
#include <string>

using namespace std;

void processStockOrder(string& stockOrder)
{
    cout << "Stock Processing Order " << stockOrder << endl;
}

int main()
{
    string order1 = "Order1";
    string order2 = "Order2";

    std::thread t1(processStockOrder, cref(order1));
    std::thread t2(processStockOrder, order2);

    t1.join();
    t2.join();

    return 0;
}