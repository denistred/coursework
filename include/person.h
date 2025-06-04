#ifndef PERSON_H
#define PERSON_H

#include "iperson.h"

#include <string>
#include <vector>
#include <chrono>
#include <utility>
#include <algorithm>

class Person : public IPerson {
public:
    Person() = default;

    // IBasicInfo
    int getId() const override { return id; }
    void setId(int id_) override { id = id_; }

    const std::string& getName() const override { return name; }
    void setName(const std::string& name_) override { name = name_; }

    const std::string& getGender() const override { return gender; }
    void setGender(const std::string& gender_) override { gender = gender_; }

    const std::tm& getBirthday() const override { return birthday; }
    void setBirthday(const std::tm& birthday_) override { birthday = birthday_; }

    const std::string& getPlaceOfBirth() const override { return placeOfBirth; }
    void setPlaceOfBirth(const std::string& place_) override { placeOfBirth = place_; }

    const std::string& getProfession() const override { return profession; }
    void setProfession(const std::string& profession_) override { profession = profession_; }

    const std::string& getPhotoPath() const override { return photoPath; }
    void setPhotoPath(const std::string& path) override { photoPath = path; }

    // IVisualInfo
    std::pair<double, double> getPosition() const override { return position; }
    void setPosition(double x, double y) override { position = {x, y}; }

    // ILifecycle
    bool isAlive() const override { return alive; }
    void setDead() override { alive = false; }

    // IFamilyNode
    void addChild(IPerson *child) override {
        if (!alive) return;
        children.push_back(child);
    }

    void removeChild(const std::string& name) override {
        children.erase(std::remove_if(children.begin(), children.end(),
            [&](IPerson*& p) {
                return p->getName() == name;
            }),
            children.end());
    }

    const std::vector<IPerson*>& getChildren() const override {
        return children;
    }

private:
    int id = -1;
    std::string name;
    std::string gender;
    std::tm birthday{};
    std::string placeOfBirth;
    std::string profession;
    std::string photoPath;
    std::pair<double, double> position = {0.0, 0.0};

    bool alive = true;
    std::vector<IPerson*> children;
};

#endif // PERSON_H