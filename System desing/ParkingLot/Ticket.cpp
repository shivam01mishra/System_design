#include "Ticket.h"
    Ticket::Ticket(int slotId,VehicleType vehicle , int entryTime){
        this->slotId=slotId;
        this->vehicle =vehicle ;
        this->entryTime=entryTime;
    }
    int Ticket::getEntryTime() {
        return entryTime;
    }
    int Ticket::getSlotId() {
        return slotId;
    }
    VehicleType Ticket::getVehicleType() {
        return vehicle;
    }