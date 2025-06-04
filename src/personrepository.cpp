#include "personrepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

PersonRepository::PersonRepository(AbstractItemFactory* factory) : factory(factory) {}

QList<IPerson*> PersonRepository::load(const QString &filename) {
    QList<IPerson*> persons;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return persons;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) return persons;

    QJsonArray array = doc.array();
    for (const QJsonValue &val : array) {
        QJsonObject obj = val.toObject();
        int id = obj["id"].toInt();
        if (id > maxId) maxId = id;

        IPerson* person = factory->createPersonWithId(id);
        person->setName(obj["name"].toString().toStdString());
        person->setGender(obj["gender"].toString().toStdString());
        //person->setBirthday(QDate::fromString(obj["birthday"].toString(), Qt::ISODate));
        QString qstr = obj["birthday"].toString();
        std::string dateStr = qstr.toStdString();
        std::tm tm{};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        person->setBirthday(tm);
        person->setPlaceOfBirth(obj["placeOfBirth"].toString().toStdString());
        person->setProfession(obj["profession"].toString().toStdString());
        person->setPhotoPath(obj["photoPath"].toString().toStdString());
        person->setPosition(obj["x"].toDouble(), obj["y"].toDouble());

        QJsonArray relArray = obj["relations"].toArray();
        for (const QJsonValue &v : relArray) {
            //person->addRelation(v.toInt());
        }

        persons.append(person);
    }

    return persons;
}

void PersonRepository::save(const QString &filename, const QList<IPerson*> &persons) {
    QJsonArray array;
    for (const IPerson* p : persons) {
        QJsonObject obj;
        obj["id"] = p->getId();
        obj["name"] = QString::fromStdString(p->getName());
        obj["gender"] = QString::fromStdString(p->getGender());
        //obj["birthday"] = p->getBirthday().toString(Qt::ISODate);
        std::tm tm = p->getBirthday();
        char buffer[11]; // "YYYY-MM-DD" + null
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
        obj["birthday"] = QString::fromUtf8(buffer);
        obj["placeOfBirth"] = QString::fromStdString(p->getPlaceOfBirth());
        obj["profession"] = QString::fromStdString(p->getProfession());
        obj["photoPath"] = QString::fromStdString(p->getPhotoPath());
        obj["x"] = p->getPosition().first;
        obj["y"] = p->getPosition().second;

        QJsonArray relArray;
        // for (int id : p->getRelations()) {
        //     relArray.append(id);
        // }
        obj["relations"] = relArray;
        array.append(obj);
    }

    QJsonDocument doc(array);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}
