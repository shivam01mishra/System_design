#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H
class PaymentMethod {
    public:
    virtual void pay(int amount)=0;
};
#endif