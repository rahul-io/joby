#include "processor.h"

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

  aggregateData[vehicleType].maxFaults =
      std::max(aggregateData[vehicleType].maxFaults, vehicle.faultCounter);

  aggregateData[vehicleType].totalPassengerDistance +=
      vehicle.odometer * vehicle.passengerCount;
}