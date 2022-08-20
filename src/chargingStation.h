#pragma once

#include <semaphore>

#include "consts.h"

struct chargingStation {
  std::counting_semaphore<NUM_CHARGERS> charger{NUM_CHARGERS};
};