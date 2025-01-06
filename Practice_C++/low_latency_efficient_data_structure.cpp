// In high-frequency trading, choosing the right data structure can significantly 
//impact performance.

#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <numeric>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

// Circular Buffers for Streaming Data - 
// useful for scenarios where you need to handle continuous data streams without 
// re-allocating memory frequently. It wraps around once it reaches the end.

class PriceCircularBuffer
{
    private:
        vector<double> stockPriceBuffer;
        size_t head;
        size_t tail;
        size_t maxSize;
        bool full;
    
    public:
        PriceCircularBuffer(int size)
        {
            maxSize = size;
            stockPriceBuffer.resize(size);
            head = 0;
            tail = 0;
            full = false;
        }

        void addPrice(double price)
        {
            stockPriceBuffer[head] = price;
            if(full)
            {
                tail = (tail + 1) % maxSize;
            }
            head = (head + 1) % maxSize;
            full = (head == tail); 
        }

        double calculateAverageForEveryDay()
        {
            size_t count = currentBufferSize();

            if(count == 0)
            {
                return 0.0;
            }

            double sum = accumulate(stockPriceBuffer.begin(), stockPriceBuffer.begin()+count, 0.0);
            return sum / count;
        }

        size_t currentBufferSize()
        {
            if(full)
            {
                return maxSize;
            }
            else if(head >= tail)
            {
                return head - tail;
            }
            return maxSize + head - tail;
        }

        bool isEmpty()
        {
            return (!full && (head == tail));
        }

        void getstockPriceBuffer()
        {
            if(isEmpty())
            {
                cout << "Current stockPriceBuffer is empty." << endl;
            }
            else
            {
                cout << "Current stockPriceBuffer " << endl;
                for(int i=0; i<stockPriceBuffer.size(); i++)
                {
                    cout << stockPriceBuffer[i] << " ";
                }
                cout << endl;
            }
        }
};

// Lock-Free Queues for Low-Latency Message Passing - For concurrency
// allows multiple threads to enqueue and dequeue items without locking, which reduces overhead.
// Single-Producer, Single-Consumer (SPSC) Queue

struct MarketData
{
    double price;
    int volume;
    chrono::time_point<chrono::high_resolution_clock> timestamp;

    MarketData(){}

    MarketData(int p, int v, chrono::time_point<chrono::high_resolution_clock> t)
    : price(p), volume(v), timestamp(t) {}
};

template <typename T>
class LockFreeQueue
{
    private:
        vector<T> buffer;
        atomic<size_t> head;
        atomic<size_t> tail;
        size_t capacity;
    public:
        LockFreeQueue(size_t capacity)
        {
            buffer.resize(capacity);
            head = 0;
            tail = 0;
            this->capacity = capacity;
        }
        bool enqueue(const T& item)
        {
            size_t current_tail = tail.load(memory_order_relaxed); 
            size_t next_tail = (current_tail + 1) % capacity;

            if(next_tail == head.load(memory_order_acquire))
            {
                return false;
            }

            buffer[current_tail] = item;
            tail.store(next_tail, memory_order_release);
            return true;
        }

        bool dequeue(T& item)
        {
            size_t current_head = head.load(memory_order_relaxed);

            if(current_head == tail.load(memory_order_acquire))
            {
                return false;
            }

            item = buffer[current_head];
            head.store((current_head + 1) % capacity, memory_order_release);
            return true;
        }
};

void producer(LockFreeQueue<MarketData>& queue, int& iteration)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> price_dist(10.0, 20.0);
    uniform_int_distribution<> volume_dist(1, 10);

    while(iteration < 20)
    {
        MarketData data(
            price_dist(gen), 
            volume_dist(gen), 
            std::chrono::high_resolution_clock::now()
        );

        if(queue.enqueue(data))
        {
            cout << "Production: Price=" << data.price << " Volume=" << data.volume << endl;
        }
        else
        {
            cout << "Queue is full, dropping some data" << endl;
        }

        iteration++;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void consumer(LockFreeQueue<MarketData>& queue, int& iteration)
{
    while(iteration < 20)
    {
        MarketData data;
        if(queue.dequeue(data))
        {
            chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
            size_t latency = chrono::duration_cast<chrono::microseconds>(now - data.timestamp).count();

            cout << "Consumed: Price: " << data.price << " Volume: " << data.price << " Latency: " << latency << endl;
        }
        else
        {
            cerr << "Queue is empty, waiting for data" << endl;
        }

        iteration++;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

int main()
{
    cout << endl << endl;
    
    // Circular Buffers for Streaming Data
    cout << "Circular Buffers for Streaming Data" << endl;
    int size = 5;
    PriceCircularBuffer pcb(size);
    pcb.addPrice(122.43);
    pcb.addPrice(132.47);
    pcb.getstockPriceBuffer();
    cout << "After stock PriceBuffer size " << pcb.currentBufferSize() << " Calculate Average stock price " << pcb.calculateAverageForEveryDay() << endl;
    pcb.addPrice(153.85);
    pcb.getstockPriceBuffer();
    cout << "After stock PriceBuffer size " << pcb.currentBufferSize() << " Calculate Average stock price " << pcb.calculateAverageForEveryDay() << endl;
    pcb.addPrice(181.33);
    pcb.addPrice(167.76);
    pcb.getstockPriceBuffer();
    cout << "After stock PriceBuffer size " << pcb.currentBufferSize() << " Calculate Average stock price " << pcb.calculateAverageForEveryDay() << endl;
    cout << endl << endl;

    cout << endl << endl;
    
    
    // Lock-Free Queues for Low-Latency Message Passing
    cout << "Lock-Free Queues for Low-Latency Message Passing" << endl;
    LockFreeQueue<MarketData> market_data_queue(10);
    
    int iteration = 0;
    std::thread producer_thread([&]() { producer(market_data_queue, iteration); });
    std::thread consumer_thread([&]() { consumer(market_data_queue, iteration); });


    producer_thread.join();
    consumer_thread.join();

    cout << endl << endl;
    return 0;
}