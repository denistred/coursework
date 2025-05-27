#include "../include/inputdialog.h"
#include "ui_inputdialog.h"
#include <QFileDialog>


InputDialog::InputDialog(QWidget *parent, Person *person) : QDialog(parent),
                                                            ui(new Ui::InputDialog) {
    ui->setupUi(this);

    setWindowTitle("Изменение данных");
    resize(300, 150);

    if (person != nullptr) {
        this->loadPerson(person);
    }

    connect(ui->loadPhotoButton, &QPushButton::clicked, this, &InputDialog::choosePhoto);
}

InputDialog::~InputDialog() {
    delete ui;
}


QString InputDialog::getName() const {
    return ui->nameLineedit->text();
}

void InputDialog::setName(const QString &name) {
    ui->nameLineedit->setText(name);
}

QString InputDialog::getGender() const {
    return ui->genderComboBox->currentText();
}

void InputDialog::setGender(const QString &gender) {
    ui->genderComboBox->setCurrentText(gender);
}

QDate InputDialog::getBirthday() const {
    return ui->birthdayDateEdit->date();
}

void InputDialog::setBirthday(const QDate &birthday) {
    ui->birthdayDateEdit->setDate(birthday);
}

QString InputDialog::getPlaceOfBirth() const {
    return ui->placeOfBirthLineEdit->text();
}

void InputDialog::setPlaceOfBirth(const QString &placeOfBirth) {
    ui->placeOfBirthLineEdit->setText(placeOfBirth);
}

QString InputDialog::getProfession() const {
    return ui->professionLineEdit->text();
}

void InputDialog::setProfession(const QString &profession) {
    ui->professionLineEdit->setText(profession);
}

void InputDialog::loadPerson(Person *person) {
    this->setName(person->getName());
    this->setGender(person->getGender());
    this->setBirthday(person->getBirthday());
    this->setPlaceOfBirth(person->getPlaceOfBirth());
    this->setProfession(person->getProfession());
    this->setPhotoPath(person->getPhotoPath());
}

void InputDialog::setPhotoPath(const QString &photoPath) {
    ui->filepathLabel->setText(photoPath);
}

QString InputDialog::getPhotoPath() const {
    return ui->filepathLabel->text();
}

void InputDialog::choosePhoto() {
    QString filename = QFileDialog::getOpenFileName(this,
        "Выбор фотографии", QString(), "Изображения (*.png *.jpg *.jpeg *.bmp)");

    if (!filename.isEmpty()) {
        this->setPhotoPath(filename);
    }
}
