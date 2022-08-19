#pragma once

#include <queue>
#include <random>
#include <thread>
#include <vector>

#include "chargingStation.h"
#include "vehicle.h"

class Simulator {
 public:
  Simulator();

  void simulate();

 private:
  static chargingStation simChargingStation;
  inline static const int NUMBER_OF_VEHICLES = 20;
  inline static const int simDuration = 180;  // (simulated) minutes
  inline static std::thread vehicleThreads[NUMBER_OF_VEHICLES];
  inline static std::mt19937 rng[NUMBER_OF_VEHICLES];
  inline static Vehicle vehicles[NUMBER_OF_VEHICLES];
};