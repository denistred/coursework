#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "individual.h"
#include "personscene.h"
#include "personrepository.h"

namespace Ui {
    class MainWindow;
}

class PersonScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void showInputDialog();


private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    PersonScene *scene;
    PersonRepository& repo = PersonRepository::instance();
    PersonFactory* factory;
};

#endif