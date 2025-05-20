#include "personscene.h"
#include "personitem.h"

PersonScene::PersonScene(QObject *parent) : QGraphicsScene(parent) {}

void PersonScene::addPerson(Person *person) {
    auto *item = new PersonItem(person);
    addItem(item);
    item->setPos(0, 0);
}
