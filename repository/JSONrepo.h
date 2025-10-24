
#ifndef JSONREPO_H
#define JSONREPO_H

#include "defaultRepo.h"
#include <QString>

class JSONrepo final : public defaultRepo {
public:
    explicit JSONrepo(std::string fileDB);
    void readFile() override;
    void writeToFile() const override;
};

#endif // JSONREPO_H
