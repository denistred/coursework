#include "personitem.h"

PersonItem::PersonItem(Person *person)
    : QGraphicsTextItem(person->getName()), person(person)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

int PersonItem::getPersonId() const {
    return person->getId();
}

void PersonItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
    emit personSelected(getPersonId());
}