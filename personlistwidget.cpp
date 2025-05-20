#include "personlistwidget.h"
#include "inputdialog.h"
#include <QStandardItem>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

PersonListWidget::PersonListWidget(QWidget *parent)
    : QListView(parent), model(new QStandardItemModel(this))
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
        obj["name"] = p->getName();
        obj["gender"] = p->getGender();
        obj["birthday"] = p->getBirthday().toString(Qt::ISODate);
        obj["placeOfBirth"] = p->getPlaceOfBirth();
        obj["profession"] = p->getProfession();
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
    for (const QJsonValue &val : array) {
        QJsonObject obj = val.toObject();
        Person *person = new Person();
        person->setName(obj["name"].toString());
        person->setGender(obj["gender"].toString());

        QDate date = QDate::fromString(obj["birthday"].toString(), Qt::ISODate);
        if (date.isValid())
            person->setBirthday(date);

        person->setPlaceOfBirth(obj["placeOfBirth"].toString());
        person->setProfession(obj["profession"].toString());

        addPerson(person);
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