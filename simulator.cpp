#include "enums.h"
#include "simulator.h"
#include "vehicle.h"
#include "vehicleParams.h"
#include <iostream>
#include <random>
#include <chrono>

using namespace std::chrono;

Simulator::Simulator() {
    auto start = steady_clock::now();
    std::mt19937 gen(system_clock::now().time_since_epoch().count());
    
    for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        std::uniform_int_distribution<int> dist(0, 4);
        int randIndex = dist(gen);
        
        this->vehicles[i] = Vehicle(simParams[randIndex].companyName, 
                                    simParams[randIndex].cruiseSpeed, 
                                    simParams[randIndex].batteryCapacity,
                                    simParams[randIndex].chargeTime,
                                    simParams[randIndex].energyUse,
                                    simParams[randIndex].passengerCount,
                                    simParams[randIndex].faultProbability);
        std::cout << "vehicle " << i << " company: " << vehicles[i].getCompanyName() << std::endl;
    }

    auto end = steady_clock::now();
    auto duration = end - start;

    std::cout << "generation time: " << duration.count() << std::endl;
}

void Simulator::simulate() {

    auto simStartTime = steady_clock::now();
    auto simEndTime = simStartTime + duration<int>(simDuration);

    for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads[i] = std::thread(&Vehicle::simulate,
                                        std::ref(vehicles[i]),
                                        simEndTime,
                                        std::ref(rng[i]));
    }

    for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads[i].join();
    }
    
}