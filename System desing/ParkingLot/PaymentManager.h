#include"Ticket.h"
#include"PaymentMethod.h"
#include<memory>
class PaymentManager {
    public:
    int getParkingCharg(std::shared_ptr<Ticket> ticket);
    void pay(std::shared_ptr<PaymentMethod>paymentMethod,int amount);

    
    
};