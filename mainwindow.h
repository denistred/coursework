#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "person.h"

namespace Ui {
    class MainWindow;
}

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
};

#endif