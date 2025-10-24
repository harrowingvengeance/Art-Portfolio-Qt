//
// Created by Lea on 6/4/2025.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "../repository/defaultRepo.h"
#include "../operations/operationStack.h"
#include "../domain/artwork.h"
#include "../service/filter.h"
#include <memory>
class Service {
private:
    repoInterface *repo;
    operationStack* opStack;
public:
    Service(repoInterface& repo, operationStack& operationStack);
    ~Service();
    void addArtwork(const Artwork& newArtwork);
    void removeArtwork(const Artwork& artworkToRemove);
    void updateArtwork(const Artwork& artwork, const Artwork& updatedArtwork);
    void undoOperation();
    void redoOperation();
    vector<Artwork>& returnContentsOfDatabase() const;
    std::vector<Artwork> filter(const std::vector<std::shared_ptr<Filter>>& filters) const;

};



#endif //SERVICE_H
