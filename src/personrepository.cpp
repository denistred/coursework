#include "personrepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

PersonRepository::PersonRepository(AbstractItemFactory* factory) : factory(factory) {}

QList<Person*> PersonRepository::load(const QString &filename) {
    QList<Person*> persons;
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

        Person* person = factory->createPersonWithId(id);
        person->setName(obj["name"].toString());
        person->setGender(obj["gender"].toString());
        person->setBirthday(QDate::fromString(obj["birthday"].toString(), Qt::ISODate));
        person->setPlaceOfBirth(obj["placeOfBirth"].toString());
        person->setProfession(obj["profession"].toString());
        person->setPhotoPath(obj["photoPath"].toString());
        person->setPosition(QPointF(obj["x"].toDouble(), obj["y"].toDouble()));

        QJsonArray relArray = obj["relations"].toArray();
        for (const QJsonValue &v : relArray) {
            person->addRelation(v.toInt());
        }

        persons.append(person);
    }

    return persons;
}

void PersonRepository::save(const QString &filename, const QList<Person*> &persons) {
    QJsonArray array;
    for (const Person* p : persons) {
        QJsonObject obj;
        obj["id"] = p->getId();
        obj["name"] = p->getName();
        obj["gender"] = p->getGender();
        obj["birthday"] = p->getBirthday().toString(Qt::ISODate);
        obj["placeOfBirth"] = p->getPlaceOfBirth();
        obj["profession"] = p->getProfession();
        obj["photoPath"] = p->getPhotoPath();
        obj["x"] = p->getPosition().x();
        obj["y"] = p->getPosition().y();

        QJsonArray relArray;
        for (int id : p->getRelations()) {
            relArray.append(id);
        }
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
