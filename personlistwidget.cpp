#include "personlistwidget.h"
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
        QMessageBox::information(
            this,
            "Данные о человеке",
            person->getName()
        );
    }
}
