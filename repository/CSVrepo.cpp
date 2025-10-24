//
// Created by Lea on 6/4/2025.
//

#include "CSVrepo.h"
#include "../exceptions/exception.h"
CSVrepo::CSVrepo(std::string fileCSV) : defaultRepo((std::move(fileCSV))) {}


void CSVrepo::writeToFile() const {
    std::ofstream outputFile(this->fileDB);
    for (const auto &artwork: this->artworkDB) {
        outputFile << artwork;
    }
}

