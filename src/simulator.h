#pragma once

#include <random>
#include <thread>
#include <vector>

#include "chargingStation.h"
#include "processor.h"
#include "vehicle.h"

class Simulator {
 public:
  Simulator();

  void simulate();

 private:
  static chargingStation simChargingStation;
  static std::array<std::thread, NUMBER_OF_VEHICLES> vehicleThreads;
  static std::array<std::mt19937, NUMBER_OF_VEHICLES> rng;
  static std::array<Vehicle, NUMBER_OF_VEHICLES> vehicles;
  static processor simProcessor;
};