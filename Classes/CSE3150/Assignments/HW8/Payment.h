#ifndef PAYMENT_H
#define PAYMENT_H

class PaymentMethod {
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~PaymentMethod() = default;
    virtual double getBalance() const = 0;
};

class CreditCard : public PaymentMethod {
public:
    // TODO: add methods
    CreditCard(double initialBalance);
    bool processPayment(double amount) override;
    double getBalance() const override;

private:
    // TODO: add private members
    double balance;
};

class PayPal : public PaymentMethod {
public:
    // TODO: add methods
    PayPal(double initialBalance);
    bool processPayment(double amount) override;
    double getBalance() const override;

private:
    // TODO: add private members
    double balance;
};

#endif
