#ifndef TICKET_H
#define TICKET_H
 #include"VehicleType.h"

 class Ticket{
    int slotId;
    VehicleType vehicle ;
    int entryTime;
    public:
    Ticket(int slotId,VehicleType vehicle , int entryTime);
   int getEntryTime();
    int getSlotId();
    VehicleType getVehicleType();
};
#endif