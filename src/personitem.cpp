#include "personitem.h"
#include <QGraphicsSceneMouseEvent>

PersonItem::PersonItem(Person *person, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), person(person)
{
    setFlags(ItemIsMovable | ItemIsSelectable);

    setPlainText(person->getName());

    if (!person->getPhotoPath().isEmpty()) {
        photoItem = new QGraphicsPixmapItem(QPixmap(person->getPhotoPath()).scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
        photoItem->setPos(0, -60);
    }

    connect(person, &Person::dataChanged, this, &PersonItem::onPersonDataChanged);
}

int PersonItem::getPersonId() const {
    return person->getId();
}

Person* PersonItem::getPerson() const {
    return person;
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

void PersonItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit personSelected(person->getId());
    QGraphicsTextItem::mousePressEvent(event);
}

void PersonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mouseMoveEvent(event);
    updateRelations();
}

void PersonItem::onPersonDataChanged() {
    setPlainText(person->getName());

    if (photoItem) {
        if (!person->getPhotoPath().isEmpty()) {
            photoItem->setPixmap(QPixmap(person->getPhotoPath()).scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            photoItem->show();
        } else {
            photoItem->hide();
        }
    }
}

void PersonItem::removeRelationWith(int otherPersonId) {
    relations.erase(std::remove_if(relations.begin(), relations.end(),
        [otherPersonId](RelationItem* r) {
            return r->getFirst()->getPersonId() == otherPersonId ||
                   r->getSecond()->getPersonId() == otherPersonId;
        }), relations.end());
}