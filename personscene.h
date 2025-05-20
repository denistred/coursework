#ifndef PERSONSCENE_H
#define PERSONSCENE_H

#include <QGraphicsScene>
#include "person.h"

class PersonScene : public QGraphicsScene {
public:
    explicit PersonScene(QObject *parent = nullptr);
    void addPerson(Person *person);
};


#endif //PERSONSCENE_H
