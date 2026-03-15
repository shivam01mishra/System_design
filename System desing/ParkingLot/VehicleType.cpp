#include"Vehicletype.h"
std::string toString(VehicleType v)
{
    switch(v)
    {
        case VehicleType::cycle: return "cycle";
        case VehicleType::TwoWheeler: return "TwoWheeler";
        case VehicleType::FourWheeler: return "FourWheeler";
    }

    return "UNKNOWN";
}