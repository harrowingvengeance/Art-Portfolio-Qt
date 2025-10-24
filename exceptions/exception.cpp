//
// Created by Lea on 6/5/2025.
//

#include "exception.h"



InvalidDimensionException::InvalidDimensionException(std::string _msg) : message{std::move(_msg)} {}

const char * InvalidDimensionException::what() const noexcept {
    return message.c_str();
}

ArtworkValidationException::ArtworkValidationException(std::string _msg) : message{std::move(_msg)} {}

const char * ArtworkValidationException::what() const noexcept {
    return message.c_str();
}

ArtworkWithSameAttributesException::ArtworkWithSameAttributesException(std::string _msg) : message{std::move(_msg)} {}

const char * ArtworkWithSameAttributesException::what() const noexcept {
    return message.c_str();
}

ArtworkNotFoundException::ArtworkNotFoundException(std::string _msg) : message{std::move(_msg)} {}

const char * ArtworkNotFoundException::what() const noexcept {
    return message.c_str();
}

UndoRedoException::UndoRedoException(std::string _msg) : message{std::move(_msg)} {}

const char * UndoRedoException::what() const noexcept {
    return message.c_str();
}