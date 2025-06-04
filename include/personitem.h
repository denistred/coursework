#ifndef PERSONITEM_H
#define PERSONITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

#include "relationitem.h"
#include "individual.h"

class PersonItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit PersonItem(IPerson *person, QGraphicsItem *parent = nullptr);

    int getPersonId() const;
    IPerson* getPerson() const;

    void addRelation(RelationItem *relation);
    void removeRelation(RelationItem *relation);
    void updateRelations();
    void removeRelationWith(int otherPersonId);
    void updateData();

    signals:
        void personSelected(int personId);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
    void onPersonDataChanged();

private:
    IPerson *person;
    QGraphicsPixmapItem *photoItem = nullptr;
    QList<RelationItem *> relations;
    QGraphicsRectItem* textBackground = nullptr;
};

#endif // PERSONITEM_H
