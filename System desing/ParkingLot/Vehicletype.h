#ifndef VEHICLE_TYPE_H
#define VEHICLE_TYPE_H
#include<string>
enum class VehicleType{
    cycle,
    TwoWheeler,
    FourWheeler
};
std::string toString(VehicleType v);
#endif