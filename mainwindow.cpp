#include <QMessageBox>
#include "mainwindow.h"
#include "inputdialog.h"
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

void MainWindow::showInputDialog()
{
    InputDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString message = QString("Dialog is working");

        QMessageBox::information(this, "Данные", message);
    }
}