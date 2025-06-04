#ifndef PERSONSCENE_H
#define PERSONSCENE_H

#include <QGraphicsScene>
#include "individual.h"
#include "personitem.h"

class PersonScene : public QGraphicsScene {

    Q_OBJECT

public:
    explicit PersonScene(QObject *parent = nullptr);
    void addPerson(IPerson *person);
    void updatePerson(IPerson *person);
    void selectPersonById(int id);
    void createRelationBetweenSelected();
    void removeRelationBetweenSelected();
    void restoreRelations(const QList<IPerson *> &persons);
    signals:
        void personSelected(int personId);

private:
    QPointF nextItemPos = QPointF(0, 0);

};


#endif
