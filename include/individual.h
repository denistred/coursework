#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "iperson.h"
#include <string>
#include <vector>
#include <stdexcept>

class Individual : public IPerson {
public:
    Individual() = default;

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

    // IFamilyNode - НЕ ПОДДЕРЖИВАЮТСЯ ДЛЯ ЛИСТА!
    void addChild(IPerson *child) override {
        throw std::logic_error("Cannot add children to an Individual");
    }

    void removeChild(const std::string& name) override {
        throw std::logic_error("Individuals don't have children to remove");
    }

    const std::vector<IPerson*>& getChildren() const override {
        static const std::vector<IPerson*> empty_children;
        return empty_children;
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
};

#endif // INDIVIDUAL_H