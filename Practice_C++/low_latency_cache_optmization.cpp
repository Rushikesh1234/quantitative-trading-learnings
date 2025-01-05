// Efficient cache usage is key in low-latency systems because accessing data in 
//cache is orders of magnitude faster than accessing it from main memory.

#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <numeric>
// #include <immintrin.h> // This will work for intel based system - x86 architecture intel specific - mmprefetch
#include <arm_neon.h>

using namespace std;

struct MarketData
{
    // Aligned to 64 bytes (alignas(64)), This prevents false sharing and ensures efficient memory access.
    alignas(64) double prices[8];
};


void processMarketData(const vector<MarketData>& marketData)
{
    double sum = 0.0;

    for(const auto& data : marketData)
    {
        // Prefetch next cache line for better performance
        // _mm_prefetch(reinterpret_cast<const char*>(&data) + 64, _MM_HINT_T0); // used for intel specific architecture
        // 
        __builtin_prefetch(reinterpret_cast<const char*>(&data) + 64, 0, 3); // For arm based architecture apple mac chip
        
        // Process each price in the current structure
        for(double price : data.prices)
        {
            // Random calculation
            sum += sqrt(price);
        }
    }

    cout << "Processed sum: " << sum << endl;
}

int main()
{
    constexpr size_t dataCount = 1000000;
    vector<MarketData> marketData(dataCount);

    // Populate market data with random prices
    for(auto& data : marketData)
    {
        generate(begin(data.prices), end(data.prices), [](){
            // Random prices between 0 and 100
            return static_cast<double>(rand()) / RAND_MAX * 100.0; 
        });
    }

    auto start = chrono::high_resolution_clock::now();
    processMarketData(marketData);
    auto end = chrono::high_resolution_clock::now();

    cout << "Processing time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}