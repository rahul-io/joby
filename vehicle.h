#pragma once

#include <chrono>
#include <random>

#include "chargingStation.h"
#include "enums.h"

class Vehicle {
 public:
  Vehicle() {}
  Vehicle(CompanyName companyName, int cruiseSpeed, int batteryCapacity,
          double chargeTime, double energyUse, int passengerCount,
          double faultProbability, int index);

  void simulate(std::chrono::steady_clock::time_point simEndTime,
                std::mt19937& rng, chargingStation& simChargingStation);
  void fly(std::chrono::steady_clock::time_point simEndTime);
  void charge(std::chrono::steady_clock::time_point simEndTime,
              chargingStation& simChargingStation);
  void printInfo();
  CompanyName getCompanyName() { return companyName; }

 private:
  VehicleState state = VehicleState::START;
  CompanyName companyName;
  int batteryCapacity;  // kWh
  int passengerCount;   // human bodies
  double energyUse;     // kWh per mile
  int index;

  double cruiseSpeed;  // miles per (simulated) minute (realworld second)
  std::chrono::duration<double>
      chargeTime;           // (simulated) minutes (realworld seconds)
  double faultProbability;  // faults per (simulated) minute (realworld second)

  // vehicle stats
  std::chrono::duration<double> totalFlightTime = std::chrono::seconds{0};
  std::chrono::duration<double> totalChargeTime = std::chrono::seconds{0};
  std::chrono::duration<double> totalChargerWaitTime = std::chrono::seconds{0};
  int faultCounter = 0;
  double odometer = 0;

  // battery charging info
  float batteryLevel;
  void trackFaults(std::chrono::steady_clock::time_point simEndTime,
                   std::mt19937& rng);
  friend class processor;
};