#include <QMessageBox>
#include <QDate>
#include "include/mainwindow.h"

#include "../include/inputdialog.h"
#include "../include/personlistwidget.h"
#include "personscene.h"
#include "personfactory.h"
#include "ui_mainwindow.h"

class PersonScene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      factory(new DefaultPersonFactory())
{
    ui->setupUi(this);

    setWindowTitle(tr("Построение генеалогического древа"));
    setMinimumSize(400, 300);
    resize(1000, 800);

    PersonRepository::instance().setFactory(factory);

    scene = new PersonScene(this);
    ui->graphicsView->setScene(scene);

    ui->listWidget->setScene(scene);


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

    connect(&repo, &PersonRepository::personAdded,
            scene, &PersonScene::addPerson);

    connect(&repo, &PersonRepository::personUpdated,
            scene, &PersonScene::updatePerson);

    repo.loadFromFile("persons.json");
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showInputDialog() {
    InputDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {

        qDebug() << "Creating new person...";
        IPerson *person = repo.createIndividual();
        qDebug() << "Person created with ID:" << person->getId();

        person->setName(dialog.getName().toStdString());
        person->setGender(dialog.getGender().toStdString());

        QDate qDate = dialog.getBirthday();
        std::tm tmDate = {};
        tmDate.tm_year = qDate.year() - 1900;
        tmDate.tm_mon = qDate.month() - 1;
        tmDate.tm_mday = qDate.day();
        person->setBirthday(tmDate);

        person->setPlaceOfBirth(dialog.getPlaceOfBirth().toStdString());
        person->setProfession(dialog.getProfession().toStdString());

        qDebug() << "Person name set to:" << QString::fromStdString(person->getName());
        qDebug() << "Persons in repo:" << repo.getAllPersons().size();

        repo.notifyPersonUpdated(person);

        QMessageBox::information(this, "Данные", "Данные добавлены");
    }
}


void MainWindow::closeEvent(QCloseEvent *event) {
    repo.saveToFile("persons.json");
    QMainWindow::closeEvent(event);
}
