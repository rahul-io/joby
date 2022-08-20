#include <gtest/gtest.h>

#include <chrono>

#include "../src/consts.h"
#include "../src/simulator.h"
#include "../src/vehicle.h"

using namespace std::chrono;

class SimulatorTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Simulator testSim;
};

TEST_F(SimulatorTest, StartsAtZero) {
  std::array<Vehicle, NUMBER_OF_VEHICLES> vehicles = testSim.getVehicles();
  for (int i = 0; i < vehicles.size(); i++) {
    EXPECT_EQ(vehicles[i].getState(), START);
    EXPECT_EQ(vehicles[i].getTotalFlightTime(), seconds{0});
    EXPECT_EQ(vehicles[i].getTotalChargeTime(), seconds{0});
    EXPECT_EQ(vehicles[i].getTotalChargerWaitTime(), seconds{0});
    EXPECT_EQ(vehicles[i].getFaultCounter(), 0);
    EXPECT_EQ(vehicles[i].getOdometer(), 0);
  }
}

TEST_F(SimulatorTest, ValidSimulation) {
  testSim.simulate();
  {
    for (auto v : testSim.getVehicles()) {
      EXPECT_EQ(v.getState(), COMPLETE);
      EXPECT_LT(
          abs(SIM_DURATION - (v.getTotalFlightTime() + v.getTotalChargeTime() +
                              v.getTotalChargerWaitTime())),
          (duration<double>(0.5)));
      EXPECT_GT(v.getOdometer(), 0);
    }
  }
}