#include "VehicleType.h"
#include <set>

class SlotManager{
VehicleType vehicleType;
std::set<int>freeSlots,occupySlots;
public:
SlotManager(VehicleType vehicleType, int n);
    bool hasFreeSlot();
    int park();
    void  freeSlot(int slotid);

};