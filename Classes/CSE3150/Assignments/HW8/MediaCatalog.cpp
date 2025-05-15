#include "MediaCatalog.h"
#include <stdexcept>

// Media ctor + accessors
Media::Media(std::string title, double price)
  : title(std::move(title)), price(price) {}

std::string Media::getTitle() const {
  return title;
}

double Media::getPrice() const {
  return price;
}

//––– existing MediaCatalog method implementations follow –––


MediaCatalog& MediaCatalog::getInstance() {
    static MediaCatalog instance;
    return instance;
}

void MediaCatalog::addMedia(const std::string& title, std::shared_ptr<Media> media) {
    catalog[title] = std::move(media);
}

void MediaCatalog::removeMedia(const std::string& title) {
    auto erased = catalog.erase(title);
    if (erased == 0) {
        throw std::runtime_error("MediaCatalog::removeMedia: title not found");
    }
}

std::shared_ptr<Media> MediaCatalog::getMedia(const std::string& title) const {
    auto it = catalog.find(title);
    if (it == catalog.end()) {
        throw std::runtime_error("MediaCatalog::getMedia: title not found");
    }
    return it->second;
}

bool MediaCatalog::hasMedia(const std::string& title) const {
    return catalog.find(title) != catalog.end();
}
