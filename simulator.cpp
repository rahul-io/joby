#include "enums.h"
#include "simulator.h"
#include "vehicle.h"
#include <random>

using namespace std::chrono;

Simulator::Simulator() {
    this->vehicles[0] = Vehicle(alpha, 120, 320, 0.6, 1.6, 4, 0.9);
}

void Simulator::simulate() {

    auto simStartTime = steady_clock::now();
    auto simEndTime = simStartTime + duration<int>(simDuration);

    for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads[i] = std::thread(&Vehicle::simulationStateMachine, std::ref(vehicles[i]), simEndTime, std::ref(rng[i]));
    }

    for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads[i].join();
    }
    
}