#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "person.h"
#include "relationitem.h"
#include "personitem.h"

class AbstractItemFactory {
public:
    virtual Person* createPerson() = 0;
    virtual Person* createPersonWithId(int id) = 0;
    virtual void setId(int id) = 0;
    virtual PersonItem* createPersonItem(Person* person) = 0;
    virtual RelationItem* createRelationItem(PersonItem* from, PersonItem* to) = 0;
    virtual ~AbstractItemFactory() = default;
};

#endif
