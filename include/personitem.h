#ifndef PERSONITEM_H
#define PERSONITEM_H

#include <QGraphicsTextItem>
#include "relationitem.h"
#include "mainwindow.h"
#include "person.h"

class PersonItem : public QGraphicsTextItem {
    Q_OBJECT
public:
    PersonItem(Person *person);
    int getPersonId() const;
    void addRelation(RelationItem *relation);
    void removeRelation(RelationItem *relation);
    void updateRelations();
signals:
    void personSelected(int personId);
public slots:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    Person *person;
    QGraphicsPixmapItem *photoItem = nullptr;
    QList<RelationItem *> relations;
};

#endif
