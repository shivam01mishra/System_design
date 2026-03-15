#include "SlotManager.h"
#include<iostream>
SlotManager::SlotManager(VehicleType vehicleType, int n){
    this->vehicleType=vehicleType;
    for(int i=0;i<n;i++){
        freeSlots.insert(i);
    }
    
};

bool SlotManager::hasFreeSlot(){
        return freeSlots.size()>0;
    }

int SlotManager::park(){
        int slotId=*freeSlots.begin();
        freeSlots.erase(slotId);
        occupySlots.insert(slotId);
        std::cout<<"you may park you vahicle at slot number "<<slotId<<std::endl;
        return slotId;
}
void  SlotManager::freeSlot(int slotid){
    occupySlots.erase(slotid);
    freeSlots.insert(slotid);
}