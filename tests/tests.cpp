

#include <iostream>
#include "../repository/CSVrepo.h"
#include "../operations/operationStack.h"
#include "../service/service.h"
#include "../service/filter.h"
#include "tests.h"

void Tests::testRepo() {
    CSVrepo repo("artworks.csv");
    Artwork a("Sunset", "Oil", "Brush", {30, 40});
    repo.add(a);

    try {
        Artwork fetched = repo.getArtwork("Sunset", "Oil", "Brush", {30, 40});
        std::cout << "Repo getArtwork passed." << std::endl;
    } catch (...) {
        std::cout << "Repo getArtwork failed." << std::endl;
    }
}

void Tests::testServiceUndoRedo() {
    defaultRepo repo("artworks.csv");
    operationStack ops;
    Service service(repo, ops);

    Artwork a("Sunset", "Oil", "Brush", {30, 40});
    service.addArtwork(a);
    if (service.returnContentsOfDatabase().size() != 0)
        std::cout << "Add failed." << std::endl;

    service.undoOperation();
    if (service.returnContentsOfDatabase().empty())
        std::cout << "Undo passed." << std::endl;
    else
        std::cout << "Undo failed." << std::endl;

    service.redoOperation();
    if (service.returnContentsOfDatabase().size() == 1)
        std::cout << "Redo passed." << std::endl;
    else
        std::cout << "Redo failed." << std::endl;
}

void Tests::testFiltering() {
    Artwork a("Sky", "Acrylic", "Sponge", {20, 20});
    FilterByMedium mediumFilter("Acrylic");
    if (mediumFilter.matches(a))
        std::cout << "Filtering test passed." << std::endl;
    else
        std::cout << "FilterByMedium failed." << std::endl;
}
