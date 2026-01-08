#include "Payment.h"
#include <stdexcept>

CreditCard::CreditCard(double initialBalance)
    : balance(initialBalance)
{}

bool CreditCard::processPayment(double amount) {
    if (balance - amount < -50.0)
        return false;
    balance -= amount;
    return true;
}

double CreditCard::getBalance() const {
    return balance;
}

PayPal::PayPal(double initialBalance)
    : balance(initialBalance)
{}

bool PayPal::processPayment(double amount) {
    if (balance < amount)
        return false;
    balance -= amount;
    return true;
}

double PayPal::getBalance() const {
    return balance;
}
