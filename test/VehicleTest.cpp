#include <array>
#include <chrono>
#include <random>

#include "../src/vehicle.h"
#include "../src/vehicleParams.h"
#include "gtest/gtest.h"

using namespace std::chrono;

class VehicleTest : public ::testing::Test {
 protected:
  void SetUp() override {
    std::mt19937 gen(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 4);
    int randIndex = dist(gen);

    testVehicle = Vehicle(
        simParams[randIndex].companyName, simParams[randIndex].cruiseSpeed,
        simParams[randIndex].batteryCapacity, simParams[randIndex].timeToCharge,
        simParams[randIndex].energyUse, simParams[randIndex].passengerCount,
        simParams[randIndex].faultProbability);
  }

  Vehicle testVehicle;
  chargingStation testChargingStation;
};

TEST_F(VehicleTest, testFly) {
  testVehicle.clearData();
  std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(1, 10);
  auto plannedFlightTime = std::chrono::seconds{dist(gen)};

  auto start = steady_clock::now();
  testVehicle.fly(steady_clock::now() + plannedFlightTime);

  // testing that estimated flight time ≈ real flight time;
  EXPECT_NEAR((testVehicle.getTotalFlightTime()).count(),
              plannedFlightTime.count(), 0.1);

  // testing that calculated flight distance ≈ real flight distance;
  double plannedOdometer =
      (plannedFlightTime).count() * testVehicle.getCruiseSpeed();
  EXPECT_NEAR(testVehicle.getOdometer(), (plannedOdometer), 0.1);

  // testing that calculated battery level ≈ real battery level;
  double plannedBatteryLevel = testVehicle.getbatteryCapacity() -
                               (plannedOdometer * testVehicle.getEnergyUse());
  EXPECT_NEAR(testVehicle.getBatteryLevel(), plannedBatteryLevel, 0.1);
}

TEST_F(VehicleTest, testCharge) {
  testVehicle.clearData();
  testVehicle.drainBattery();
  auto start = steady_clock::now();
  testVehicle.charge(steady_clock::now() + duration<int>(180),
                     testChargingStation);
  auto end = steady_clock::now();
  auto chargeDuration = duration_cast<seconds>(end - start);
  EXPECT_NEAR(chargeDuration.count(), testVehicle.getTimeToCharge().count(),
              0.1);
}