#include "person.h"

Person::Person(QObject *parent) : QObject(parent) {
}

int Person::getId() const {
    return id;
}

void Person::setId(int newId) {
    if (id != newId) {
        id = newId;
        emit dataChanged();
    }
}

QString Person::getName() const {
    return name;
}

void Person::setName(const QString &newName) {
    if (name != newName) {
        name = newName;
        emit dataChanged();
    }
}

QString Person::getGender() const {
    return gender;
}

void Person::setGender(const QString &newGender) {
    if (gender != newGender) {
        gender = newGender;
        emit dataChanged();
    }
}

QDate Person::getBirthday() const {
    return birthday;
}

void Person::setBirthday(const QDate &newBirthday) {
    if (birthday != newBirthday) {
        birthday = newBirthday;
        emit dataChanged();
    }
}

QString Person::getPlaceOfBirth() const {
    return placeOfBirth;
}

void Person::setPlaceOfBirth(const QString &newPlace) {
    if (placeOfBirth != newPlace) {
        placeOfBirth = newPlace;
        emit dataChanged();
    }
}

QString Person::getProfession() const {
    return profession;
}

void Person::setProfession(const QString &newProfession) {
    if (profession != newProfession) {
        profession = newProfession;
        emit dataChanged();
    }
}

QString Person::getPhotoPath() const {
    return photoPath;
}

void Person::setPhotoPath(const QString &newPath) {
    if (photoPath != newPath) {
        photoPath = newPath;
        emit dataChanged();
    }
}

QList<int> Person::getRelations() const {
    return relations;
}

void Person::addRelation(int id) {
    if (!relations.contains(id)) {
        relations.append(id);
        emit dataChanged();
    }
}

void Person::setRelations(const QList<int> &newRelations) {
    relations = newRelations;
    emit dataChanged();
}

void Person::removeRelation(int id) {
    relations.removeAll(id);
}

void Person::setPosition(const QPointF &pos) {
    position = pos;
}

QPointF Person::getPosition() const {
    return position;
}