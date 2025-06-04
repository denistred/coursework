#ifndef PERSONREPOSITORY_H
#define PERSONREPOSITORY_H

#include <QObject>
#include <vector>
#include <map>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDate>
#include "iperson.h"
#include "personfactory.h"

class PersonRepository : public QObject
{
    Q_OBJECT
public:
    PersonRepository(const PersonRepository&) = delete;
    PersonRepository& operator=(const PersonRepository&) = delete;

    static PersonRepository& instance();

    void addPerson(IPerson* person);
    void removePerson(int id);
    IPerson* getPersonById(int id) const;
    const std::vector<IPerson*>& getAllPersons() const;
    void clear();

    IPerson* createIndividual();
    IPerson* createFamily();
    IPerson* createIndividual(const std::string& name,
                             const std::string& gender,
                             const std::tm& birthday);

    void saveToFile(const QString& filename) const;
    void loadFromFile(const QString& filename);

    void setFactory(PersonFactory* factory);

    void notifyPersonUpdated(IPerson* person);

    signals:
        void personAdded(IPerson* newPerson);
    void personRemoved(int id);
    void personUpdated(IPerson* updatedPerson);
    void dataChanged();

private:
    PersonRepository() = default;
    ~PersonRepository();

    QJsonArray saveToJsonArray() const;
    void loadFromJsonArray(const QJsonArray& array);

    std::vector<IPerson*> persons;
    PersonFactory* factory = nullptr;
    int nextId = 1;
    std::map<IPerson*, std::vector<int>> pendingRelations;
};

#endif // PERSONREPOSITORY_H