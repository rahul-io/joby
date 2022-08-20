#include "vehicle.h"

#include <math.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "enums.h"
#include "stdlib.h"

using namespace std::chrono;

Vehicle::Vehicle(CompanyName companyName, int cruiseSpeed, int batteryCapacity,
                 double chargeTime, double energyUse, int passengerCount,
                 double faultProbability, int index)
    : companyName(companyName),
      cruiseSpeed(cruiseSpeed),
      batteryCapacity(batteryCapacity),
      energyUse(energyUse),
      passengerCount(passengerCount),
      faultProbability(faultProbability),
      index(index) {
  this->batteryLevel = batteryCapacity;
  this->cruiseSpeed /= MINUTES_PER_HOUR;
  this->chargeTime = duration<double>(chargeTime * MINUTES_PER_HOUR);

  // converting probability of failure per hour to probability of failure per
  // minute
  this->faultProbability =
      1 - pow(1 - this->faultProbability, (double)1 / MINUTES_PER_HOUR);
}

void Vehicle::simulate(steady_clock::time_point simEndTime, std::mt19937& rng,
                       chargingStation& simChargingStation) {
  rng.seed(std::hash<std::thread::id>()(std::this_thread::get_id()));
  std::thread faultCounterThread(&Vehicle::trackFaults, this, simEndTime,
                                 std::ref(rng));

  while (std::chrono::steady_clock::now() < simEndTime) {
    switch (this->state) {
      case START:
        this->state = VehicleState::FLYING;
      case FLYING:
        fly(simEndTime);
        break;
      case CHARGING:
        charge(simEndTime, simChargingStation);
        break;
      case COMPLETE:
        break;
      default:
        std::cout << "we shouldn't be here\n";
    }
  }

  faultCounterThread.join();
  return;
}

void Vehicle::printInfo() {
  std::printf(
      "index: %i \tcompanyName: %i\tbatteryLevel: %f\ttotalFlightTime: "
      "%f\ttotalChargeTime: %f\ttotalChargingWaitTime: %f\todometer: "
      "%f\tfaultCounter: %i\n",
      index, companyName, batteryLevel, totalFlightTime.count(),
      totalChargeTime.count(), totalChargerWaitTime.count(), odometer,
      faultCounter);
  return;
}

void Vehicle::fly(steady_clock::time_point simEndTime) {
  auto flightStartTime = steady_clock::now();
  duration<double> currentFlightDuration;
  double currentFlightDistance;

  while (steady_clock::now() < simEndTime && batteryLevel > 0) {
    std::this_thread::sleep_for(1s);
    auto now = steady_clock::now();
    currentFlightDuration = now - flightStartTime;
    currentFlightDistance = currentFlightDuration.count() * cruiseSpeed;
    batteryLevel = batteryCapacity - (currentFlightDistance * energyUse);
  }

  // handle battery drain overflows
  if (batteryLevel <= 0) {
    auto subFlightDistance = (0 - batteryLevel) / energyUse;
    currentFlightDistance -= subFlightDistance;
    currentFlightDuration -= duration<double>(subFlightDistance / cruiseSpeed);
    batteryLevel = 0;
    this->state = VehicleState::CHARGING;
  }

  // handle sim clock overflows
  if (steady_clock::now() >= simEndTime) {
    duration<double> subFlightTime = steady_clock::now() - simEndTime;
    currentFlightDuration -= subFlightTime;
    currentFlightDistance -= (subFlightTime * cruiseSpeed).count();
    this->state = VehicleState::COMPLETE;
  }

  totalFlightTime += currentFlightDuration;
  odometer += currentFlightDistance;
  return;
}

void Vehicle::charge(std::chrono::steady_clock::time_point simEndTime,
                     chargingStation& simChargingStation) {
  auto chargeWaitingStart = steady_clock::now();
  bool startedCharging =
      simChargingStation.charger.try_acquire_until(simEndTime);
  auto chargeWaitingEnd = steady_clock::now();
  totalChargerWaitTime += chargeWaitingEnd - chargeWaitingStart;

  if (startedCharging && steady_clock::now() < simEndTime) {
    // std::printf("Vehicle %i started charging\n", this->index);
    duration<double> currentChargeTime = duration<double>(std::min(
        this->chargeTime.count(),
        double(duration<double>(simEndTime - steady_clock::now()).count())));
    std::this_thread::sleep_for(currentChargeTime);
    this->totalChargeTime += currentChargeTime;
    this->batteryLevel = batteryCapacity;
    // std::printf("Vehicle %i finished charging\n", this->index);
    simChargingStation.charger.release();
    this->state = FLYING;
  } else {
    this->state = COMPLETE;
  }

  return;
}

void Vehicle::trackFaults(steady_clock::time_point simEndTime,
                          std::mt19937& rng) {
  while (steady_clock::now() < simEndTime) {
    std::this_thread::sleep_for(1s);
    double randDouble = (double)rng() / UINT32_MAX;
    faultCounter += (randDouble < this->faultProbability) ? 1 : 0;
  }
  return;
}

/*
 TODO LIST
 tests
 documentation
*/
