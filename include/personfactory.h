#ifndef PERSONFACTORY_H
#define PERSONFACTORY_H

#include "iperson.h"
#include <string>
#include <ctime>

class PersonFactory {
public:
    virtual ~PersonFactory() = default;

    virtual IPerson* createIndividual() = 0;
    virtual IPerson* createFamily() = 0;
    virtual IPerson* createIndividual(const std::string& name,
                                     const std::string& gender,
                                     const std::tm& birthday) = 0;
    virtual IPerson* createPersonWithId(int id) = 0;
};

class DefaultPersonFactory : public PersonFactory {
public:
    IPerson* createIndividual() override;
    IPerson* createFamily() override;
    IPerson* createIndividual(const std::string& name,
                             const std::string& gender,
                             const std::tm& birthday) override;
    IPerson* createPersonWithId(int id) override;
};

#endif // PERSONFACTORY_H