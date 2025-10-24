
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>


class ArtworkValidationException : public std::exception {
    std::string message;
public:
    ArtworkValidationException(std::string _msg);
    const char* what() const noexcept override;
};

class InvalidDimensionException : public std::exception {
    std::string message;
public:
    InvalidDimensionException(std:: string _msg);
    const char* what() const noexcept override;
};
class ArtworkWithSameAttributesException : public std::exception {
    std::string message;
public:
    ArtworkWithSameAttributesException(std::string _msg);
    const char* what() const noexcept override;
};

class ArtworkNotFoundException: public std::exception {
    std::string message;
public:
    ArtworkNotFoundException(std::string _msg);
    const char* what() const noexcept override;
};

class UndoRedoException : public std::exception {
    std::string message;
public:
    UndoRedoException(std::string _msg);
    const char* what() const noexcept override;
};
#endif // EXCEPTION_H

