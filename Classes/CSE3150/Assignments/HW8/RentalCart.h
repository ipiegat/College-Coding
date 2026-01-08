#ifndef RENTALCART_H
#define RENTALCART_H

#include <vector>
#include <memory>
#include "MediaCatalog.h"

class User;

class RentalCart {
public:
    void addMedia(std::shared_ptr<Media> media);
    void clearCart();
    double calculateTotal(const User* user) const;

private:
    std::vector<std::shared_ptr<Media>> items;
};

#endif
