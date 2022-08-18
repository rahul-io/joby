#include "enums.h"
#include "simulator.h"
#include "vehicle.h"
#include <thread>
#include <random>

using namespace std::chrono;

Simulator::Simulator() {
    this->vehicle = Vehicle(alpha, 120, 320, 0.6, 1.6, 4, 0.9);
}

void Simulator::simulate() {
    // create a thread for each vehicle
    std::thread vehicleThreads;

    // create an rng for each vehicle
    std::mt19937 rng(std::hash<std::thread::id>()(std::this_thread::get_id()));

    auto simStartTime = steady_clock::now();
    auto simEndTime = simStartTime + duration<int>(simDuration);

    //for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        Vehicle& vehicleRef = vehicle;
        vehicleThreads = std::thread(&Vehicle::simulationStateMachine, vehicleRef, simEndTime, std::ref(rng));
    //}

    //for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads.join();
    //}
    
}