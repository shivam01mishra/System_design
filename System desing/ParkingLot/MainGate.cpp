#include<memory>
#include"ParkingLot.h"
#include"PaymentManager.h"
#include"VehicleType.h"
#include<iostream>
#include"UpiMode.h"
#include"CreditCard.h"
using namespace std;
int main(){
        std::shared_ptr<ParkingLot>parkingLot=std::make_shared<ParkingLot>();
        std::shared_ptr<PaymentManager>paymentManager=std::make_shared<PaymentManager>();


        
        parkingLot->addVehicleParking(VehicleType::FourWheeler,10);
        parkingLot->addVehicleParking(VehicleType::TwoWheeler,10);

        parkingLot->pakrVehile(VehicleType::cycle);

        
        std::shared_ptr<Ticket> ticket1=parkingLot->pakrVehile(VehicleType::TwoWheeler);
        int amount1=paymentManager->getParkingCharg(ticket1);
        paymentManager->pay(std::make_shared<CreditCard>(), amount1);
        parkingLot->unpark(ticket1);

        std::shared_ptr<Ticket> ticket2=parkingLot->pakrVehile(VehicleType::FourWheeler);
        int amount2=paymentManager->getParkingCharg(ticket2);
        paymentManager->pay(std::make_shared<UpiMode>(), amount2);
        parkingLot->unpark(ticket2);
        return 0;
    }