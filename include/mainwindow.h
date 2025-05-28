#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "person.h"
#include "personscene.h"
#include "abstractfactory.h"

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

    void addListItem(Person *person);

private slots:
    void showInputDialog();


private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    PersonScene *scene;
    AbstractItemFactory* factory;
};

#endif