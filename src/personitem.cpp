#include "personitem.h"
#include <QFile>
#include <QCoreApplication>
#include <iostream>
#include <QGraphicsSceneMouseEvent>

PersonItem::PersonItem(Person *person, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), person(person)
{
    setFlags(ItemIsMovable | ItemIsSelectable);

    if (!person->getPosition().isNull()) {
        setPos(person->getPosition());
    }

    setPlainText(person->getName());

    QString path = person->getPhotoPath();
    if (path.isEmpty() || !QFile::exists(path)) {
        path = ":/default-avatar-icon-of-social-media-user-vector.jpg";
        std::cout << path.toStdString() << std::endl;
    }

    QPixmap pix(path);
    if (pix.isNull()) {
        qDebug() << "Не удалось загрузить ресурс!";
    }
    photoItem = new QGraphicsPixmapItem(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
    photoItem->setPos(0, -100);
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
    person->setPosition(pos());
}

void PersonItem::onPersonDataChanged() {
    setPlainText(person->getName());

    if (photoItem) {
        if (!person->getPhotoPath().isEmpty()) {
            photoItem->setPixmap(QPixmap(person->getPhotoPath()).scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            photoItem->show();
        }
        else {
            photoItem->setPixmap(QPixmap(":/default-avatar-icon-of-social-media-user-vector.jpg").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            photoItem->show();
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