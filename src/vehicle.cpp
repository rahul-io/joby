#include "vehicle.h"

#include <math.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "stdlib.h"

using namespace std::chrono;

Vehicle::Vehicle(CompanyName companyName, int cruiseSpeed, int batteryCapacity,
                 double timeToCharge, double energyUse, int passengerCount,
                 double faultProbability)
    : companyName(companyName),
      cruiseSpeed(cruiseSpeed),
      batteryCapacity(batteryCapacity),
      energyUse(energyUse),
      passengerCount(passengerCount),
      faultProbability(faultProbability) {
  this->batteryLevel = batteryCapacity;
  this->cruiseSpeed /= MINUTES_PER_HOUR;
  this->timeToCharge = duration<double>(timeToCharge * MINUTES_PER_HOUR);

  // converting probability of failure per hour to probability of failure per
  // minute
  this->faultProbability =
      1 - pow(1 - this->faultProbability, (double)1 / MINUTES_PER_HOUR);
}

void Vehicle::simulate(steady_clock::time_point simEndTime, std::mt19937& rng,
                       chargingStation& simChargingStation) {
  // start tracking faults in  a separate thread, independent of flying/charging
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

void Vehicle::fly(steady_clock::time_point simEndTime) {
  auto flightStartTime = steady_clock::now();
  duration<double> currentFlightDuration;
  double currentFlightDistance;

  // Every second, measure time and distance travelled
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
  // Try to acquire charger semaphore, block until semaphore is
  // acquired and log total wait time.
  auto chargeWaitingStart = steady_clock::now();
  bool startedCharging =
      simChargingStation.charger.try_acquire_until(simEndTime);
  auto chargeWaitingEnd = steady_clock::now();
  totalChargerWaitTime += chargeWaitingEnd - chargeWaitingStart;

  if (startedCharging && steady_clock::now() < simEndTime) {
    // We don't want to keep charging after the simulation is over, so only
    // charge for the charge time or until the simulation ends (whichever is
    // smaller).
    duration<double> currentChargeTime = duration<double>(std::min(
        this->timeToCharge.count(),
        double(duration<double>(simEndTime - steady_clock::now()).count())));
    std::this_thread::sleep_for(currentChargeTime);
    this->totalChargeTime += currentChargeTime;
    this->batteryLevel = batteryCapacity;
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

void Vehicle::clearData() {
  this->state = START;
  this->totalFlightTime = seconds{0};
  this->totalChargeTime = seconds{0};
  this->totalChargerWaitTime = seconds{0};
  this->faultCounter = 0;
  this->odometer = 0;
}

void Vehicle::drainBattery() { batteryLevel = 0; }

/*
 TODO LIST
 tests
 documentation
*/
