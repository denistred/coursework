#include "person.h"

Person::Person(QObject *parent) : QObject(parent)
{
}

QString Person::getName() const {
    return this->name;
}

void Person::setName(const QString &name) {
    this->name = name;
}

QString Person::getGender() const {
    return this->gender;
}

void Person::setGender(const QString &gender) {
    this->gender = gender;
}

QDate Person::getBirthday() const {
    return this->birthday;
}

void Person::setBirthday(const QDate &birthday) {
    this->birthday = birthday;
}

QString Person::getPlaceOfBirth() const {
    return this->placeOfBirth;
}

void Person::setPlaceOfBirth(const QString &placeOfBirth) {
    this->placeOfBirth = placeOfBirth;
}

QString Person::getProfession() const {
    return this->profession;
}

void Person::setProfession(const QString &profession) {
    this->profession = profession;
}
