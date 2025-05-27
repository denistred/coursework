#ifndef PERSONITEM_H
#define PERSONITEM_H

#include <QGraphicsTextItem>

#include "mainwindow.h"
#include "person.h"

class PersonItem : public QGraphicsTextItem {
    Q_OBJECT
public:
    PersonItem(Person *person);
    int getPersonId() const;
signals:
    void personSelected(int personId);
public slots:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    Person *person;
    QGraphicsPixmapItem *photoItem = nullptr;
};

#endif
