#ifndef MEDIACATALOG_H
#define MEDIACATALOG_H

#include <string>
#include <map>
#include <memory>

class Media {
public:
    Media(std::string title, double price);
    virtual ~Media() = default;
    std::string getTitle() const;
    double getPrice() const;

private:
    std::string title;
    double price;
};

class MediaCatalog {
public:
    // TODO: add methods
    static MediaCatalog& getInstance();
    void addMedia(const std::string& title, std::shared_ptr<Media> media);
    void removeMedia(const std::string& title);
    std::shared_ptr<Media> getMedia(const std::string& title) const;
    bool hasMedia(const std::string& title) const;

private:
    // TODO: add private members
    std::map<std::string, std::shared_ptr<Media>> catalog;
};

#endif
