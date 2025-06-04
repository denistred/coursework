#ifndef PERSONREPOSITORY_H
#define PERSONREPOSITORY_H

#include <QList>
#include <QString>
#include "person.h"
#include "abstractfactory.h"


class PersonRepository {
public:
    explicit PersonRepository(AbstractItemFactory* factory);

    QList<IPerson*> load(const QString& filename);
    void save(const QString& filename, const QList<IPerson*>& persons);

private:
    AbstractItemFactory* factory;
    int maxId = 0;
};

#endif // PERSONREPOSITORY_H
