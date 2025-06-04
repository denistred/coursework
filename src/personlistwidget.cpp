#include "personlistwidget.h"
#include "inputdialog.h"
#include <QMessageBox>
#include <QDate>
#include <iostream>

PersonListWidget::PersonListWidget(QWidget *parent)
    : QListView(parent), model(new QStandardItemModel(this)), factory(nullptr)
{
    setModel(model);
    setSelectionMode(SingleSelection);

    connect(this, &QListView::doubleClicked,
            this, &PersonListWidget::onItemDoubleClicked);
    connect(this, &QListView::clicked,
            this, &PersonListWidget::onItemClicked);


    connect(&repo, &PersonRepository::personAdded,
            this, &PersonListWidget::refreshList);
    connect(&repo, &PersonRepository::personRemoved,
            this, &PersonListWidget::refreshList);
    connect(&repo, &PersonRepository::dataChanged,
            this, &PersonListWidget::refreshList);

    refreshList();
}

void PersonListWidget::loadScene() {
    const auto& allPersons = repo.getAllPersons();
    if (scene) {
        qDebug() << "LOADING SCENE";
        scene->clear();
        for (IPerson* person : allPersons) {
            scene->addPerson(person);
        }
    }
}

void PersonListWidget::refreshList()
{
    model->clear();
    const auto& allPersons = repo.getAllPersons();

    for (IPerson* person : allPersons) {
        QStandardItem *item = new QStandardItem(QString::fromStdString(person->getName()));
        item->setData(person->getId(), Qt::UserRole);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        model->appendRow(item);
    }
    qDebug() << "FIRST REFRESH";
    loadScene();
    if (scene && factory) {
        scene->clear();

        for (IPerson* person : allPersons) {
            scene->addPerson(person);
        }


        QList<IPerson*> qList;
        qList.reserve(allPersons.size());
        for (IPerson* person : allPersons) {
            qList.append(person);
        }

        scene->restoreRelations(qList);
    }
}

void PersonListWidget::onItemDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    int id = model->itemFromIndex(index)->data(Qt::UserRole).toInt();
    IPerson *person = repo.getPersonById(id);
    if (!person) return;

    InputDialog dialog(this, person);

    if (dialog.exec() == QDialog::Accepted) {
        person->setName(dialog.getName().toStdString());
        person->setGender(dialog.getGender().toStdString());

        QDate qDate = dialog.getBirthday();
        std::tm tmDate = {};
        tmDate.tm_year = qDate.year() - 1900;
        tmDate.tm_mon = qDate.month() - 1;
        tmDate.tm_mday = qDate.day();
        person->setBirthday(tmDate);

        person->setPlaceOfBirth(dialog.getPlaceOfBirth().toStdString());
        person->setProfession(dialog.getProfession().toStdString());
        person->setPhotoPath(dialog.getPhotoPath().toStdString());


        model->itemFromIndex(index)->setText(QString::fromStdString(person->getName()));


        repo.notifyPersonUpdated(person);
        QMessageBox::information(this, "Данные", "Данные изменены");
    }
}

void PersonListWidget::onItemClicked(const QModelIndex &index) {
    if (!index.isValid()) return;
    int id = model->itemFromIndex(index)->data(Qt::UserRole).toInt();
    emit personSelected(id);
}

void PersonListWidget::removeSelectedPerson()
{
    QModelIndex index = currentIndex();
    if (!index.isValid()) return;

    int id = model->itemFromIndex(index)->data(Qt::UserRole).toInt();
    repo.removePerson(id);
}

void PersonListWidget::selectPersonById(int id) {
    for (int i = 0; i < model->rowCount(); ++i) {
        QStandardItem* item = model->item(i);
        if (item->data(Qt::UserRole).toInt() == id) {
            setCurrentIndex(model->index(i, 0));
            break;
        }
    }
}

void PersonListWidget::setScene(PersonScene *s) {
    scene = s;
}

void PersonListWidget::setFactory(PersonFactory* factory) {
    this->factory = factory;
}
