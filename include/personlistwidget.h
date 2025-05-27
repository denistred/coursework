#ifndef PERSONLISTWIDGET_H
#define PERSONLISTWIDGET_H

#include <QListView>
#include <QStandardItemModel>
#include "person.h"
#include "personscene.h"

class PersonListWidget : public QListView
{
    Q_OBJECT
public:
    explicit PersonListWidget(QWidget *parent = nullptr);

    void addPerson(Person *person);
    void clear();
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &filename);
    void selectPersonById(int id);
    QList<Person *> getPersons() const;

    void setScene(PersonScene *scene);

    signals:
        void personDoubleClicked(const Person &person);
        void personSelected(int personId);

public slots:
    void removeSelectedPerson();

private slots:
    void onItemDoubleClicked(const QModelIndex &index);
    void onItemClicked(const QModelIndex &index);

private:
    QStandardItemModel *model;
    QList<Person*> personsList;
    PersonScene *scene = nullptr;
};

#endif