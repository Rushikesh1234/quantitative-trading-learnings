
#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

void processStockOrder(string& stockOrder)
{
    cout << "Stock Processing Order " << stockOrder << endl;
}

mutex mtx;

void updateStockPrice(double price)
{
    mtx.lock();
    cout << "Stock price has been successfully updated " << price << endl;
    mtx.unlock();
}

int main()
{
    // Multithreading - In high-frequency trading, multiple tasks often need to be executed simultaneously

    cout << "Multithreading" << endl;
    string order1 = "Order1";
    string order2 = "Order2";

    thread t1(processStockOrder, order1);
    thread t2(processStockOrder, order2);

    t1.join();
    t2.join();

    cout << endl << endl;

    // Thread synchronization with mutex to avoid race conditions and to sunchonize thread activity.

    cout << "Thread synchronization with Mutex" << endl;
    thread t3(updateStockPrice, 129.22);
    thread t4(processStockOrder, 222.21);

    t3.join();
    t4.join();

    cout << endl << endl;

    return 0;
}