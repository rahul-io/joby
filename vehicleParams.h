#include "enums.h"

struct vehicleParams {
  CompanyName companyName;
  int cruiseSpeed; 
  int batteryCapacity; 
  double chargeTime;
  double energyUse;
  int passengerCount;
  double faultProbability;
};

vehicleParams simParams[5] = {{alpha,   120,  320,  0.6,  1.6,  4,  0.25},
                              {beta,    100,  100,  0.2,  1.5,  5,  0.10},
                              {charlie, 160,  220,  0.8,  2.2,  3,  0.05},
                              {delta,   90,   120,  0.62, 0.8,  2,  0.22},
                              {echo,    30,   150,  0.3,  5.8,  2,  0.61},
                             };