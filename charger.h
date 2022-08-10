#pragma once

#include "vehicle.h"
#include <vector>
#include <queue>

#define charger std::queue<vehicle*>

class chargingStation {
    public:
        chargingStation(int numChargers);
        void allocate(vehicle);

    private:
        // maybe make this a priority queue based on queue size
        std::vector<charger> chargerList;
};