#pragma once

#include "vehicle.h"
#include <queue>

// needs a semaphore
class chargingStation {
    public:
        chargingStation(int numChargers);
        void allocate();

    private:
        int chargerCounter = 3;
        std::queue<vehicle*> vehicleQueue;
};