#pragma once

#include "charger.h"
#include "vehicle.h"
#include <vector>
#include <queue>

class Simulator {

public:
    Simulator();
    void simulate();

private:
    inline static const int NUMBER_OF_VEHICLES = 20;
    inline static const int simDuration = 180; // (simulated) minutes
    Vehicle vehicle;
};