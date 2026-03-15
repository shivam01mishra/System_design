#include<map>
#include<memory>
#include"VehicleType.h"
#include"SlotManager.h"
#include"Ticket.h"
#include<iostream>

class ParkingLot{
    std::map<VehicleType ,std::shared_ptr<SlotManager>>vehicleManager;
    public:
    void addVehicleParking(VehicleType vehicle, int numberOfSlot);
    std::shared_ptr<Ticket> pakrVehile(VehicleType vehicle);
    void unpark(std::shared_ptr<Ticket>ticket);
};
 
