#ifndef PERSONITEM_H
#define PERSONITEM_H

#include <QGraphicsTextItem>
#include "person.h"

class PersonItem : public QGraphicsTextItem {
public:
    PersonItem(Person *person);

private:
    Person *person;
};

#endif
