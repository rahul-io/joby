#pragma once

#include "charger.h"
#include "vehicle.h"
#include <vector>
#include <queue>
#include <random>
#include <thread>

class Simulator {

public:
    Simulator();
    void simulate();

private:
    inline static const int NUMBER_OF_VEHICLES = 20;
    inline static const int simDuration = 180; // (simulated) minutes
    inline static std::thread vehicleThreads[NUMBER_OF_VEHICLES];
    inline static std::mt19937 rng[NUMBER_OF_VEHICLES];
    inline static Vehicle vehicles[NUMBER_OF_VEHICLES];
};