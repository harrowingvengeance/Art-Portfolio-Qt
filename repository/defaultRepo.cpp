//
// Created by promp on 6/4/2025.
//

#include "defaultRepo.h"
#include <algorithm>
#include <fstream>
#include "../exceptions/exception.h"
void defaultRepo::readFile() {
    std::ifstream inputFile(this->fileDB);
    if (!inputFile.is_open()) {
        throw DBException("Could not open file for reading");
    }
    Artwork lineArtwork;

    while (inputFile >> lineArtwork) {
        this->artworkDB.push_back(lineArtwork);
    }
}

void defaultRepo::writeToFile() const {
    std::ofstream outputFile(this->fileDB);
    if (!outputFile.is_open()) {
        throw DBException("Could not open file for writing");
    }
    for (const auto &artwork: this->artworkDB) {
        outputFile << artwork;
    }
}

defaultRepo::defaultRepo(string fileDB) : fileDB(std::move(fileDB)){}
void defaultRepo::add(const Artwork &a) {
    this->artworkDB.push_back(a);
    writeToFile();
}

void defaultRepo::remove(const Artwork &artwork) {
    const auto it = std::find(artworkDB.begin(), artworkDB.end(),artwork);
    artworkDB.erase(it);
    writeToFile();
}

void defaultRepo::update(const Artwork& artwork, const Artwork &updatedArtwork) {

    for (auto &iterArtwork: this->artworkDB) {
        if (iterArtwork.getTitle() == updatedArtwork.getTitle()){
            iterArtwork = updatedArtwork;
            writeToFile();
            return;
        }
    }

}


Artwork defaultRepo::getArtwork(const string &title, const string &medium, const string &technique, const aDimension &dimension) {
    const auto searchResult = std::find(artworkDB.begin(), artworkDB.end(), Artwork{title, medium, technique, dimension});
    if (searchResult == artworkDB.end())
        throw ArtworkNotFoundException("Could not find artwork to remove/update!");
    return *searchResult;

}

vector<Artwork> &defaultRepo::getArtworkDB() {
    return artworkDB;
}

