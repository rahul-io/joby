#include "enums.h"
#include "simulator.h"
#include "vehicle.h"


/**
Orchestrator | Start your job, 1 charging slot| figure out the simulator|
A            |    time0 -Flying               | time0-1 transition time | time 1
B            |          -Flying->Waiting      | Everybody who's waiting |
B            |          -Flying->Waiting      | Everybody who's waiting |
B            |          -Flying->Waiting      | Everybody who's waiting |
B            |          -Waiting              | Everybody who's waiting |
C            |          -Charging->FLying     |                         |
*/

Simulator::Simulator(int elapseTimeInMinutes, std::vector<Vehicle> vehicles) {
    // create vector of vehicles
    
    this->elapseTimeInMinutes = elapseTimeInMinutes;
    this->vehicles = vehicles;
}

void Simulator::simulate() {
    // create a thread for each vehicle

    // start execution thread for vehicle

    // call fly on flying boys
    for (auto vehicle : vehicles) {
        vehicle.fly(); // asynchronously
    }
    // call charge on charging boys
    // call chargewait on charging wait boys

    // after 3 calls are OVER then call Pick charge

    // sleep depends on the time left
    sleep(1000);
}

void Charger::tryToCharge(Vehicle* chargingVehicle) {
    if (chargeSlot > 0) {
        chargeSlot--;
        Vehicle->charge();
    }
    else {
        chargingQueue.push(chargingVehicle);
    }
}

void Charger::free() {
    chargeSlot++;
}

void Simulator::pickCharges() {
    if (this->chargeSlot >= 0) {
        return;
    }

    while (this->chargeSlot <= 0) {
        if (this->chargingQueue.size() == 0) { break; }

        Vehicle* chargeReadyVehicle = this->chargingQueue.pop();
        chargeReadyVehicle->chargeReady(this->elapsedTimeInMintues);
        this->chargeSlot = -1;
        //
        // auto mostWaitTime = -1;
        // Vehicle* mostWaitTimeVehicle;
        // for (Vehicle vehicle : vehicles) {
        //     if (vehicle.getVehicleState() != VehicleState::CHARGING_WAIT) { continue; }
            
        //     auto potentialChargeWaitTime = vehicle.getCurrentChargeWaitTime();
        //     if (potentialChargeWaitTime > mostWaitTime) {
        //         mostWaitTime = vehicle.getCurrentChargeWaitTime();
        //         mostWaitTimeVehicle = &vehicle;
        //     }
        // }

        // if(mostWaitTimeVehicle->getVehicleState() == VehicleState::NOT_WORKING) { break; }

        // if (chargeSlot > 0) {
        //     mostWaitTimeVehicle->chargeReady(this->elapsedTimeInMintues);
        // }
        // this->chargeSlot -= 1;
    }
 
}