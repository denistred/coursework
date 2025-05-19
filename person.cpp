#include "person.h"

Person::Person(QObject *parent) : QObject(parent), gender(Male)
{
}

QString Person::getName() const {
    return this->name;
}

void Person::setName(const QString &name) {
    this->name = name;
}

Person::Gender Person::getGender() const {
    return this->gender;
}

void Person::setGender(const Gender &gender) {
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

