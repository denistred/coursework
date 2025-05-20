#include <QMessageBox>
#include "mainwindow.h"
#include "inputdialog.h"
#include "personlistwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(tr("Qt Application"));
    setMinimumSize(400, 300);
    resize(800, 600);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::showInputDialog);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showInputDialog() {
    InputDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString message = QString("Dialog is working");
        QString name = dialog.getName();
        Person *person = new Person();
        person->setName(name);
        this->addListItem(person);

        QMessageBox::information(this, "Данные", message);
    }
}

void MainWindow::addListItem(Person *person) {
    person->setName(person->getName());
    ui->listWidget->addPerson(person);
}
