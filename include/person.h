#ifndef PERSON_H
#define PERSON_H

#include <QDate>
#include <QString>
#include <QObject>

class Person : public QObject
{
    Q_OBJECT


    public:
        static int nextId;
        explicit Person(QObject *parent = nullptr);

        int getId() const;
        void setId(int newId);

        QString getName() const;
        void setName(const QString &name);

        QString getGender() const;
        void setGender(const QString &gender);

        QDate getBirthday() const;
        void setBirthday(const QDate &date);

        QString getPlaceOfBirth() const;
        void setPlaceOfBirth(const QString &placeOfBirth);

        QString getProfession() const;
        void setProfession(const QString &profession);

        QString getPhotoPath() const;
        void setPhotoPath(const QString &path);

    signals:
        void nameChanged(const QString &newName);

    private:
        int id;
        QString name;
        QString gender;
        QDate birthday;
        QString placeOfBirth;
        QString profession;
        QString photoPath;
};


#endif