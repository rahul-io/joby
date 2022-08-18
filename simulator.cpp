#include "enums.h"
#include "simulator.h"
#include "vehicle.h"
#include <thread>

using namespace std::chrono;

Simulator::Simulator() {
    this->vehicle = Vehicle(alpha, 120, 320, 0.6, 1.6, 4, 0.25);
}

void Simulator::simulate() {
    // create a thread for each vehicle
    std::thread vehicleThreads;

    auto simStartTime = steady_clock::now();
    auto simEndTime = simStartTime + duration<int>(simDuration);

    //for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        Vehicle& vehicleRef = vehicle;
        vehicleThreads = std::thread(&Vehicle::simulationStateMachine, vehicleRef, simEndTime);
    //}

    //for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads.join();
    //}
    
}