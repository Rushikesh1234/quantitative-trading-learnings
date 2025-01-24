#ifndef LATENCYSIMULATOR_HPP
#define LATENCYSIMULATOR_HPP

#include <thread>
#include <iostream>
#include <chrono>

class LatencySimputor
{
    public:
        void simulateLatency(int milliSeconds)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
            std::cout << "Latency Simulated: " << milliSeconds << " ms\n";
        }
};

#endif