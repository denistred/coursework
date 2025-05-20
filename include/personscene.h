#ifndef PERSONSCENE_H
#define PERSONSCENE_H

#include <QGraphicsScene>
#include "person.h"

class PersonScene : public QGraphicsScene {

    Q_OBJECT

public:
    explicit PersonScene(QObject *parent = nullptr);
    void addPerson(Person *person);
    void selectPersonById(int id);
    signals:
        void personSelected(int personId);
};


#endif
