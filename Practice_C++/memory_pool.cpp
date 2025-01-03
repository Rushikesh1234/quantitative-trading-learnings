// Memory Pools - To avoid continuous allocation and deallocation of memory, it helps to pre-allocate blocks of memory to avoid overhead and fragmentation.
    
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Order
{
    int id;
    double price;
    string type;
    int quantity;
};

//Manually create memory pool
class MemoryPool
{
    private:
        size_t blockSize;
        size_t poolSize;
        vector<void*> freeList;
        vector<char> pool;
    
    public:
        MemoryPool(size_t blockSize, size_t blockCount)
        {
            this->blockSize = blockSize;
            poolSize = blockSize * blockCount;
            pool.resize(poolSize);

            for(size_t i=0; i<blockCount; i++)
            {
                freeList.push_back(&pool[i*blockSize]);
            }
        }

        void * allocate()
        {
            if(freeList.empty())
            {
                throw bad_alloc();
            }

            void *ptr = freeList.back();
            freeList.pop_back();
            return ptr;
        }

        void deallocate(void *ptr)
        {
            freeList.push_back(ptr);
        }
};

class TradingModel
{
    private:
        MemoryPool orderPool;
        double threshold;

    public:
        TradingModel(double threshold) : orderPool(sizeof(Order), 100)
        {
            this->threshold = threshold;
        }

        void placeHolder(double price, int quantity)
        {
            Order* order = static_cast<Order*>(orderPool.allocate());

            order->id = rand() % 1000;
            order->price = price;
            order->quantity = quantity;
            order->type = (price < threshold) ? "BUY" : "SELL";

            cout << "Order Id " << order->id << " Type " << order->type << " Quantity " << order->quantity << " Price " << order->price << endl;

            orderPool.deallocate(order);
        }

        void runModel(vector<double>& prices, int quantity)
        {
            for(double price: prices)
            {
                placeHolder(price, quantity);
            }
        }

};

int main()
{

    srand(static_cast<unsigned int>(time(0)));

    TradingModel model(100.0);

    vector<double> prices = {122.3, 121.4, 82.34, 112.53, 94.21};

    model.runModel(prices, 10);
    
    return 0;
}