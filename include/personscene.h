#ifndef PERSONSCENE_H
#define PERSONSCENE_H

#include <QGraphicsScene>
#include "person.h"
#include "personitem.h"

class PersonScene : public QGraphicsScene {

    Q_OBJECT

public:
    explicit PersonScene(QObject *parent = nullptr);
    void addPerson(Person *person);
    void selectPersonById(int id);
    void createRelationBetweenSelected();
    signals:
        void personSelected(int personId);

private:
    QPointF nextItemPos = QPointF(0, 0);
};


#endif
