#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include "person.h"

namespace Ui {
    class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    InputDialog(QWidget *parent = nullptr, Person *person = nullptr);
    ~InputDialog();

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
    void loadPerson(Person *person);

private:

    Ui::InputDialog *ui;
};

#endif