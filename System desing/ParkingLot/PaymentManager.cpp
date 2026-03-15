#include"PaymentManager.h"
 #include<iostream>
   int PaymentManager::getParkingCharg(std::shared_ptr<Ticket> ticket){
        int perMinutCharg;
        switch (ticket->getVehicleType()) {
            case VehicleType::TwoWheeler:
                    perMinutCharg=2;
                break;
            case VehicleType::FourWheeler:
                perMinutCharg=4;
            default:
                perMinutCharg=4;
                break;
        }
        int currentTime=1000;
        return (currentTime-ticket->getEntryTime())*perMinutCharg;
    }

     void PaymentManager::pay(std::shared_ptr<PaymentMethod> paymentMethod,int amount){
        paymentMethod->pay(amount);
        std::cout<<"Thanks for visite"<<std::endl;
    }