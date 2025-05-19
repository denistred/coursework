#ifndef PERSON_H
#define PERSON_H

#include <QDate>
#include <QString>
#include <QObject>

class Person : public QObject
{
    Q_OBJECT


    public:
        explicit Person(QObject *parent = nullptr);

        enum Gender {
            Male,
            Female
        };
        Q_ENUM(Gender)

        QString getName() const;
        void setName(const QString &name);

        Gender getGender() const;
        void setGender(const Gender &gender);

        QDate getBirthday() const;
        void setBirthday(const QDate &date);

        QString getPlaceOfBirth() const;
        void setPlaceOfBirth(const QString &placeOfBirth);

        QString getProfession() const;
        void setProfession(const QString &profession);

    private:
        QString name;
        Gender gender;
        QDate birthday;
        QString placeOfBirth;
        QString profession;
};

#endif