#ifndef FAMILY_H
#define FAMILY_H

#include "iperson.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class Family : public IPerson {
public:
    Family() = default;

    int getId() const override { return id; }
    void setId(int id_) override { id = id_; }

    const std::string& getName() const override { return familyName; }
    void setName(const std::string& name_) override { familyName = name_; }

    const std::string& getGender() const override {
        throw std::logic_error("Family doesn't have gender");
    }
    void setGender(const std::string&) override {
        throw std::logic_error("Cannot set gender for Family");
    }
    const std::tm& getBirthday() const override {
        throw std::logic_error("Family doesn't have birthday");
    }
    void setBirthday(const std::tm&) override {
        throw std::logic_error("Cannot set birthday for Family");
    }
    const std::string& getPlaceOfBirth() const override {
        throw std::logic_error("Family doesn't have place of birth");
    }
    void setPlaceOfBirth(const std::string&) override {
        throw std::logic_error("Cannot set place of birth for Family");
    }
    const std::string& getProfession() const override {
        throw std::logic_error("Family doesn't have profession");
    }
    void setProfession(const std::string&) override {
        throw std::logic_error("Cannot set profession for Family");
    }
    const std::string& getPhotoPath() const override {
        throw std::logic_error("Family doesn't have photo");
    }
    void setPhotoPath(const std::string&) override {
        throw std::logic_error("Cannot set photo for Family");
    }


    std::pair<double, double> getPosition() const override { return position; }
    void setPosition(double x, double y) override { position = {x, y}; }

    bool isAlive() const override { return true; }
    void setDead() override {
        throw std::logic_error("Cannot 'kill' a Family");
    }

    void addChild(IPerson *child) override {
        children.push_back(child);
    }

    void removeChild(const std::string& name) override {
        children.erase(std::remove_if(children.begin(), children.end(),
            [&](IPerson* p) { return p->getName() == name; }),
            children.end());
    }

    const std::vector<IPerson*>& getChildren() const override {
        return children;
    }

private:
    int id = -1;
    std::string familyName;
    std::pair<double, double> position = {0.0, 0.0};
    std::vector<IPerson*> children;
};

#endif // FAMILY_H