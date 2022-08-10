#pragma once

#include "common.h"

class vehicle {
 public:
  vehicle(int cruiseSpeed, int batteryCapacity);
  void fly();
  void charge();

 private:
  companyType company;
  int cruiseSpeed;
  int batteryCapacity;
  float chargeTime;
  float energyUse;
  int passengerCount;
  float faultProbability;

  float flightTime;
  float batteryLevel;
  int faultCounter;
  float odometer;

  // battery charging info
  int numberOfCharges;
  int currentChargeTime;
  int avgChargeTime;
};