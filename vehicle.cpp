#include "vehicle.h"
#include "enums.h"
#include "stdlib.h"

Vehicle::Vehicle(
    CompanyType company,
    int cruiseSpeed, 
    int batteryCapacity, 
    float chargeTime, 
    float energyUse, 
    int passengerCount, 
    float faultProbability) :
        company(company),
        batteryCapacity(batteryCapacity),
        chargeTime(chargeTime),
        energyUse(energyUse),
        passengerCount(passengerCount),
        faultProbability(faultProbability) {
          this->batteryLevel = batteryCapacity;

          this->cruiseSpeed *= MINUTES_PER_HOUR;
          this->chargeTime *= MINUTES_PER_HOUR;
          this->faultProbability /= MINUTES_PER_HOUR;
        }

void Vehicle::simulationStateMachine(time_t startTime, int simDuration) {
  while (/*current time is less than end time*/) {
    switch (this->state) {
      case START:
        this->state = VehicleState::FLYING;
      case FLYING:
        fly();
    }
  }
}

void Vehicle::fly(/*simulation end time*/) {

  //state = VehicleState::FLYING;
  //flightTime += elapsedTimeInMinutes;

  

  int elapsedDistance = elapsedTimeInMinutes * cruiseSpeed;
  odometer += elapsedDistance;
  batteryLevel -= elapsedDistance * energyUse;

  if (batteryLevel <= 0) {
    this->state = VehicleState::CHARGING_WAIT;
    // check this math
    odometer += batteryLevel / energyUse;
    // Update odometer with negative values.
    this->batteryLevel = 0;
    Charger.tryToCharge(this);
  }
}

void Vehicle::fault(int elapsedTimeInMinutes) {
  faultCounter += (rand() < this->faultProbability * elapsedTimeInMinutes) ? 1 : 0;
}

// 
void Vehicle::chargeWait(int elapsedTimeInMinutes) {
  state = VehicleState::CHARGING_WAIT;
  totalChargerWaitTime += 1;
} 

void Vehicle::chargeReady(int elapsedTimeInMintues) {
  this->state = VehicleState::CHARGING;
  this->totalChargerWaitTime = this->currentChargeWaitTime;

  this->currentChargeWaitTime = 0;
}

void Vehicle::charge(int elapsedTimeInMinutes) {
  // Each slice of simulation is a minute.
  this->state = VehicleState::CHARGING;
  this->currentChargeTime += elapsedTimeInMinutes;
 
  if (this->currentChargeTime >= this->chargeTime) {
    this->batteryLevel = this->batteryCapacity;
    this-> state = VehicleState::FLYING;
    Charger.free();
    // let go of the charge mutex; increment the mutex.
  }
}

// Fault means it can fly for the sake of brevity. 
// Things to keep track of while flying
// * Distance: odometer
// * flight time: flightTime
// * Battery level: batteryLevel
