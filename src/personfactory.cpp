#include "abstractfactory.h"
#include "personfactory.h"
#include "person.h"
#include "personitem.h"
#include "relationitem.h"


Person* PersonFactory::createPerson() {
    Person* person = new Person();
    person->setId(personNextId++);
    return person;
}

Person* PersonFactory::createPersonWithId(int id) {
    Person* person = new Person();
    person->setId(id);
    return person;
}

void PersonFactory::setId(int id) {
    this->personNextId = id;
}

PersonItem* PersonFactory::createPersonItem(Person* person) {
    return new PersonItem(person);
}
RelationItem* PersonFactory::createRelationItem(PersonItem* from, PersonItem* to) {
    return new RelationItem(from, to);
}