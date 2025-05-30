#include "abstractfactory.h"
#include "personfactory.h"

#include <iostream>

#include "person.h"
#include "personitem.h"
#include "relationitem.h"


Person* PersonFactory::createPerson() {
    Person* person = new Person();
    person->setId(personNextId++);
    std::cout << person->getId() << "Simple created" << std::endl;
    return person;
}

Person* PersonFactory::createPersonWithId(int id) {
    Person* person = new Person();
    person->setId(id);
    this->setId(id);
    return person;
}

void PersonFactory::setId(int id) {
    if (id >= this->personNextId) {
        this->personNextId = id + 1;
    }
}

PersonItem* PersonFactory::createPersonItem(Person* person) {
    return new PersonItem(person);
}
RelationItem* PersonFactory::createRelationItem(PersonItem* from, PersonItem* to) {
    return new RelationItem(from, to);
}