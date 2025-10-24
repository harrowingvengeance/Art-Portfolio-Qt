//
// Created by promp on 5/29/2025.
//

#ifndef ARTWORK_H
#define ARTWORK_H

#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QIODevice>
#include <QDebug>
typedef std::pair<int, int> aDimension;

using std::string;

class Artwork {
protected:
    string title;
    string medium;
    string technique;
    aDimension dimension;
public:
    Artwork();
    explicit Artwork(string name, string type, string medium, const aDimension &dimension);

    ~Artwork();
    Artwork(const Artwork& copy);
    Artwork &operator=(const Artwork& copy);

    string getTitle() const;
    string getMedium() const;
    string getTechnique() const;
    aDimension getDimension() const;

    void setTitle(string title);
    void setMedium(string medium);
    void setTechnique(string technique);
    void setDimension (const aDimension &dimension);

    string toString() const;

    friend std::istream &operator>>(std::istream &inputStream, Artwork &inputArtwork);
    friend std::ostream &operator<<(std::ostream &outputStream, const Artwork &outputArtwork);

    bool operator==(const Artwork &a) const;

    QJsonObject toJson() const;
    static Artwork fromJson(const QJsonObject& obj);

};

#endif //ARTWORK_H
