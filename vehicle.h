#pragma once

#include "enums.h"
#include <chrono>
#include <random>

class Vehicle {
 public:
  Vehicle() {}
  Vehicle(
    CompanyName companyName,
    int cruiseSpeed, 
    int batteryCapacity, 
    double chargeTime, 
    double energyUse, 
    int passengerCount, 
    double faultProbability);

  void simulationStateMachine(std::chrono::steady_clock::time_point simEndTime, std::mt19937& rng);
  void fly(std::chrono::steady_clock::time_point simEndTime, std::mt19937& rng);
  void charge();

 private:
  VehicleState state = VehicleState::START;
  CompanyName companyName;
  int batteryCapacity; // kWh
  int passengerCount; // human bodies
  double energyUse; // kWh per mile
  
  double cruiseSpeed; // miles per (simulated) minute (realworld second)
  double chargeTime; // (simulated) minutes (realworld seconds)
  double faultProbability; // faults per (simulated) minute (realworld second)
  
  // vehicle stats
  std::chrono::duration<double> totalFlightTime = std::chrono::seconds{0};
  std::chrono::duration<double> totalChargingTime = std::chrono::seconds{0};
  std::chrono::duration<double> totalChargerWaitTime = std::chrono::seconds{0};
  int faultCounter = 0;
  double odometer = 0;

  // battery charging info
  float batteryLevel;

  double fault(std::mt19937& rng);
};