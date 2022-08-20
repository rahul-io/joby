#pragma once
#include <array>
#include <chrono>
#include <string>

#include "consts.h"
#include "vehicle.h"

class processor {
 public:
  processor();
  void processVehicle(const Vehicle& vehicle);
  void prettyPrint();
  void clearData();

 private:
  struct typeInfo {
    std::string companyNameString = "";
    int numVehicles = 0;
    std::chrono::duration<double> avgFlightTime = std::chrono::seconds{0};
    std::chrono::duration<double> avgChargeTime = std::chrono::seconds{0};
    std::chrono::duration<double> avgChargerWaitTime = std::chrono::seconds{0};
    int maxFaults = 0;
    double totalPassengerDistance = 0;
  };
  std::array<std::string, NUMBER_OF_COMPANIES> companyNameStrings{
      "Alpha", "Beta", "Charlie", "Delta", "Echo"};
  std::array<typeInfo, NUMBER_OF_COMPANIES> aggregateData;
};