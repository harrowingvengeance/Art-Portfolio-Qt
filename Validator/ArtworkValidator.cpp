//
// Created by Lea on 6/5/2025.
//

#include "ArtworkValidator.h"

#include "../exceptions/exception.h"

void ArtworkValidator::validateDimension(const vector<string> &inputDimension) {
    string errors;
    //Checking width (characters are digits)
    try {
        int dimensionWidth = std::stoi(inputDimension[0]);
        if (dimensionWidth < 0)
            errors += string("The width must be a positive number or zero!\n");
    }catch (std::invalid_argument const& excep) {
        errors += string("The width must be a positive number or zero!\n");
    }catch (std::out_of_range const& excep){
        errors += string("The width is too large to store!\n");
    }

    try {
        int dimensionHeight = std::stoi(inputDimension[1]);
        if (dimensionHeight < 0)
            errors += string("The height must be a positive number or zero!\n");

    }catch (std::invalid_argument const& excep) {
        errors += string("The height must be a positive number or zero!\n");

    }catch (std::out_of_range const& excep){
        errors += string("The height is too large to store!\n");
    }

    if (!errors.empty())
        throw InvalidDimensionException(errors);
}

void ArtworkValidator::validateDataPoints(const vector<string> &inputDataPoints) {


    if (inputDataPoints.size() < 5)
        throw ArtworkValidationException("Not enough data points to construct a Tutorial entity!\n");

    string errors;
    // Checking whether any provided data point is empty
    int i = 0;
    for (const string& dataPoint : inputDataPoints) {
        if (dataPoint.empty()) {
            errors += string("The no.");
            errors += std::to_string(i+1);
            errors += string(" data point is empty!\n");
        }
        ++i;
    }

    // Checking width (characters are digits and the number is less than 0
    try {

        int dimensionWidth = std::stoi(inputDataPoints[3]);
        if (dimensionWidth < 0)
                errors += string("The width must be a positive number or zero!\n");

        } catch (std::invalid_argument const& excep) {
            errors += string("The width must be a positive number or zero!\n");
        } catch (std::out_of_range const& excep) {
        errors += string("The width is too large to store!\n");
    }

    // Checking height (characters are digits and the number is less than 0)
    try {

        int duration_seconds = std::stoi(inputDataPoints[4]);

    } catch (std::invalid_argument const& excep) {
        errors += string("The height must be a positive number or zero!\n");
    } catch (std::out_of_range const& excep) {
        errors += string("The height is too large to store!\n");
    }


    if (!errors.empty())
        throw ArtworkValidationException(errors);
}
