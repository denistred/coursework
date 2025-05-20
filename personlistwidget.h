#ifndef PERSONLISTWIDGET_H
#define PERSONLISTWIDGET_H

#include <QListView>
#include <QStandardItemModel>
#include "person.h"

class PersonListWidget : public QListView
{
    Q_OBJECT
public:
    explicit PersonListWidget(QWidget *parent = nullptr);

    void addPerson(Person *person);
    void clear();
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &filename);

    signals:
        void personDoubleClicked(const Person &person);

public slots:
    void removeSelectedPerson();

private slots:
    void onItemDoubleClicked(const QModelIndex &index);

private:
    QStandardItemModel *model;
    QList<Person*> personsList;
};

#endif