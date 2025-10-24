//
// Created by promp on 5/29/2025.
//

#include "../domain/artwork.h"
#include "../exceptions/exception.h"
#include <sstream>
#include <vector>
#include <fstream>
using std::string;
using std::vector;
using std::stringstream;

Artwork::Artwork() {
    this->title = "";
    this->medium = "";
    this->technique = "";
    this->dimension = {0,0};
}

Artwork::Artwork(string title, string medium, string technique, const aDimension &dimension) {
    this->title = std::move(title);
    this->medium = std::move(medium);
    this->technique = std::move (technique);
    this->dimension = dimension;
}

Artwork::Artwork(const Artwork &copy) {
    this->title = copy.title;
    this->medium = copy.medium;
    this->technique = copy.technique;
    this->dimension = copy.dimension;
}

Artwork &Artwork::operator=(const Artwork &copy) {
    if (this==&copy) return *this;
    this->title = copy.title;
    this->medium = copy.medium;
    this->technique = copy.technique;
    this->dimension = copy.dimension;
    return *this;
}

Artwork::~Artwork() = default;

string Artwork::getTitle() const{
    return title;
}

string Artwork::getMedium() const{
    return medium;
}

string Artwork::getTechnique() const{
    return technique;
}

aDimension Artwork::getDimension() const{
    return dimension;
}

void Artwork::setTitle(string title) {
    this->title = std::move(title);
}

void Artwork::setMedium(string medium){
    this->medium = std::move(medium);
}

void Artwork::setTechnique(string technique){
    this->technique = std::move(technique);
}

void Artwork::setDimension(const aDimension &dimension){
    this->dimension = dimension;
}

string Artwork::toString() const{
    std::stringstream representation;
    representation << this->getTitle() << " - ";
    representation << this->getMedium() << " - ";
    representation << this->getTechnique() << " - ";
    representation << this->getDimension().first <<"x";
    representation << this->getDimension().second;
    return representation.str();
}

bool Artwork::operator==(const Artwork &a) const{
    if(a.title == title && a.medium == medium && a.technique == technique
       && a.dimension.first == dimension.first && a.dimension.second == dimension.second)
        return true;
    return false;
}

std::istream &operator>>(std::istream &inputStream, Artwork &inputArtwork){
    string line;
    getline(inputStream, line);
    if (line.empty())
        return inputStream;

    std:stringstream ss(line);
    string newTitle, newMedium, newTechnique, newDimensionWidth, newDimensionHeight;
    getline(ss, newTitle,',');
    getline(ss, newMedium, ',');
    getline(ss, newTechnique, ',');
    getline(ss, newDimensionWidth,'x');
    getline(ss, newDimensionHeight, '\n');
    aDimension newDimension;
    newDimension.first = std::stoi(newDimensionWidth);
    newDimension.second = std::stoi(newDimensionHeight);

    inputArtwork.title = newTitle;
    inputArtwork.medium = newMedium;
    inputArtwork.technique = newTechnique;
    inputArtwork.dimension = newDimension;

    return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const Artwork &outputArtwork){
    outputStream << outputArtwork.getTitle() << ','
                 << outputArtwork.getMedium() << ','
                 << outputArtwork.getTechnique() << ','
                 << outputArtwork.getDimension().first << 'x' << outputArtwork.getDimension().second << '\n';
    return outputStream;
}

QJsonObject Artwork::toJson() const {
    QJsonObject obj;
    obj["title"] = QString::fromStdString(title);
    obj["medium"] = QString::fromStdString(medium);
    obj["technique"] = QString::fromStdString(technique);
    obj["width"] = dimension.first;
    obj["height"] = dimension.second;
    return obj;
}

Artwork Artwork::fromJson(const QJsonObject& obj) {
    std::string title = obj["title"].toString().toStdString();
    std::string medium = obj["medium"].toString().toStdString();
    std::string technique = obj["technique"].toString().toStdString();
    int width = obj["width"].toInt(-1);
    int height = obj["height"].toInt(-1);
    if (width < 0 || height < 0) {
        throw ArtworkValidationException("Invalid or missing dimensions!");
    }
    return Artwork(title, medium, technique, std::make_pair(width, height));
}
