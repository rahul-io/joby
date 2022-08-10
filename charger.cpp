#include "charger.h"

void chargingStation::enterCharger(Vehicle* chargingVehicle) {
    if (chargerCounter > 0) {
        chargerCounter--;
        chargingVehicle->charge();
    }
    else {
        chargingQueue.push(chargingVehicle);
    }
}

void Charger::freeCharger() {
    chargeSlot++;
}