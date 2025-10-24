//
// Created by promp on 6/3/2025.
//

#ifndef REPOINTERFACE_H
#define REPOINTERFACE_H
#include "../domain/artwork.h"
#include <vector>
#include <exception>

using std::exception;
class DBException final : public exception {
        const char *s;
public:
        const char *what() const noexcept override {
                return s;
        }

        explicit DBException(const char *s): s(s) { ; }
};


class repoInterface {
public:
        virtual void add(const Artwork& artwork) = 0;
        virtual void remove(const Artwork& artwork) = 0;
        virtual void update(const Artwork& artwork, const Artwork &updatedArtwork) = 0;
        virtual Artwork getArtwork(const string &title, const string &medium, const string &technique, const aDimension &dimension) = 0;
        virtual std::vector<Artwork>& getArtworkDB() = 0;
        virtual void readFile() = 0;
        virtual void writeToFile() const = 0;
        virtual ~repoInterface() = default;
};

#endif //REPOINTERFACE_H
