#pragma once

#include "vehicle.h"
#include <queue>

// needs a semaphore
class chargingStation {
    public:
        chargingStation(int numChargers);
        void allocate();
        void enterCharger(Vehicle* chargingVehicle);

    private:
        int chargerCounter = 3;
        std::queue<Vehicle*> chargingQueue;
};