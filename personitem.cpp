#include "personitem.h"

PersonItem::PersonItem(Person *person)
    : QGraphicsTextItem(person->getName()), person(person)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

