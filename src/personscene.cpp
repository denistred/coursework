#include "../include/personscene.h"

#include <iostream>

#include "../include/personitem.h"

PersonScene::PersonScene(QObject *parent) : QGraphicsScene(parent) {
}

void PersonScene::addPerson(Person *person) {
    auto *item = new PersonItem(person);

    connect(item, &PersonItem::personSelected, this, &PersonScene::personSelected);
    addItem(item);

    item->setPos(nextItemPos);

    nextItemPos.rx() += 170;
}

void PersonScene::selectPersonById(int id) {
    for (auto item: items()) {
        auto personItem = qgraphicsitem_cast<PersonItem *>(item);
        if (personItem) {
            personItem->setSelected(personItem->getPersonId() == id);
        }
    }
}

void PersonScene::createRelationBetweenSelected() {
    QList<QGraphicsItem *> selected = selectedItems();
    if (selected.size() != 2) return;

    auto *item1 = qgraphicsitem_cast<PersonItem *>(selected[0]);
    auto *item2 = qgraphicsitem_cast<PersonItem *>(selected[1]);
    if (!item1 || !item2) return;

    auto *line = new RelationItem(item1, item2);
    addItem(line);

    item1->getPerson()->addRelation(item2->getPersonId());
    item2->getPerson()->addRelation(item1->getPersonId());
}

void PersonScene::removeRelationBetweenSelected() {
    QList<QGraphicsItem *> selected = selectedItems();
    if (selected.size() != 2) return;

    auto *item1 = qgraphicsitem_cast<PersonItem *>(selected[0]);
    auto *item2 = qgraphicsitem_cast<PersonItem *>(selected[1]);
    if (!item1 || !item2) return;

    for (QGraphicsItem *item : items()) {
        auto *rel = qgraphicsitem_cast<RelationItem *>(item);
        if (!rel) continue;

        PersonItem *first = rel->getFirst();
        PersonItem *second = rel->getSecond();

        if ((first == item1 && second == item2) || (first == item2 && second == item1)) {
            removeItem(rel);
            delete rel;

            item1->getPerson()->removeRelation(item2->getPersonId());
            item2->getPerson()->removeRelation(item1->getPersonId());

            break;
        }
    }
}


void PersonScene::restoreRelations(const QList<Person *> &persons) {
    QMap<int, PersonItem *> idToItem;
    for (QGraphicsItem *item: items()) {
        auto *pItem = qgraphicsitem_cast<PersonItem *>(item);
        if (pItem) {
            idToItem[pItem->getPersonId()] = pItem;
        }
    }

    QSet<QPair<int, int> > created;

    for (Person *person: persons) {
        int id = person->getId();
        PersonItem *fromItem = idToItem.value(id, nullptr);
        if (!fromItem) continue;

        for (int relatedId: person->getRelations()) {
            if (id == relatedId) continue;

            QPair<int, int> key = qMakePair(qMin(id, relatedId), qMax(id, relatedId));
            if (created.contains(key)) continue;

            PersonItem *toItem = idToItem.value(relatedId, nullptr);
            if (!toItem) continue;

            auto *rel = new RelationItem(fromItem, toItem);
            addItem(rel);

            fromItem->addRelation(rel);
            toItem->addRelation(rel);

            created.insert(key);

            std::cout << fromItem->getPerson()->getName().toStdString()
                    << " <--> "
                    << toItem->getPerson()->getName().toStdString()
                    << std::endl;
        }
    }
}
