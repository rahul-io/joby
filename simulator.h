#include "charger.h"
#include "vehicle.h"
#include <vector>
#include <queue>

class Simulator {
public:
    Simulator(int elapsedTimeInMinutes, std::vector<Vehicle> vehicles);
    void simulate();

private:
    std::vector<Vehicle> vehicles;
    int elapsedTimeInMintues;
    int chargeSlot=3;
    std::queue<Vehicle*> chargingQueue;

    void pickCharges();
};