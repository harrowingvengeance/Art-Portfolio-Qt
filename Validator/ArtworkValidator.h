//
// Created by Lea on 6/5/2025.
//

#ifndef ARTWORKVALIDATOR_H
#define ARTWORKVALIDATOR_H
#include <vector>
#include <string>

using std::vector, std::string;

class ArtworkValidator {
public:

    static void validateDataPoints(const vector <string>& inputDataPoints);

    static void validateDimension(const vector <string>& inputDimension);

};



#endif //ARTWORKVALIDATOR_H
