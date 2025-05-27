#include "../include/personscene.h"
#include "../include/personitem.h"

PersonScene::PersonScene(QObject *parent) : QGraphicsScene(parent) {}

void PersonScene::addPerson(Person *person) {
    auto *item = new PersonItem(person);
    connect(item, &PersonItem::personSelected, this, &PersonScene::personSelected);
    addItem(item);

    item->setPos(nextItemPos);

    nextItemPos.rx() += 170;
}

void PersonScene::selectPersonById(int id) {
    for (auto item : items()) {
        auto personItem = qgraphicsitem_cast<PersonItem*>(item);
        if (personItem) {
            personItem->setSelected(personItem->getPersonId() == id);
        }
    }
}

void PersonScene::createRelationBetweenSelected() {
    QList<QGraphicsItem*> selected = selectedItems();
    if (selected.size() != 2) return;

    auto *item1 = qgraphicsitem_cast<PersonItem*>(selected[0]);
    auto *item2 = qgraphicsitem_cast<PersonItem*>(selected[1]);
    if (!item1 || !item2) return;

    auto *line = new RelationItem(item1, item2);
    addItem(line);
}