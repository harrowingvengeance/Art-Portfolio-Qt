//
// Created by Lea on 6/4/2025.
//

#ifndef CSVREPO_H
#define CSVREPO_H

#include "defaultRepo.h"
#include <fstream>

class CSVrepo final :  public defaultRepo{
public:
    explicit CSVrepo(std::string fileDB);

    void writeToFile() const override;
};



#endif //CSVREPO_H
