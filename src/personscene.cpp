#include "../include/personscene.h"

#include <iostream>
#include "../include/personitem.h"
#include "../include/relationitem.h"

PersonScene::PersonScene(QObject *parent) : QGraphicsScene(parent) {
}

void PersonScene::addPerson(IPerson *person) {
    if (person->getChildren().empty()) {
        auto *item = new PersonItem(person);
        connect(item, &PersonItem::personSelected, this, &PersonScene::personSelected);
        addItem(item);
        item->setPos(nextItemPos);
        nextItemPos.rx() += 170;
    } else {
        auto *item = new PersonItem(person);
        connect(item, &PersonItem::personSelected, this, &PersonScene::personSelected);
        addItem(item);
        item->setPos(nextItemPos);
        nextItemPos.rx() += 170;

        for (IPerson *child : person->getChildren()) {
            addPerson(child);

            PersonItem *childItem = nullptr;
            for (QGraphicsItem *gItem : items()) {
                auto *temp = qgraphicsitem_cast<PersonItem *>(gItem);
                if (temp && temp->getPersonId() == child->getId()) {
                    childItem = temp;
                    break;
                }
            }

            if (childItem) {
                auto *rel = new RelationItem(item, childItem);
                addItem(rel);
                item->addRelation(rel);
                childItem->addRelation(rel);
            }
        }
    }
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

    IPerson *parent = item1->getPerson();
    IPerson *child = item2->getPerson();

    for (IPerson *existing : parent->getChildren()) {
        if (existing->getId() == child->getId())
            return;
    }

    parent->addChild(child);

    std::cout << parent->getName() << " --> " << child->getName() << std::endl;

    auto *rel = new RelationItem(item1, item2);
    addItem(rel);
    item1->addRelation(rel);
    item2->addRelation(rel);
}

void PersonScene::removeRelationBetweenSelected() {
    QList<QGraphicsItem *> selected = selectedItems();
    if (selected.size() != 2) return;

    auto *item1 = qgraphicsitem_cast<PersonItem *>(selected[0]);
    auto *item2 = qgraphicsitem_cast<PersonItem *>(selected[1]);
    if (!item1 || !item2) return;

    IPerson *parent = item1->getPerson();
    IPerson *child = item2->getPerson();

    parent->removeChild(child->getName());

    for (QGraphicsItem *item : items()) {
        auto *rel = qgraphicsitem_cast<RelationItem *>(item);
        if (!rel) continue;

        PersonItem *first = rel->getFirst();
        PersonItem *second = rel->getSecond();

        if ((first == item1 && second == item2) || (first == item2 && second == item1)) {
            removeItem(rel);
            delete rel;
            break;
        }
    }
}

void PersonScene::restoreRelations(const QList<IPerson *> &persons) {
    QMap<int, PersonItem *> idToItem;
    for (QGraphicsItem *item: items()) {
        auto *pItem = qgraphicsitem_cast<PersonItem *>(item);
        if (pItem) {
            idToItem[pItem->getPersonId()] = pItem;
        }
    }

    for (IPerson *parent: persons) {
        int parentId = parent->getId();
        PersonItem *parentItem = idToItem.value(parentId, nullptr);
        if (!parentItem) continue;

        for (IPerson *child : parent->getChildren()) {
            PersonItem *childItem = idToItem.value(child->getId(), nullptr);
            if (!childItem) continue;

            auto *rel = new RelationItem(parentItem, childItem);
            addItem(rel);
            parentItem->addRelation(rel);
            childItem->addRelation(rel);

            std::cout << parent->getName()
                      << " --> "
                      << child->getName()
                      << std::endl;
        }
    }
}
