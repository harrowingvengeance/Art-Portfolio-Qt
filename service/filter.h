
#ifndef FILTER_H
#define FILTER_H

#include "../domain/artwork.h"
#include <vector>
#include <memory>

class Filter {
public:
    virtual ~Filter() = default;
    virtual bool matches(const Artwork& artwork) const = 0;
};

class FilterByMedium : public Filter {
private:
    std::string medium;
public:
    explicit FilterByMedium(std::string medium) : medium(std::move(medium)) {}
    bool matches(const Artwork& artwork) const override;
};

class FilterByTechnique : public Filter {
private:
    std::string technique;
public:
    explicit FilterByTechnique(std::string technique) : technique(std::move(technique)) {}
    bool matches(const Artwork& artwork) const override;
};


#endif // FILTER_H
