#include "personscene.h"
#include "personitem.h"

PersonScene::PersonScene(QObject *parent) : QGraphicsScene(parent) {}

void PersonScene::addPerson(Person *person) {
    auto *item = new PersonItem(person);
    connect(item, &PersonItem::personSelected, this, &PersonScene::personSelected);
    addItem(item);
    item->setPos(0, 0);
}

void PersonScene::selectPersonById(int id) {
    for (auto item : items()) {
        auto personItem = qgraphicsitem_cast<PersonItem*>(item);
        if (personItem) {
            personItem->setSelected(personItem->getPersonId() == id);
        }
    }
}
