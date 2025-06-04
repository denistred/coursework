#include "personitem.h"
#include <QFile>
#include <QCoreApplication>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

PersonItem::PersonItem(IPerson *person, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), person(person)
{
    setFlags(ItemIsMovable | ItemIsSelectable);

    auto pos = person->getPosition();
    setPos(pos.first, pos.second);

    setPlainText(QString::fromStdString(person->getName()));

    QString path = QString::fromStdString(person->getPhotoPath());
    if (path.isEmpty() || !QFile::exists(path)) {
        path = ":/default-avatar-icon-of-social-media-user-vector.jpg";
        std::cout << path.toStdString() << std::endl;
    }

    QPixmap pix(path);
    if (pix.isNull()) {
        qDebug() << "Не удалось загрузить ресурс!";
    }
    photoItem = new QGraphicsPixmapItem(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);

    qreal textWidth = boundingRect().width();
    qreal photoWidth = photoItem->pixmap().width();
    qreal xPos = (textWidth - photoWidth) / 2.0;

    photoItem->setPos(xPos, -100);

    // connect(person, &Person::dataChanged, this, &PersonItem::onPersonDataChanged);
}

int PersonItem::getPersonId() const {
    return person->getId();
}

IPerson* PersonItem::getPerson() const {
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
    person->setPosition(pos().x(), pos().y());
}

void PersonItem::onPersonDataChanged() {
    setPlainText(QString::fromStdString(person->getName()));

    if (photoItem) {
        if (person->getPhotoPath() != "") {
            photoItem->setPixmap(QPixmap(QString::fromStdString(person->getPhotoPath())).scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

void PersonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QRectF backgroundRect = rect.adjusted(-2, -2, 2, 2);

    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::NoPen);

    painter->drawRect(backgroundRect);

    QGraphicsTextItem::paint(painter, option, widget);
}