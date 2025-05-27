#include "../include/personitem.h"
#include <QString>

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
            QPixmap scaled = pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            photoItem = new QGraphicsPixmapItem(scaled, this);
            photoItem->setPos(0, -scaled.height());
            photoItem->setAcceptedMouseButtons(Qt::AllButtons);
            photoItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
            photoItem->setAcceptHoverEvents(true);
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