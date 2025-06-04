#include "personrepository.h"
#include "family.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <QDebug>
#include <algorithm>

PersonRepository::~PersonRepository() {
    clear();
}

PersonRepository& PersonRepository::instance() {
    static PersonRepository instance;
    return instance;
}

void PersonRepository::addPerson(IPerson* person) {
    if (!person) return;

    if (person->getId() == -1) {
        person->setId(nextId++);
    }

    auto it = std::find(persons.begin(), persons.end(), person);
    if (it == persons.end()) {
        persons.push_back(person);
        emit personAdded(person);
        emit dataChanged();
    }
}

void PersonRepository::removePerson(int id) {
    auto it = std::remove_if(persons.begin(), persons.end(),
        [id](IPerson* p) { return p->getId() == id; });

    if (it != persons.end()) {
        IPerson* person = *it;
        persons.erase(it, persons.end());
        delete person;
        emit personRemoved(id);
        emit dataChanged();
    }
}

IPerson* PersonRepository::getPersonById(int id) const {
    auto it = std::find_if(persons.begin(), persons.end(),
        [id](IPerson* p) { return p->getId() == id; });

    return (it != persons.end()) ? *it : nullptr;
}

const std::vector<IPerson*>& PersonRepository::getAllPersons() const {
    return persons;
}

void PersonRepository::clear() {
    for (IPerson* person : persons) {
        delete person;
    }
    persons.clear();
    nextId = 1;
    pendingRelations.clear();
    emit dataChanged();
}

void PersonRepository::setFactory(PersonFactory* factory) {
    this->factory = factory;
}

IPerson* PersonRepository::createIndividual() {
    if (!factory) {
        qCritical() << "Factory not set!";
        return nullptr;
    }

    IPerson* person = factory->createIndividual();
    person->setId(nextId++);
    addPerson(person);
    return person;
}

IPerson* PersonRepository::createFamily() {
    if (!factory) {
        qCritical() << "Factory not set!";
        return nullptr;
    }

    IPerson* family = factory->createFamily();
    family->setId(nextId++);
    addPerson(family);
    return family;
}

IPerson* PersonRepository::createIndividual(const std::string& name,
                                          const std::string& gender,
                                          const std::tm& birthday) {
    if (!factory) {
        qCritical() << "Factory not set!";
        return nullptr;
    }

    IPerson* person = factory->createIndividual(name, gender, birthday);
    person->setId(nextId++);
    addPerson(person);
    return person;
}

void PersonRepository::saveToFile(const QString& filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << filename;
        return;
    }

    QJsonDocument doc(saveToJsonArray());
    file.write(doc.toJson());
    file.close();
}

void PersonRepository::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << filename;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        qWarning() << "Invalid file format. Expected JSON array.";
        return;
    }

    clear();
    loadFromJsonArray(doc.array());
    emit dataChanged();
}

QJsonArray PersonRepository::saveToJsonArray() const {
    QJsonArray array;

    for (IPerson* person : persons) {
        QJsonObject obj;
        obj["id"] = person->getId();
        obj["name"] = QString::fromStdString(person->getName());
        obj["gender"] = QString::fromStdString(person->getGender());

        std::tm birth = person->getBirthday();
        std::ostringstream oss;
        oss << std::put_time(&birth, "%Y-%m-%d");
        obj["birthday"] = QString::fromStdString(oss.str());

        obj["placeOfBirth"] = QString::fromStdString(person->getPlaceOfBirth());
        obj["profession"] = QString::fromStdString(person->getProfession());
        obj["photoPath"] = QString::fromStdString(person->getPhotoPath());

        auto [x, y] = person->getPosition();
        obj["x"] = x;
        obj["y"] = y;

        QJsonArray childrenIds;
        for (IPerson* child : person->getChildren()) {
            childrenIds.append(child->getId());
        }
        obj["children"] = childrenIds;

        array.append(obj);
    }

    return array;
}

void PersonRepository::loadFromJsonArray(const QJsonArray& array) {
    if (!factory) {
        qCritical() << "Factory not set before loading!";
        return;
    }

    for (const QJsonValue& val : array) {
        QJsonObject obj = val.toObject();
        int id = obj["id"].toInt();

        if (id >= nextId) {
            nextId = id + 1;
        }

        IPerson* person = factory->createPersonWithId(id);
        if (!person) {
            qWarning() << "Failed to create person with ID:" << id;
            continue;
        }

        person->setName(obj["name"].toString().toStdString());
        person->setGender(obj["gender"].toString().toStdString());

        QString dateStr = obj["birthday"].toString();
        if (!dateStr.isEmpty()) {
            std::tm tm = {};
            std::istringstream ss(dateStr.toStdString());
            ss >> std::get_time(&tm, "%Y-%m-%d");
            if (!ss.fail()) {
                person->setBirthday(tm);
            }
        }

        person->setPlaceOfBirth(obj["placeOfBirth"].toString().toStdString());
        person->setProfession(obj["profession"].toString().toStdString());
        person->setPhotoPath(obj["photoPath"].toString().toStdString());

        if (obj.contains("x") && obj.contains("y")) {
            double x = obj["x"].toDouble();
            double y = obj["y"].toDouble();
            person->setPosition(x, y);
        }

        QJsonArray childrenIds = obj["children"].toArray();
        std::vector<int> childIds;
        for (const QJsonValue& childIdVal : childrenIds) {
            childIds.push_back(childIdVal.toInt());
        }
        pendingRelations[person] = childIds;

        persons.push_back(person);
    }

    for (auto& [person, childIds] : pendingRelations) {
        for (int childId : childIds) {
            IPerson* child = getPersonById(childId);
            if (child) {
                person->addChild(child);
            }
        }
    }

    pendingRelations.clear();
    emit dataChanged();
}

void PersonRepository::notifyPersonUpdated(IPerson* person) {
    emit personUpdated(person);
    emit dataChanged();
}