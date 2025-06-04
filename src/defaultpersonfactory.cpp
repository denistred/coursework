#include "personfactory.h"
#include "individual.h"
#include "family.h"

IPerson* DefaultPersonFactory::createIndividual() {
    return new Individual();
}

IPerson* DefaultPersonFactory::createFamily() {
    return new Family();
}

IPerson* DefaultPersonFactory::createIndividual(const std::string& name, 
                                              const std::string& gender,
                                              const std::tm& birthday) {
    Individual* person = new Individual();
    person->setName(name);
    person->setGender(gender);
    person->setBirthday(birthday);
    return person;
}

IPerson* DefaultPersonFactory::createPersonWithId(int id) {
    Individual* person = new Individual();
    person->setId(id);
    return person;
}