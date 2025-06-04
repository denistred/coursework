#ifndef PERSONLISTWIDGET_H
#define PERSONLISTWIDGET_H

#include <QListView>
#include <QStandardItemModel>
#include "person.h"
#include "personscene.h"
#include "abstractfactory.h"
#include "personrepository.h"

class PersonListWidget : public QListView
{
    Q_OBJECT
public:
    explicit PersonListWidget(QWidget *parent = nullptr);

    void addPerson(IPerson *person);
    void clear();
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &filename);
    void selectPersonById(int id);
    QList<IPerson *> getPersons() const;
    void setFactory(AbstractItemFactory* factory);
    void setRepository(PersonRepository* repository);
    void setScene(PersonScene *scene);

    signals:
        void personDoubleClicked(const IPerson &person);
        void personSelected(int personId);

public slots:
    void removeSelectedPerson();

private slots:
    void onItemDoubleClicked(const QModelIndex &index);
    void onItemClicked(const QModelIndex &index);

private:
    QStandardItemModel *model;
    QList<IPerson*> personsList;
    PersonScene *scene = nullptr;
    AbstractItemFactory* factory;
    PersonRepository* repository;
};

#endif