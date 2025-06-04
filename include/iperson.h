#ifndef IPERSON_H
#define IPERSON_H

#include <chrono>

class IPerson {
public:
    ~IPerson()= default;
    virtual int getId() const = 0;
    virtual void setId(int id) = 0;

    virtual const std::string& getName() const = 0;
    virtual void setName(const std::string& name) = 0;

    virtual const std::string& getGender() const = 0;
    virtual void setGender(const std::string& gender) = 0;

    virtual const std::tm& getBirthday() const = 0;
    virtual void setBirthday(const std::tm& birthday) = 0;

    virtual const std::string& getPlaceOfBirth() const = 0;
    virtual void setPlaceOfBirth(const std::string& placeOfBirth) = 0;

    virtual const std::string& getProfession() const = 0;
    virtual void setProfession(const std::string& profession) = 0;

    virtual bool isAlive() const = 0;
    virtual void setDead() = 0;

    virtual const std::string& getPhotoPath() const = 0;
    virtual void setPhotoPath(const std::string& photoPath) = 0;

    virtual std::pair<double, double> getPosition() const = 0;
    virtual void setPosition(double x, double y) = 0;

    virtual void addChild(IPerson* child) = 0;
    virtual void removeChild(const std::string& name) = 0;
    virtual const std::vector<IPerson*>& getChildren() const = 0;
};

#endif //IPERSON_H
