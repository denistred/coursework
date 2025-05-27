#include "../include/personitem.h"
#include <QString>
#include "relationitem.h"

PersonItem::PersonItem(Person *person)
    : QGraphicsTextItem(person->getName()), person(person)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    connect(person, &Person::nameChanged, this, [this](const QString &newName) {
        setPlainText(newName);
    });

    if (!person->getPhotoPath().isEmpty()) {
        QPixmap pix(person->getPhotoPath());
        if (!pix.isNull()) {
            QPixmap scaled = pix.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            photoItem = new QGraphicsPixmapItem(scaled, this);
            photoItem->setPos(0, -scaled.height());
            photoItem->setAcceptedMouseButtons(Qt::AllButtons);
        }
    }
}

int PersonItem::getPersonId() const {
    return person->getId();
}

void PersonItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
    emit personSelected(getPersonId());
}

void PersonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mouseMoveEvent(event);
    updateRelations();
}

void PersonItem::addRelation(RelationItem *relation) {
    if (!relations.contains(relation))
        relations.append(relation);
}

void PersonItem::removeRelation(RelationItem *relation) {
    relations.removeAll(relation);
}

void PersonItem::updateRelations() {
    for (RelationItem *rel : relations) {
        rel->updatePosition();
    }
}