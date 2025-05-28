#include "../include/personlistwidget.h"

#include <iostream>

#include "../include/inputdialog.h"
#include <QStandardItem>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

PersonListWidget::PersonListWidget(QWidget *parent)
    : QListView(parent), model(new QStandardItemModel(this)), factory(nullptr)
{
    setModel(model);
    setSelectionMode(SingleSelection);

    connect(this, &QListView::doubleClicked, 
            this, &PersonListWidget::onItemDoubleClicked);
}

void PersonListWidget::addPerson(Person *person)
{
    personsList.append(person);
    QStandardItem *item = new QStandardItem(person->getName());
    item->setData(person->getId(), Qt::UserRole);

    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    model->appendRow(item);
}

void PersonListWidget::clear()
{
    model->clear();
    personsList.clear();
}

void PersonListWidget::onItemDoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    if (row >= 0 && row < personsList.size()) {
        Person *person = personsList[row];

        InputDialog dialog(this, person);

        if (dialog.exec() == QDialog::Accepted) {
            person->setName(dialog.getName());
            model->item(row)->setText(person->getName());
            person->setGender(dialog.getGender());
            person->setBirthday(dialog.getBirthday());
            person->setPlaceOfBirth(dialog.getPlaceOfBirth());
            person->setProfession(dialog.getProfession());
            person->setPhotoPath(dialog.getPhotoPath());
            QMessageBox::information(this, "Данные", "Данные изменены");
        }
    }
}

void PersonListWidget::onItemClicked(const QModelIndex &index) {
    int row = index.row();
    if (row >= 0 && row < personsList.size()) {
        emit personSelected(personsList[row]->getId());
    }
}

void PersonListWidget::saveToFile(const QString &filename)
{
    QJsonArray array;
    for (const Person *p : personsList) {
        QJsonObject obj;
        obj["id"] = p->getId();
        obj["name"] = p->getName();
        obj["gender"] = p->getGender();
        obj["birthday"] = p->getBirthday().toString(Qt::ISODate);
        obj["placeOfBirth"] = p->getPlaceOfBirth();
        obj["profession"] = p->getProfession();
        obj["photoPath"] = p->getPhotoPath();
        obj["x"] = p->getPosition().x();
        obj["y"] = p->getPosition().y();
        QJsonArray relArray;
        for (int id : p->getRelations()) {
            relArray.append(id);
        }
        obj["relations"] = relArray;

        array.append(obj);
    }

    QJsonDocument doc(array);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void PersonListWidget::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return;

    clear();

    QJsonArray array = doc.array();
    personsList.clear();
    QList<QList<int>> pendingRelations;

    for (const QJsonValue &val : array) {
        QJsonObject obj = val.toObject();
        int id = obj["id"].toInt();
        Person *person = factory->createPersonWithId(id);
        factory->setId(id);
        person->setName(obj["name"].toString());
        person->setGender(obj["gender"].toString());

        QDate date = QDate::fromString(obj["birthday"].toString(), Qt::ISODate);
        if (date.isValid())
            person->setBirthday(date);

        person->setPlaceOfBirth(obj["placeOfBirth"].toString());
        person->setProfession(obj["profession"].toString());
        person->setPhotoPath(obj["photoPath"].toString());

        QPointF pos(obj["x"].toDouble(), obj["y"].toDouble());
        person->setPosition(pos);

        personsList.append(person);

        QStandardItem *item = new QStandardItem(person->getName());
        item->setData(person->getId(), Qt::UserRole);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        model->appendRow(item);

        if (scene) {
            PersonItem *pItem = factory->createPersonItem(person);
            scene->addItem(pItem);
        }

        QJsonArray relArray = obj["relations"].toArray();
        QList<int> relations;
        for (const QJsonValue &v : relArray) {
            relations.append(v.toInt());
        }
        pendingRelations.append(relations);
    }

    for (int i = 0; i < personsList.size(); ++i) {
        Person *p = personsList[i];
        for (int relatedId : pendingRelations[i]) {
            if (!p->getRelations().contains(relatedId))
                p->addRelation(relatedId);
        }
    }
    if (scene) {
        scene->restoreRelations(personsList);
    }
}

void PersonListWidget::removeSelectedPerson()
{
    QModelIndex index = currentIndex();
    int row = index.row();
    if (row >= 0 && row < personsList.size()) {
        delete personsList[row];
        personsList.removeAt(row);
        model->removeRow(row);
    }
}

void PersonListWidget::selectPersonById(int id) {
    for (int i = 0; i < personsList.size(); ++i) {
        if (personsList[i]->getId() == id) {
            setCurrentIndex(model->index(i, 0));
            break;
        }
    }
}

QList<Person *> PersonListWidget::getPersons() const {
    return personsList;
}

void PersonListWidget::setScene(PersonScene *s) {
    scene = s;
}

void PersonListWidget::setFactory(AbstractItemFactory* factory) {
    this->factory = factory;
}