#ifndef RELATIONITEM_H
#define RELATIONITEM_H

#include <QGraphicsLineItem>

class PersonItem;

class RelationItem : public QGraphicsLineItem {
public:
    RelationItem(PersonItem *start, PersonItem *end, QGraphicsItem *parent = nullptr);
    void updatePosition();

private:
    PersonItem *fromItem;
    PersonItem *toItem;
};

#endif
