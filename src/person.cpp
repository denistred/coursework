#include "person.h"
#include <algorithm>

int Person::getId() const {
    return id;
}

void Person::setId(int newId) {
    id = newId;
}

const std::string& Person::getName() const {
    return name;
}

void Person::setName(const std::string& newName) {
    name = newName;
}

const std::string& Person::getGender() const {
    return gender;
}

void Person::setGender(const std::string& newGender) {
    gender = newGender;
}

const std::tm& Person::getBirthday() const {
    return birthday;
}

void Person::setBirthday(const std::tm& newBirthday) {
    birthday = newBirthday;
}

const std::string& Person::getPlaceOfBirth() const {
    return placeOfBirth;
}

void Person::setPlaceOfBirth(const std::string& newPlaceOfBirth) {
    placeOfBirth = newPlaceOfBirth;
}

const std::string& Person::getProfession() const {
    return profession;
}

void Person::setProfession(const std::string& newProfession) {
    profession = newProfession;
}

const std::string& Person::getPhotoPath() const {
    return photoPath;
}

void Person::setPhotoPath(const std::string& newPhotoPath) {
    photoPath = newPhotoPath;
}

const std::vector<int>& Person::getRelations() const {
    return relations;
}

void Person::addRelation(int relId) {
    if (std::find(relations.begin(), relations.end(), relId) == relations.end()) {
        relations.push_back(relId);
    }
}

void Person::removeRelation(int relId) {
    relations.erase(std::remove(relations.begin(), relations.end(), relId), relations.end());
}

void Person::setRelations(const std::vector<int>& newRelations) {
    relations = newRelations;
}

std::pair<double, double> Person::getPosition() const {
    return position;
}

void Person::setPosition(double x, double y) {
    position = {x, y};
}
