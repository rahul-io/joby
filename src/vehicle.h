#pragma once

#include <chrono>
#include <random>

#include "chargingStation.h"
#include "consts.h"

class Vehicle {
 public:
  Vehicle() {}
  Vehicle(CompanyName companyName, int cruiseSpeed, int batteryCapacity,
          double timeToCharge, double energyUse, int passengerCount,
          double faultProbability);

  void simulate(std::chrono::steady_clock::time_point simEndTime,
                std::mt19937& rng, chargingStation& simChargingStation);
  void fly(std::chrono::steady_clock::time_point simEndTime);
  void charge(std::chrono::steady_clock::time_point simEndTime,
              chargingStation& simChargingStation);

  // getters (only used for unit tests to validate vehicle data)
  double getCruiseSpeed() { return cruiseSpeed; }
  int getbatteryCapacity() { return batteryCapacity; }
  std::chrono::duration<double> getTimeToCharge() { return timeToCharge; }
  double getEnergyUse() { return energyUse; }
  int getPassengerCount() { return passengerCount; }
  double getFaultProbability() { return faultProbability; }

  VehicleState getState() { return state; }
  std::chrono::duration<double> getTotalFlightTime() { return totalFlightTime; }
  std::chrono::duration<double> getTotalChargeTime() { return totalChargeTime; }
  std::chrono::duration<double> getTotalChargerWaitTime() {
    return totalChargerWaitTime;
  }
  int getFaultCounter() { return faultCounter; }
  double getOdometer() { return odometer; }
  double getBatteryLevel() { return batteryLevel; }
  void clearData();
  void drainBattery();

 private:
  CompanyName companyName;
  double cruiseSpeed;   // miles per (simulated) minute (realworld second)
  int batteryCapacity;  // kWh
  std::chrono::duration<double>
      timeToCharge;         // (simulated) minutes (realworld seconds)
  double energyUse;         // kWh per mile
  int passengerCount;       // human bodies
  double faultProbability;  // faults per (simulated) minute (realworld second)

  // vehicle stats
  VehicleState state = VehicleState::START;
  std::chrono::duration<double> totalFlightTime = std::chrono::seconds{0};
  std::chrono::duration<double> totalChargeTime = std::chrono::seconds{0};
  std::chrono::duration<double> totalChargerWaitTime = std::chrono::seconds{0};
  int faultCounter = 0;
  double odometer = 0;

  // battery charging info
  double batteryLevel;
  void trackFaults(std::chrono::steady_clock::time_point simEndTime,
                   std::mt19937& rng);
  friend class processor;
};