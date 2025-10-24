//
// Created by promp on 6/4/2025.
//

#ifndef DEFAULTREPO_H
#define DEFAULTREPO_H

#include "repoInterface.h"

using std::vector;

class defaultRepo : public repoInterface{
protected:
    vector<Artwork> artworkDB;
    string fileDB;
public:
    defaultRepo(string fileDB);

    void add(const Artwork &a) override;

    void remove(const Artwork &artwork) override;

    void update(const Artwork& artwork, const Artwork &updatedArtwork) override;

    Artwork getArtwork(const string &title, const string &medium, const string &technique, const aDimension &dimension) override;

    vector<Artwork>& getArtworkDB() override;

    void readFile() override;
    void writeToFile() const override;

    ~defaultRepo() override = default;
};



#endif //DEFAULTREPO_H
