#include "enums.h"
#include "simulator.h"
#include "vehicle.h"
#include <thread>

/**
Orchestrator | Start your job, 1 charging slot| figure out the simulator|
A            |    time0 -Flying               | time0-1 transition time | time 1
B            |          -Flying->Waiting      | Everybody who's waiting |
B            |          -Flying->Waiting      | Everybody who's waiting |
B            |          -Flying->Waiting      | Everybody who's waiting |
B            |          -Waiting              | Everybody who's waiting |
C            |          -Charging->FLying     |                         |
*/

Simulator::Simulator(int simDuration) : simDuration(simDuration) {
    // create vector of vehicles
    
}

void Simulator::simulate() {
    // create a thread for each vehicle
    std::thread vehicleThreads[20];

    std::time_t startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // call fly on flying boys
    for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads[i] = std::thread(&Vehicle::simulationStateMachine, vehicles[i], startTime, simDuration);// asynchronously
    }

    for (int i = 0; i < NUMBER_OF_VEHICLES; i++) {
        vehicleThreads[i].join();
    }

    // call chargewait on charging wait boys

    // after 3 calls are OVER then call Pick charge

    // sleep depends on the time left
    
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