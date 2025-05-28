#include <QMessageBox>
#include "include/mainwindow.h"

#include "../include/inputdialog.h"
#include "../include/personlistwidget.h"
#include "personscene.h"
#include "personfactory.h"
#include "ui_mainwindow.h"

class PersonScene;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle(tr("Построение гениалогического древа"));
    setMinimumSize(400, 300);
    resize(1000, 800);

    factory = new PersonFactory();
    ui->listWidget->setFactory(factory);

    scene = new PersonScene(this);
    ui->graphicsView->setScene(scene);
    ui->listWidget->setScene(scene);
    for (Person *p : ui->listWidget->getPersons()) {
        scene->addPerson(p);
    }

    ui->listWidget->loadFromFile("persons.json");
    connect(ui->addButton, &QPushButton::clicked,
            this, &MainWindow::showInputDialog);
    connect(ui->deleteButton, &QPushButton::clicked,
                ui->listWidget, &PersonListWidget::removeSelectedPerson);

    connect(ui->listWidget, &PersonListWidget::personSelected,
        scene, &PersonScene::selectPersonById);

    connect(scene, &PersonScene::personSelected,
            ui->listWidget, &PersonListWidget::selectPersonById);


    connect(ui->addRelationButton, &QPushButton::clicked, this, [this]() {
        scene->createRelationBetweenSelected();
    });

    connect(ui->removeRelationButton, &QPushButton::clicked, this, [this]() {
        scene->removeRelationBetweenSelected();
    });

}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showInputDialog() {
    InputDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString message = QString("Данные добавлены");
        Person *person = factory->createPerson();
        person->setName(dialog.getName());
        person->setGender(dialog.getGender());
        person->setBirthday(dialog.getBirthday());
        person->setPlaceOfBirth(dialog.getPlaceOfBirth());
        person->setProfession(dialog.getProfession());
        this->addListItem(person);

        QMessageBox::information(this, "Данные", message);
    }
}

void MainWindow::addListItem(Person *person) {
    person->setName(person->getName());
    ui->listWidget->addPerson(person);

    scene->addPerson(person);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    ui->listWidget->saveToFile("persons.json");
    QMainWindow::closeEvent(event);
}
