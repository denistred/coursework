#include "relationitem.h"
#include "personitem.h"

RelationItem::RelationItem(PersonItem *start, PersonItem *end, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), fromItem(start), toItem(end) {
    setZValue(-1);
    fromItem->addRelation(this);
    toItem->addRelation(this);
    updatePosition();
}

void RelationItem::updatePosition() {
    if (!fromItem || !toItem) return;

    QPointF p1 = fromItem->sceneBoundingRect().center();
    QPointF p2 = toItem->sceneBoundingRect().center();
    setLine(QLineF(p1, p2));
}
