//
// Created by Lea on 6/4/2025.
//

#include "../service/service.h"


Service::Service(repoInterface &repo, operationStack &operationStack) : repo(&repo), opStack(&operationStack){}

Service::~Service() {
    this->repo = nullptr;
}

void Service::addArtwork(const Artwork &newArtwork) {
    Operation* addOp = new AddOperation(newArtwork);
    this->repo->add(newArtwork);
    opStack->recordOperation(addOp);
}

void Service::removeArtwork(const Artwork &artworkToRemove) {
    Artwork removeArtwork = this->repo->getArtwork(artworkToRemove.getTitle());
    Operation* removeOp = new RemoveOperation(removeArtwork);
    this->repo->remove(artworkToRemove);
    opStack->recordOperation(removeOp);

}

void Service::updateArtwork(const Artwork& artwork, const Artwork &updatedArtwork) {
    Artwork oldArtwork = this->repo->getArtwork(artwork.getTitle());
    Operation* updateOp = new UpdateOperation(oldArtwork, updatedArtwork);
    this->repo->update(artwork, updatedArtwork);
    opStack->recordOperation(updateOp);
}

void Service::undoOperation() {
    Operation* undoOp = opStack->getUndoOperation();

    if (undoOp ->getOperationType() == "add")
        repo->remove(undoOp->getUndoParamater());

    else if (undoOp->getOperationType() == "remove")
        repo->add(undoOp->getUndoParamater());

    else if (undoOp ->getOperationType() == "update")
        repo->update(undoOp->getRedoParamater(), undoOp->getUndoParamater());

}

void Service::redoOperation() {
    Operation* redoOp = opStack->getRedoOperation();

    if (redoOp ->getOperationType() == "add")
        repo->add(redoOp->getRedoParamater());

    else if (redoOp->getOperationType() == "remove")
        repo->remove(redoOp->getRedoParamater());

    else if (redoOp ->getOperationType() == "update")
        repo->update(redoOp->getUndoParamater(), redoOp->getRedoParamater());

}

vector<Artwork> &Service::returnContentsOfDatabase() const {
    return this->repo->getArtworkDB();
}


std::vector<Artwork> Service::filter(const std::string& medium, const std::string& technique) const {
    std::vector<Artwork> filteredArtworks;
    for (const auto& artwork: this->repo->getArtworkDB()) {
        if ((!medium.empty() && artwork.getMedium() != medium) || (!technique.empty() && artwork.getTechnique() != technique))
            continue;
        filteredArtworks.push_back(artwork);
    }
    return filteredArtworks;
}
