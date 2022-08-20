#include "simulator.h"

#include <chrono>
#include <iostream>
#include <random>

#include "vehicle.h"
#include "vehicleParams.h"

using namespace std::chrono;

chargingStation Simulator::simChargingStation;
processor Simulator::simProcessor;
std::array<std::thread, NUMBER_OF_VEHICLES> Simulator::vehicleThreads;
std::array<std::mt19937, NUMBER_OF_VEHICLES> Simulator::rng;
std::array<Vehicle, NUMBER_OF_VEHICLES> Simulator::vehicles;

Simulator::Simulator() {
  auto start = steady_clock::now();
  std::mt19937 gen(system_clock::now().time_since_epoch().count());

  for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
    std::uniform_int_distribution<int> dist(0, 4);
    int randIndex = dist(gen);

    vehicles[i] = Vehicle(
        simParams[randIndex].companyName, simParams[randIndex].cruiseSpeed,
        simParams[randIndex].batteryCapacity, simParams[randIndex].timeToCharge,
        simParams[randIndex].energyUse, simParams[randIndex].passengerCount,
        simParams[randIndex].faultProbability);
  }

  auto end = steady_clock::now();
  auto duration = end - start;
}

void Simulator::simulate() {
  auto simStartTime = steady_clock::now();
  auto simEndTime = simStartTime + SIM_DURATION;

  for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
    vehicleThreads[i] =
        std::thread(&Vehicle::simulate, std::ref(vehicles[i]), simEndTime,
                    std::ref(rng[i]), std::ref(simChargingStation));
  }

  int timeCounter = 0;
  while (steady_clock::now() < simEndTime) {
    std::cout << timeCounter << " minutes\n";
    timeCounter++;
    std::this_thread::sleep_for(1s);
  }

  for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
    vehicleThreads[i].join();
  }

  std::cout << (timeCounter) << " minutes\nSimulation complete!\n\n";

  for (auto vehicle : this->vehicles) {
    simProcessor.processVehicle(vehicle);
  }

  simProcessor.prettyPrint();
  clearData();
  return;
}

void Simulator::clearData() {
  simProcessor.clearData();
  for (auto v : vehicles) {
    v.clearData();
  }
}