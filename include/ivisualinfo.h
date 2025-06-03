#ifndef IVISUALINFO_H
#define IVISUALINFO_H
#include <string>

class IVisualInfo {
public:
    virtual ~IVisualInfo() = default;

    virtual const std::string& getPhotoPath() const = 0;
    virtual void setPhotoPath(const std::string& photoPath) = 0;

    virtual std::pair<double, double> getPosition() const = 0;
    virtual void setPosition(double x, double y) = 0;
};

#endif //IVISUALINFO_H
