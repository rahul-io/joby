#pragma once
#include <chrono>

enum CompanyName { alpha = 0, beta, charlie, delta, echo };

enum VehicleState {
  START = 0,
  FLYING,
  CHARGING,
  COMPLETE,
};

static const int MINUTES_PER_HOUR = 60;
static const int NUMBER_OF_COMPANIES = 5;
static const int NUMBER_OF_VEHICLES = 20;
static const std::chrono::duration<int> SIM_DURATION =
    std::chrono::seconds{2};  // (simulated) minutes