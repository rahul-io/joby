#include "charger.h"
#include "vehicle.h"
#include <vector>
#include <queue>
#include <chrono>

class Simulator {
public:
    Simulator(int simDuration) : {};
    void simulate();

private:
    static const int NUMBER_OF_VEHICLES = 20;
    int simDuration; // in minutes;
    std::vector<Vehicle> vehicles[20];
    std::queue<Vehicle*> chargingQueue;

    void pickCharges();
};