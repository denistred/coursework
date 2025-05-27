#include "../include/personitem.h"
#include <QString>

PersonItem::PersonItem(Person *person)
    : QGraphicsTextItem(person->getName()), person(person)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    connect(person, &Person::nameChanged, this, [this](const QString &newName) {
        setPlainText(newName);
    });
}

int PersonItem::getPersonId() const {
    return person->getId();
}

void PersonItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
    emit personSelected(getPersonId());
}