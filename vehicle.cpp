#include "vehicle.h"
#include "enums.h"
#include "stdlib.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <math.h>

using namespace std::chrono;

Vehicle::Vehicle(
    CompanyName companyName,
    int cruiseSpeed, 
    int batteryCapacity, 
    double chargeTime, 
    double energyUse, 
    int passengerCount, 
    double faultProbability) :
        companyName(companyName),
        cruiseSpeed(cruiseSpeed),
        batteryCapacity(batteryCapacity),
        chargeTime(chargeTime),
        energyUse(energyUse),
        passengerCount(passengerCount),
        faultProbability(faultProbability) {
          this->batteryLevel = batteryCapacity;

          this->cruiseSpeed /= MINUTES_PER_HOUR;
          this->chargeTime /= MINUTES_PER_HOUR;
          
          // converting probability of failure per hour to probability of failure per minute
          this->faultProbability = 1 - pow(1-this->faultProbability,
                                          (double)1/MINUTES_PER_HOUR);
        }

void Vehicle::simulate(steady_clock::time_point simEndTime, std::mt19937& rng, int index) {
  rng.seed(std::hash<std::thread::id>()(std::this_thread::get_id()));
  std::thread faultCounterThread(&Vehicle::trackFaults,
                                  this,
                                  simEndTime,
                                  std::ref(rng));

  while (std::chrono::steady_clock::now() < simEndTime) {
    switch (this->state) {
      case START:
        this->state = VehicleState::FLYING;
      case FLYING:
        fly(simEndTime, index);
        break;
      case CHARGING:
        charge();
        break;
      case COMPLETE:
        break;
      default:
        std::cout << "we shouldn't be here\n";
    }
  }

  faultCounterThread.join();
  std::printf("batteryLevel: %f\ttotalFlightTime: %f\todometer: %f\tfaultCounter: %i\n", batteryLevel, totalFlightTime.count(), odometer, faultCounter);
}

void Vehicle::fly(steady_clock::time_point simEndTime, int index) {
  auto flightStartTime = steady_clock::now();
  duration<double> currentFlightDuration;
  double currentFlightDistance;

  while (steady_clock::now() < simEndTime && batteryLevel > 0) {
    std::this_thread::sleep_for(1s);
    auto now = steady_clock::now();
    currentFlightDuration = now - flightStartTime;
    currentFlightDistance = currentFlightDuration.count() * cruiseSpeed;
    batteryLevel = batteryCapacity - (currentFlightDistance * energyUse);

    std::printf("Vehicle index: %i\tCompany Name: %i\tcurrentFlightDuration: %f\tcurrentFlightDistance: %f\tbatteryLevel: %f\n", index, companyName, currentFlightDuration.count(), currentFlightDistance, batteryLevel);
  }

  // handle battery drain overflows
  if (batteryLevel <= 0) {
    auto subFlightDistance = (0 - batteryLevel) / energyUse;
    currentFlightDistance -= subFlightDistance;
    currentFlightDuration -= duration<double>(subFlightDistance / cruiseSpeed);
    batteryLevel = 0;
    this->state = VehicleState::CHARGING;
    std::cout << "battery dead, charging" << std::endl;
  }

  // handle sim clock overflows
  if (steady_clock::now() >= simEndTime) {
    duration<double> subFlightTime = steady_clock::now() - simEndTime;
    currentFlightDuration -= subFlightTime;
    currentFlightDistance -= (subFlightTime * cruiseSpeed).count();
    this->state = VehicleState::COMPLETE;
    std::cout << "simulation complete\n";
  }

  totalFlightTime += currentFlightDuration;
  odometer += currentFlightDistance;
  return;

}

void Vehicle::trackFaults(steady_clock::time_point simEndTime, std::mt19937& rng) {
  while (steady_clock::now() < simEndTime) {
    std::this_thread::sleep_for(1s);
    double randDouble = (double) rng() / UINT32_MAX;
    faultCounter += (randDouble < this->faultProbability) ? 1 : 0;
  }
  return;
}

 /*
  TODO LIST
  instantiate all vehicles
  charger
  calc
  tests
  mutex on fault counter
 */

void Vehicle::charge() {
  // Each slice of simulation is a minute.
  /*this->state = VehicleState::CHARGING;
  this->currentChargeTime += elapsedTimeInMinutes;
 
  if (this->currentChargeTime >= this->chargeTime) {
    this->batteryLevel = this->batteryCapacity;
    this-> state = VehicleState::FLYING;
    Charger.free();
    // let go of the charger mutex; increment the mutex.
  }*/
}

// Fault means it can fly for the sake of brevity. 
// Things to keep track of while flying
// * Distance: odometer
// * flight time: flightTime
// * Battery level: batteryLevel
