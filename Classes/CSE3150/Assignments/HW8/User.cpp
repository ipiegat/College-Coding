#include "Payment.h"
#include "RentalCart.h"
#include "User.h"
#include <memory>
#include <utility>

User::User(std::string id, std::string name, int loyaltyPoints, PaymentMethod* paymentMethod)
    : userID(std::move(id))
    , name(std::move(name))
    , loyaltyPoints(loyaltyPoints)
    , cart(new RentalCart())
    , paymentMethod(paymentMethod)
{}

double User::calculateRentalDiscount() {
    return 0.0;
}

RentalCart* User::getRentalCart() {
    return cart.get();
}

int User::getLoyaltyPoints() const {
    return loyaltyPoints;
}

double User::useLoyaltyPoints() {
    return calculateRentalDiscount();
}

void User::updateLoyaltyPoints(double total) {
    loyaltyPoints += static_cast<int>(total / 10);
}

double User::getDiscount() const {
    return discount;
}

StudentUser::StudentUser(std::string id, std::string name, int loyaltyPoints, PaymentMethod* paymentMethod)
    : User(std::move(id), std::move(name), loyaltyPoints, paymentMethod)
{}

double StudentUser::calculateRentalDiscount() {
    if (getLoyaltyPoints() >= 100) {
        updateLoyaltyPoints(-1000);
        return 0.15;
    }
    return 0.0;
}

FacultyUser::FacultyUser(std::string id, std::string name, int loyaltyPoints, PaymentMethod* paymentMethod)
    : User(std::move(id), std::move(name), loyaltyPoints, paymentMethod)
{}

double FacultyUser::calculateRentalDiscount() {
    if (getLoyaltyPoints() >= 100) {
        updateLoyaltyPoints(-1000);
        return 0.25;
    }
    return 0.0;
}
