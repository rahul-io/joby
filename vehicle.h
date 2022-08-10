#pragma once

#include "enums.h"

class Vehicle {
 public:
  Vehicle() {}
  Vehicle(
    CompanyType companyType,
    int cruiseSpeed, 
    int batteryCapacity, 
    float chargeTime, 
    float energyUse, 
    int passengerCount, 
    float faultProbability);

  void fly(int);
  void charge(int);
  void chargeWait(int);
  
  // In-between actions
  void chargeReady(int);

  VehicleState getVehicleState() { return this->state;}
  void simulationStateMachine();
  float getCurrentChargeWaitTime() { return this->currentChargeWaitTime;}

 private:
  VehicleState state = VehicleState::START;
  CompanyType company;
  int cruiseSpeed; // miles per minute
  int batteryCapacity; // kWh
  float chargeTime; // minutes
  float energyUse; // kWh per mile
  int passengerCount; // human bodies
  float faultProbability; // faults per minute

  // vehicle stats
  float flightTime = 0;
  float totalChargeTime = 0;
  float currentChargeTime = 0;
  float totalChargerWaitTime = 0;
  int faultCounter = 0;
  float odometer = 0;

  // battery charging info
  // battery state.
  float batteryLevel;

  void fault(int elapsedFaultProbability);
};