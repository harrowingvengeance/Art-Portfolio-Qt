//
// Created by Lea on 6/4/2025.
//

#ifndef OPERATION_H
#define OPERATION_H

#include "../domain/artwork.h"
#include <string>
using std::string;

class Operation {
public:
    virtual ~Operation() = default;

    virtual string getOperationType()=0;
    virtual Artwork getRedoParamater() = 0;
    virtual Artwork getUndoParamater() = 0;
};

class AddOperation final : public Operation {
    Artwork artwork;
public:
    explicit AddOperation(Artwork artwork) : artwork(artwork) {}

    string getOperationType() override {return "add";}
    Artwork getRedoParamater() override {return artwork;}
    Artwork getUndoParamater() override {return artwork;}
};

class RemoveOperation final : public Operation {
    Artwork artwork;
public:
    explicit RemoveOperation(Artwork artwork) : artwork(artwork) {}

    string getOperationType() override {return "remove";}
    Artwork getRedoParamater() override {return artwork;}
    Artwork getUndoParamater() override {return artwork;}
};

class UpdateOperation final : public Operation {
    Artwork oldArtwork;
    Artwork newArtwork;
public:
    explicit UpdateOperation(Artwork oldArtwork, Artwork newArtwork) : oldArtwork(oldArtwork), newArtwork(newArtwork){}

    string getOperationType() override {return "update";}
    Artwork getRedoParamater() override {return newArtwork;}
    Artwork getUndoParamater() override {return oldArtwork;}
};
#endif //OPERATION_H