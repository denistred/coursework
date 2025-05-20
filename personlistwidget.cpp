#include "personlistwidget.h"
#include "inputdialog.h"
#include <QStandardItem>
#include <QMessageBox>

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
    item->setData(QVariant::fromValue(personsList.size() - 1), Qt::UserRole);

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
