#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle(tr("Qt Application"));
    setMinimumSize(400, 300);
    resize(800, 600);
}


MainWindow::~MainWindow() {
    delete ui;
}
