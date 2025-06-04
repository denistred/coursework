#ifndef PERSONLISTWIDGET_H
#define PERSONLISTWIDGET_H

#include <QListView>
#include <QStandardItemModel>
#include "personrepository.h"
#include "personfactory.h"
#include "personscene.h"

class PersonListWidget : public QListView
{
    Q_OBJECT
public:
    explicit PersonListWidget(QWidget *parent = nullptr);

    void setScene(PersonScene *s);
    void setFactory(PersonFactory* factory);
    void selectPersonById(int id);
    void loadScene();

    signals:
        void personSelected(int id);

public slots:
    void refreshList();
    void removeSelectedPerson();

private slots:
    void onItemDoubleClicked(const QModelIndex &index);
    void onItemClicked(const QModelIndex &index);

private:
    QStandardItemModel *model;
    PersonFactory* factory = nullptr;
    PersonScene* scene = nullptr;
    PersonRepository& repo = PersonRepository::instance();

};

#endif // PERSONLISTWIDGET_H