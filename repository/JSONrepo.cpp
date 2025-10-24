
#include "JSONrepo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QIODevice>
#include <QDebug>

#include "../domain/artwork.h"

JSONrepo::JSONrepo(std::string fileDB) : defaultRepo(std::move(fileDB)) {
}

void JSONrepo::readFile() {
    QFile file(QString::fromStdString(fileDB));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QByteArray rawData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(rawData);
    file.close();

    artworkDB.clear();
    QJsonArray array = doc.array();
    for (const auto& val : array) {
        QJsonObject obj = val.toObject();
        artworkDB.push_back(Artwork::fromJson(obj));
    }
}

void JSONrepo::writeToFile() const {
    QFile file(QString::fromStdString(fileDB));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;

    QJsonArray array;
    for (const auto& a : artworkDB) {
        array.append(a.toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();
}
