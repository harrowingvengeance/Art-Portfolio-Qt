
#include "filter.h"

bool FilterByMedium::matches(const Artwork& artwork) const {
    return artwork.getMedium() == medium;
}

bool FilterByTechnique::matches(const Artwork& artwork) const {
    return artwork.getTechnique() == technique;
}

