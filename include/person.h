#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <chrono>
#include <utility>

class Person {
public:
    Person() = default;

    int getId() const;
    void setId(int id);

    const std::string& getName() const;
    void setName(const std::string& name);

    const std::string& getGender() const;
    void setGender(const std::string& gender);

    const std::tm& getBirthday() const;
    void setBirthday(const std::tm& birthday);

    const std::string& getPlaceOfBirth() const;
    void setPlaceOfBirth(const std::string& placeOfBirth);

    const std::string& getProfession() const;
    void setProfession(const std::string& profession);

    const std::string& getPhotoPath() const;
    void setPhotoPath(const std::string& photoPath);

    const std::vector<int>& getRelations() const;
    void addRelation(int id);
    void removeRelation(int id);
    void setRelations(const std::vector<int>& relations);

    std::pair<double, double> getPosition() const;
    void setPosition(double x, double y);

private:
    int id = -1;
    std::string name;
    std::string gender;
    std::tm birthday{};
    std::string placeOfBirth;
    std::string profession;
    std::string photoPath;
    std::vector<int> relations;
    std::pair<double, double> position = {0.0, 0.0}; // x, y
};

#endif // PERSON_H