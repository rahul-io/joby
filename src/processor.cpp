#include "processor.h"

#include <iomanip>
#include <iostream>
processor::processor() {
  for (int i = 0; i < NUMBER_OF_COMPANIES; i++) {
    aggregateData[i].companyNameString = companyNameStrings[i];
  }
}

void processor::processVehicle(const Vehicle& vehicle) {
  int vehicleType = vehicle.companyName;

  aggregateData[vehicleType].numVehicles++;

  aggregateData[vehicleType].avgFlightTime =
      ((aggregateData[vehicleType].avgFlightTime *
        (aggregateData[vehicleType].numVehicles - 1)) +
       (vehicle.totalFlightTime)) /
      aggregateData[vehicleType].numVehicles;

  aggregateData[vehicleType].avgChargeTime =
      ((aggregateData[vehicleType].avgChargeTime *
        (aggregateData[vehicleType].numVehicles - 1)) +
       (vehicle.totalChargeTime)) /
      aggregateData[vehicleType].numVehicles;

  aggregateData[vehicleType].avgChargerWaitTime =
      ((aggregateData[vehicleType].avgChargerWaitTime *
        (aggregateData[vehicleType].numVehicles - 1)) +
       (vehicle.totalChargerWaitTime)) /
      aggregateData[vehicleType].numVehicles;

  aggregateData[vehicleType].maxFaults =
      std::max(aggregateData[vehicleType].maxFaults, vehicle.faultCounter);

  aggregateData[vehicleType].totalPassengerDistance +=
      vehicle.odometer * vehicle.passengerCount;

  return;
}

void processor::prettyPrint() {
  std::cout << std::setw(17) << "Company Name" << std::setw(23)
            << "Number of Vehicles" << std::setw(24) << "Average Flight Time"
            << std::setw(26) << "Average Charging Time" << std::setw(30)
            << "Average Charger Wait Time" << std::setw(15) << "Max Faults"
            << std::setw(36) << "Total Passenger Travel Distance" << '\n';

  std::cout << std::string(171, '-') << '\n';

  for (auto a : aggregateData) {
    std::cout << std::setw(17) << a.companyNameString << std::setw(23)
              << a.numVehicles << std::setw(16) << a.avgFlightTime.count()
              << " minutes" << std::setw(18) << a.avgChargeTime.count()
              << " minutes" << std::setw(22) << a.avgChargerWaitTime.count()
              << " minutes" << std::setw(15) << a.maxFaults << std::setw(30)
              << a.totalPassengerDistance << " miles" << '\n';
  }
  std::cout << std::endl;

  return;
}