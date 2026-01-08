#include "RentalCart.h"
#include "User.h"
#include "Payment.h"

void RentalCart::addMedia(std::shared_ptr<Media> media) {
    items.push_back(std::move(media));
}

void RentalCart::clearCart() {
    items.clear();
}

double RentalCart::calculateTotal(const User* user) const {
    double sum = 0;
    for (const auto& m : items) {
        sum += m->getPrice();
    }
    auto usr = const_cast<User*>(user);
    double discount = usr->useLoyaltyPoints();
    double total = sum * (1 - discount);

    auto pm = usr->getPaymentMethod();
    bool canPay = false;
    if (auto cc = dynamic_cast<CreditCard*>(pm)) {
        if (cc->getBalance() - total >= -50.0) {
            canPay = true;
        }
    } else if (auto pp = dynamic_cast<PayPal*>(pm)) {
        if (pp->getBalance() - total >= 0.0) {
            canPay = true;
        }
    }
    if (canPay) {
        usr->updateLoyaltyPoints(total);
    }
    return total;
}
