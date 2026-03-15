#include "ParkingLot.h"
 #include<iostream>
  void ParkingLot::addVehicleParking(VehicleType vehicle, int numberOfSlot)
    {
        vehicleManager[vehicle]=  std::make_shared<SlotManager>(vehicle,numberOfSlot);
    }
std::shared_ptr<Ticket> ParkingLot::pakrVehile(VehicleType vehicle){

    if(vehicleManager.find(vehicle) == vehicleManager.end()){
        std::cout<<"We do not have parking feature for vehicle type : "
                 << toString(vehicle) << std::endl;
        return nullptr;
    }

    std::shared_ptr<SlotManager> slotManager = vehicleManager[vehicle];

    if(!slotManager->hasFreeSlot()){
        std::cout<<"No free parking area for this vehicle"<<std::endl;
        return nullptr;
    }

    std::cout<<"Please collect your Ticket of Type: "
             << toString(vehicle) << std::endl;

    return std::make_shared<Ticket>(slotManager->park(), vehicle, 0);
}
    void ParkingLot::unpark(std::shared_ptr<Ticket> ticket){
        vehicleManager[ticket->getVehicleType()]->freeSlot(ticket->getSlotId());
         std::cout<<"vehicle have been unparked"<<std::endl;

    }