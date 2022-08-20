#pragma once

#include <semaphore>

struct chargingStation {
  chargingStation(){};
  inline static const int NUM_CHARGERS = 3;
  std::counting_semaphore<NUM_CHARGERS> charger{NUM_CHARGERS};
};