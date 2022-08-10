#include "charger.h"
#include "vehicle.h"

class Simulator {
public:
    void Simulate();
    std::vector<vehicle> testVehicles;

private:
    chargingStation simCharger;

};