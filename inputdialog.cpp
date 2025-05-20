#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);

    setWindowTitle("Ввод данных");
    resize(300, 150);
}

InputDialog::~InputDialog()
{
    delete ui;
}

QString InputDialog::getName() const {
    return ui->nameLineedit->text();
}

QString InputDialog::getGender() const {
    return ui->genderComboBox->currentText();
}

QString InputDialog::getBirthday() const {
    return ui->birthdayDateEdit->date().toString("dd.MM.yyyy");
}

QString InputDialog::getPlaceOfBirth() const {
    return ui->placeOfBirthLineEdit->text();
}

QString InputDialog::getProfession() const {
    return ui->professionLineEdit->text();
}

