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
    if (repository)
        repository->save(filename, personsList);
}

void PersonListWidget::loadFromFile(const QString &filename)
{
    if (!repository) return;

    clear();
    personsList = repository->load(filename);

    model->clear();

    for (Person* person : personsList) {
        QStandardItem* item = new QStandardItem(person->getName());
        item->setData(person->getId(), Qt::UserRole);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        model->appendRow(item);

        if (scene) {
            PersonItem* pItem = factory->createPersonItem(person);
            scene->addItem(pItem);
        }
    }

    if (scene)
        scene->restoreRelations(personsList);
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

void PersonListWidget::setRepository(PersonRepository* repository) {
    this->repository = repository;
}