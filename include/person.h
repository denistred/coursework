#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QDate>
#include <QPointF>

class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);

    int getId() const;
    void setId(int id);

    QString getName() const;
    void setName(const QString &name);

    QString getGender() const;
    void setGender(const QString &gender);

    QDate getBirthday() const;
    void setBirthday(const QDate &birthday);

    QString getPlaceOfBirth() const;
    void setPlaceOfBirth(const QString &placeOfBirth);

    QString getProfession() const;
    void setProfession(const QString &profession);

    QString getPhotoPath() const;
    void setPhotoPath(const QString &photoPath);

    QList<int> getRelations() const;
    void addRelation(int id);
    void removeRelation(int id);
    void setRelations(const QList<int> &relations);

    void setPosition(const QPointF &pos);
    QPointF getPosition() const;

    signals:
        void dataChanged();

private:
    int id = -1;
    QString name;
    QString gender;
    QDate birthday;
    QString placeOfBirth;
    QString profession;
    QString photoPath;
    QList<int> relations;
    QPointF position;
};

#endif // PERSON_H
